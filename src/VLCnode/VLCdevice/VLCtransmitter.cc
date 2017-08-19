/*
 * VLCtransmitter.cc
 *
 *  Created on: Jul 30, 2017
 *      Author: casper
 */

#include <VLCtransmitter.h>
#include <VLCchannelMsg_m.h>
#include <VLCmobilityManager.h>
#include <VLCpacket_m.h>
#include <VLCtransmissionModels.h>

void VLC::VLCtransmitter::initialize(){
    VLCdevice::initialize();

    // Set the transmitter lambertian order
    this->lambertianOrder = - ( log(2) / log( cos( this->semiAngle ) ) );

    this->deviceType = TRANSMITTER_DEVICE;
    scheduleAt(simTime() + 500, new cMessage("Starting transmission!", 1));
}

double VLC::VLCtransmitter::getLambertianOrder() const {
    return lambertianOrder;
}

void VLC::VLCtransmitter::handleMessage(cMessage *msg){
    switch(msg->getKind()){
        case 1:{
            this->startTransmission();
            break;
        }
        case 2:{
            this->stopTransmission();
            break;
        }
    }
    delete msg;
}


std::map<std::string, double> VLC::VLCtransmitter::getCurrentTransmissionInfo() {
    return this->currentTransmissionInfo;
}

void VLC::VLCtransmitter::startTransmission() {
    VLCchannelSignalBegin *csb = new VLCchannelSignalBegin();
    csb->setMessageType(CH_BEGIN_COMM_MSG);
    csb->setNodeId(this->getId());

    // Set the info for the transmission
    this->currentTransmissionInfo["modulationType"] = PAM;
    this->currentTransmissionInfo["transmissionPower"] = 50.0;
    this->currentTransmissionInfo["packetLength"] = 32.0;
    this->currentTransmissionInfo["modulationOrder"] = 2;


    csb->encapsulate(new VLCpacket("Hello"));
    send(csb, "channelPort$o");
    scheduleAt(simTime()+500, new cMessage("Done", 2));
}

void VLC::VLCtransmitter::stopTransmission() {
    VLCchannelSignalEnd *cse = new VLCchannelSignalEnd();
    cse->setNodeId(this->getId());
    cse->setMessageType(CH_END_COMM_MSG);
    sendDelayed(cse, 1000.0, "channelPort$o");
}
