/*
 * VLCemitter.cc
 *
 *  Created on: Sep 5, 2017
 *      Author: casper
 */

#include <VLCemitter.h>
#include <string>

std::map<VLC::transmissionKeys, double>& VLC::VLCemitter::getCurrentTransmissionInfo(){
    return this->currentTransmissionInfo;
}

double VLC::VLCemitter::getLambertianOrder() const {
    return lambertianOrder;
}

VLC::VLCemitter::VLCemitter() {
    this->currentTransmissionInfo[TRANSMISSION_POWER] = 0;
}

double VLC::VLCemitter::getEmitterPower() {
    return this->currentTransmissionInfo[TRANSMISSION_POWER];
}
