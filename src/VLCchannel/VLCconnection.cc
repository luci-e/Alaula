/*
 * VLCconnection.cpp
 *
 *  Created on: Aug 8, 2017
 *      Author: casper
 */

#include <VLCconnection.h>
#include <VLCchannelMsg_m.h>
#include <VLCchannel.h>
#include <math.h>
#include <map>
#include <string>
#include <VLCtransmissionModels.h>
#include <VLCtransmitter.h>

namespace VLC {


VLCconnection::VLCconnection(VLCdevice *  transmitter, VLCdevice *  receiver, VLCchannel* channel) : transmitter(dynamic_cast<VLCtransmitter*>(transmitter)), receiver(dynamic_cast<VLCreceiver*>(receiver)), channel(channel){
    // Dummy connections are built with NULL that would cause a segfault
    if( channel != NULL){
        this->gainConstantPart = ( this->transmitter->getLambertianOrder() + 1 ) * this->receiver->getPhotoDetectorArea() / ( 2 * M_PI );
        this->transmissionInfo = this->transmitter->getCurrentTransmissionInfo();
        this->updateConnection();
    }
}
// Add a new value to the SINR trend
void VLCconnection::calculateNextValue() {
    // TODO: magic responsivity number
    double receivedSignalPower = this->connectionGain * this->transmissionInfo["transmissionPower"];
    double SINR =  (receivedSignalPower * 0.003) * (receivedSignalPower * 0.003) / this->receiver->getNoiseVariance(this->transmissionInfo["transmissionPower"]);
    this->SINRTrend.push_back((VLCtimeSINR) {simTime(), SINR});
}

// Updates the values used to calculate the SINR
void VLCconnection::updateConnection() {
    VLCdevViewInfo viewInfo = this->channel->getDevViewInfo(this->transmitter, this->receiver);
    // TODO: Find the function for the optical filter gain and put it as part of the equation!
    this->connectionGain = (this->gainConstantPart / (viewInfo.distance)) * std::pow(cos(viewInfo.angle1), transmitter->getLambertianOrder()) * 1.0 * this->receiver->opticalGain(viewInfo.angle2) * cos(viewInfo.angle2);
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
    // Given the SINR trend and the parameters of the connection return the outcome of the transmission
    return VLC::packetTransmitted(this->SINRTrend, this->transmissionInfo);
}

// Abort this connection
void VLCconnection::abortConnection() const{
    ev<<"oh noes!\n";
}

} /* namespace VLC */


