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

// Add a new value to the SINR trend
void VLCconnection::addValue(VLC::VLCtimeSINR ts) {
    this->SINRTrend.push_back(ts);
}

// A connection equals another iff the transmitter and receiver are the same
inline bool VLCconnection::operator==(const VLCconnection &c2) const{
    return ((this->transmitter) == (c2.transmitter)) && ((this->receiver) == (c2.receiver));
}


// C1 is lt C2 iff (c1.transmitter < c2.transmitter) or ((c1.transmitter == c2.transmitter) and (c1.receiver < c2.receiver ))
bool VLCconnection::operator<(const VLCconnection& c2) const {
    if(this->transmitter->getId() < c2.transmitter->getId()){
        return true;
    }

    if(this->transmitter->getId() == c2.transmitter->getId()){
        return this->receiver->getId() < c2.receiver->getId();
    }

    return false;
}

VLCconnection::~VLCconnection() {}

// Compute the outcome of this transmission, returns true if it was successful false otherwise
bool VLCconnection::getOutcome() {
    // Given the SINR trend and the parameters of the connection return the outcom of the transmission
    return true;
}



// Abort this connection
void VLCconnection::abortConnection() const{
    ev<<"oh noes!\n";
}

} /* namespace VLC */
