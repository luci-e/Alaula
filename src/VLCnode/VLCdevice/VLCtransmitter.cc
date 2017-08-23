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

void VLC::VLCtransmitter::initialize(){
    VLCdevice::initialize();

    this->lambertianOrder = - ( log(2) / log( cos( this->semiAngle ) ) );
    this->deviceType = TRANSMITTER_DEVICE;
}

double VLC::VLCtransmitter::getLambertianOrder() const {
    return lambertianOrder;
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


std::map<std::string, double> VLC::VLCtransmitter::getCurrentTransmissionInfo() {
    return this->currentTransmissionInfo;
}

void VLC::VLCtransmitter::startTransmission(dataPacket *dataPacket) {
    VLCchannelSignalBegin *csb = new VLCchannelSignalBegin();
    csb->setMessageType(VLC_SIG_BEGIN_MSG);
    csb->setNodeId(this->getId());

    // Set the info for the transmission
    this->currentTransmissionInfo["modulationType"] = dataPacket->getModulationType();
    this->currentTransmissionInfo["transmissionPower"] = dataPacket->getTransmissionPower();
    this->currentTransmissionInfo["packetLength"] = dataPacket->getByteLength();

    switch(dataPacket->getModulationType()){
        case PAM:{
            this->currentTransmissionInfo["modulationOrder"] = dataPacket->getModulationOrder();
            break;
        }

        case VPPM:{
            this->currentTransmissionInfo["dutyCycle"] = dataPacket->getDutyCycle();
            break;
        }
    }


    csb->encapsulate(dataPacket);
    send(csb, "channelPort$o");

    // Close the transmission when done
    VLCctrlMsg *ctrlMessage = new VLCctrlMsg();
    ctrlMessage->setCtrlCode(TRANSMISSION_DONE);
    scheduleAt(simTime()+500, ctrlMessage);
}

void VLC::VLCtransmitter::stopTransmission() {
    VLCchannelSignalEnd *cse = new VLCchannelSignalEnd();
    cse->setNodeId(this->getId());
    cse->setMessageType(VLC_SIG_END_MSG);
    send(cse, "channelPort$o");
}
