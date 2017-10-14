/*
 * VLCtransmitter.cc
 *
 *  Created on: Jul 30, 2017
 *      Author: casper
 */

#include <VLCtransmitter.h>
#include <VLCpacket_m.h>
#include <VLCmobilityManager.h>
#include <VLCpacket_m.h>
#include <VLCtransmissionModels.h>
#include <stdlib.h>
#include <time.h>
#include <VLCnetController.h>

void VLC::VLCtransmitter::initialize(){
    VLCdevice::initialize();
    this->currentTransmissionInfo[TRANSMISSION_POWER] = 0;
    this->lambertianOrder = -( log(2.0) / log(cos(this->semiAngle)));
    this->deviceType = TRANSMITTER_DEVICE;
    this->address = par("address");

    std::vector<double> devicePars = cStringTokenizer(par("devPars").stringValue()).asDoubleVector();
    this->maxTransmissionPower =  devicePars[1];

    cGate * controllerGate = gate("controllerPort$o")->getPathEndGate();
    ((VLCnetController *) controllerGate->getOwnerModule())->registerTransmitter(this->address, this->getId(), controllerGate);
}

void VLC::VLCtransmitter::handleMessage(cMessage *msg){
    // If it's not a self message it can be either a ctrl message or a data message
    VLCpacket *vlcMsg = (VLCpacket*) msg;

    switch(vlcMsg->getMessageType()){
        case VLC_DATA_MSG: case VLC_MAC_MSG:{
            this->startTransmission(vlcMsg);
            break;
        }

        case VLC_CTRL_MSG:{
            VLCctrlMsg * ctrlMsg = (VLCctrlMsg*) vlcMsg;
            switch(ctrlMsg->getCtrlCode()){
                case TRANSMISSION_END:{
                    // Stop the transmission inform the queue that the device is now available to send another packet
                    this->stopTransmission();
                    send(ctrlMsg, "controllerPort$o");
                    break;
                }
                case ABORT_TRANSMISSION:{
                    // Stop the transmission inform the channel that the transmission has stopped
                    this->abortTransmission();
                    delete msg;
                    break;
                }
                case VPPM_CYCLE_DOWN:{
                    //this->currentTransmissionInfo[TRANSMISSION_POWER] = 1.0;
                    //this->updateMyConnections();
                    delete msg;
                    break;
                }
            }
        }
    }
}


void VLC::VLCtransmitter::startTransmission(VLCpacket *packet) {
    VLCctrlMsg *csb = new VLCctrlMsg();
    csb->setMessageType(VLC_CTRL_MSG);
    csb->setCtrlCode(TRANSMISSION_BEGIN);
    csb->setNodeId(this->getId());

    double dataRate = this->getDataRate();
    double transmissionTime = this->getTransmissionTime(packet->getByteLength(), dataRate);

    switch(packet->getMessageType()){
        case VLC_DATA_MSG:{
            dataPacket *dp = (dataPacket*) packet;
            // Set the info for the transmission
            this->currentTransmissionInfo[MODULATION_TYPE] = dp->getModulationType();
            this->currentTransmissionInfo[TRANSMISSION_POWER] = dp->getTransmissionPower();
            this->currentTransmissionInfo[PACKET_LENGTH] = dp->getByteLength();
            dp->setTransmissionStartTime(simTime().dbl());
            this->lastPacket = *dp;

            // NOooooooo
            switch(dp->getModulationType()){
                case PAM:{
                    this->currentTransmissionInfo[MODULATION_ORDER] = dp->getModulationOrder();
                    break;
                }
                case VPPM:{
                    VLCctrlMsg * VPPMctrl = new VLCctrlMsg();
                    VPPMctrl->setMessageType(VLC_CTRL_MSG);
                    VPPMctrl->setCtrlCode(VPPM_CYCLE_DOWN);
                    double dutyCycle = dp->getDutyCycle();

                    this->currentTransmissionInfo[DUTY_CYCLE] = dutyCycle;
                    scheduleAt( simTime() + (transmissionTime * dutyCycle), VPPMctrl);
                    break;
                }
            }

            csb->encapsulate(dp);
            break;
        }
        case VLC_MAC_MSG:{
            VLCBeaconMsg *bp = (VLCBeaconMsg*) packet;
            // We know he can only receive beacon messages
            this->currentTransmissionInfo[MODULATION_TYPE] = bp->getModulationType();
            this->currentTransmissionInfo[TRANSMISSION_POWER] = bp->getTransmissionPower();
            this->currentTransmissionInfo[PACKET_LENGTH] = bp->getByteLength();

            // I'm sorryyyyyy
            switch(bp->getModulationType()){
                case PAM:{
                    this->currentTransmissionInfo[MODULATION_ORDER] = bp->getModulationOrder();
                    break;
                }
                case VPPM:{
                    VLCctrlMsg * VPPMctrl = new VLCctrlMsg();
                    VPPMctrl->setMessageType(VLC_CTRL_MSG);
                    VPPMctrl->setCtrlCode(VPPM_CYCLE_DOWN);
                    double dutyCycle = bp->getDutyCycle();

                    this->currentTransmissionInfo[DUTY_CYCLE] = dutyCycle;
                    scheduleAt( simTime() + (transmissionTime * dutyCycle), VPPMctrl);
                    break;
                }
            }

            csb->encapsulate(bp);
            break;
        }
    }




    send(csb, "channelPort$o");
    // Close the transmission when done
    VLCctrlMsg *ctrlMessage = new VLCctrlMsg();
    ctrlMessage->setMessageType(VLC_CTRL_MSG);
    ctrlMessage->setCtrlCode(TRANSMISSION_END);
    ctrlMessage->setNodeAddress(this->address);
    ctrlMessage->setNodeId(this->getId());


    scheduleAt(simTime() + transmissionTime, ctrlMessage);
}

double VLC::VLCtransmitter::getTransmissionTime(double packetLength, double dataRate){
    double transmissionTime = (packetLength * 8.0 * 1000.0 / dataRate);
    ev<<"Transmission time is "<<transmissionTime<<"ms \n";
    return transmissionTime;
}

// Compute the datarate as a function of the transmissionInfo
double VLC::VLCtransmitter::getDataRate(){
    return 5000000.0;
}

void VLC::VLCtransmitter::stopTransmission() {
    VLCctrlMsg *cse = new VLCctrlMsg();

    cse->setNodeId(this->getId());
    cse->setNodeAddress(this->address);
    cse->setMessageType(VLC_CTRL_MSG);
    cse->setCtrlCode(TRANSMISSION_END);
    send(cse, "channelPort$o");
}

void VLC::VLCtransmitter::addConnectionStart(VLCconnection* connection) {
    this->connectionStarts.insert(connection);
}

void VLC::VLCtransmitter::removeConnectionStart(VLCconnection* connection) {
    this->connectionStarts.erase(connection);
}

void VLC::VLCtransmitter::updateMyConnections() {
    for( auto& conn : this->connectionStarts){
        conn->updateConnection();
        conn->calculateNextValue();
    }
}

void VLC::VLCtransmitter::abortTransmission() {
    VLCctrlMsg *csa = new VLCctrlMsg();

    csa->setNodeId(this->getId());
    csa->setNodeAddress(this->address);
    csa->setMessageType(VLC_CTRL_MSG);
    csa->setCtrlCode(TRANSMISSION_ABORT);
    send(csa, "channelPort$o");
}

std::set<VLC::VLCconnection*>& VLC::VLCtransmitter::getConnectionStarts(){
    return connectionStarts;
}
