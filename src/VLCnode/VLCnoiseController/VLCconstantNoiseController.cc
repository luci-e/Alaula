/*
 * VLCconstantNoiseController.cpp
 *
 *  Created on: Sep 7, 2017
 *      Author: casper
 */

#include <VLCconstantNoiseController.h>
#include <VLCpacket_m.h>
#include <omnetpp.h>

VLC::VLCconstantNoiseController::VLCconstantNoiseController() {
    // TODO Auto-generated constructor stub
}

VLC::VLCconstantNoiseController::~VLCconstantNoiseController() {
    // TODO Auto-generated destructor stub
}

bool VLC::VLCconstantNoiseController::stepNoise(double time) {
    VLCnoiseControlMsg * ctrlMsg = new VLCnoiseControlMsg();
    ctrlMsg->setNoisePower(this->noisePower);
    send(ctrlMsg, "noiseDevicePort$o");
    return true;
}

void VLC::VLCconstantNoiseController::initialize() {
    VLC::VLCnoiseController::initialize();
    std::vector<double> noisePars = cStringTokenizer(par("noisePars").stringValue()).asDoubleVector();
    this->noisePower = noisePars[0];
}


