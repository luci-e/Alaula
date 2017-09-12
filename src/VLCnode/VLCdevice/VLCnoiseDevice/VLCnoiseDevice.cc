/*
 * VLCtransmitter.cc
 *
 *  Created on: Jul 30, 2017
 *      Author: casper
 */

#include <VLCnoiseDevice.h>
#include <VLCpacket_m.h>
#include <VLCmobilityManager.h>
#include <VLCpacket_m.h>
#include <stdlib.h>
#include <time.h>

void VLC::VLCnoiseDevice::initialize(){
    VLCdevice::initialize();
    this->lambertianOrder = -( log(2.0) / log(cos(this->semiAngle)));
    this->deviceType = NOISE_DEVICE;
}

void VLC::VLCnoiseDevice::handleMessage(cMessage *msg){
    if(msg->isSelfMessage()){
        // What?
    }else{
        VLCnoiseControlMsg * ctrlMsg = (VLCnoiseControlMsg*) msg;
        this->setNoisePower(ctrlMsg->getNoisePower());
    }
}

// Sets the noise power level to the specified value in dBm
void VLC::VLCnoiseDevice::setNoisePower(double noisePower) {
    this->currentTransmissionInfo[TRANSMISSION_POWER] = noisePower;
    VLCnoiseMsg * noiseMsg = new VLCnoiseMsg();
    noiseMsg->setMessageType(VLC_NOISE_MSG);
    noiseMsg->setNodeId(this->getId());
    send(noiseMsg, "channelPort$o");
}
