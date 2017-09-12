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

void VLC::VLCtransmitter::initialize(){
    VLCdevice::initialize();
    this->currentTransmissionInfo[TRANSMISSION_POWER] = 0;
    this->lambertianOrder = -( log(2.0) / log(cos(2.0*this->semiAngle)));
    this->deviceType = TRANSMITTER_DEVICE;
}

void VLC::VLCtransmitter::handleMessage(cMessage *msg){
    if(msg->isSelfMessage()){
        VLCctrlMsg *ctrlMsg = (VLCctrlMsg*) msg;
        switch(ctrlMsg->getCtrlCode()){
            case TRANSMISSION_DONE:{
                // Stop the transmission inform the queue that the device is now available to send another packet
                this->stopTransmission();
                send(ctrlMsg, "queuePort$o");
                break;
            }
        }
    }else{
        // If it's not a self message it can be either a ctrl message or a data message
        VLCpacket *vlcMsg = (VLCpacket*) msg;

        switch(vlcMsg->getMessageType()){
            case VLC_DATA_MSG:{
                this->startTransmission((dataPacket*) vlcMsg);
                break;
            }

            case VLC_CTRL_MSG:{
                VLCctrlMsg * ctrlMsg = (VLCctrlMsg*) vlcMsg;
                switch(ctrlMsg->getCtrlCode()){
                    case ABORT_TRANSMISSION:{
                        this->stopTransmission();
                        break;
                    }
                }
            }
        }
    }
}


void VLC::VLCtransmitter::startTransmission(dataPacket *dataPacket) {
    VLCchannelSignalBegin *csb = new VLCchannelSignalBegin();
    csb->setMessageType(VLC_SIG_BEGIN_MSG);
    csb->setNodeId(this->getId());

    // Set the info for the transmission
    this->currentTransmissionInfo[MODULATION_TYPE] = dataPacket->getModulationType();
    this->currentTransmissionInfo[TRANSMISSION_POWER] = dataPacket->getTransmissionPower();
    this->currentTransmissionInfo[PACKET_LENGTH] = dataPacket->getByteLength();

    switch(dataPacket->getModulationType()){
        case PAM:{
            this->currentTransmissionInfo[MODULATION_ORDER] = dataPacket->getModulationOrder();
            break;
        }

        case VPPM:{
            this->currentTransmissionInfo[DUTY_CYCLE] = dataPacket->getDutyCycle();
            break;
        }
    }


    csb->encapsulate(dataPacket);
    send(csb, "channelPort$o");

    // Close the transmission when done
    VLCctrlMsg *ctrlMessage = new VLCctrlMsg();
    ctrlMessage->setCtrlCode(TRANSMISSION_DONE);
    dataPacket->setTransmissionStartTime(simTime().dbl());

    double dataRate = this->getDataRate();
    scheduleAt(simTime()+ this->getTransmissionTime(dataPacket->getByteLength(), dataRate), ctrlMessage);
    this->lastPacket = *dataPacket;

}

double VLC::VLCtransmitter::getTransmissionTime(double packetLength, double dataRate){
    double transmissionTime = (packetLength * 8.0 / dataRate);
    return transmissionTime;
}

// Compute the datarate as a function of the transmissionInfo
double VLC::VLCtransmitter::getDataRate(){
    return 5000000;
}

void VLC::VLCtransmitter::stopTransmission() {
    VLCchannelSignalEnd *cse = new VLCchannelSignalEnd();

    cse->setNodeId(this->getId());
    cse->setMessageType(VLC_SIG_END_MSG);
    send(cse, "channelPort$o");

}

void VLC::VLCtransmitter::addConnectionStart(VLCconnection* connection) {
    this->connectionStarts.insert(connection);
}

void VLC::VLCtransmitter::removeConnectionStart(VLCconnection* connection) {
    this->connectionStarts.erase(connection);
}

std::set<VLC::VLCconnection*>& VLC::VLCtransmitter::getConnectionStarts(){
    return connectionStarts;
}
