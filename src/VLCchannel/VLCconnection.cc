/*
 * VLCconnection.cpp
 *
 *  Created on: Aug 8, 2017
 *      Author: casper
 */

#include <VLCconnection.h>

namespace VLC {


VLCconnection::VLCconnection(VLCdevice *  transmitter, VLCdevice *  receiver) : transmitter(transmitter), receiver(receiver){
}

void VLCconnection::addValue(VLC::VLCtimeSINR ts) {
}

bool VLCconnection::operator == (const VLCconnection &c2){
    return ((this->transmitter) == (c2.transmitter)) && ((this->receiver) == (c2.receiver));
}


VLCconnection::~VLCconnection() {
    // TODO Auto-generated destructor stub
}

bool VLCconnection::getOutcome() {
    return true;
}

void VLCconnection::abortConnection() const{
    ev<<"oh noes!\n";
}

} /* namespace VLC */
