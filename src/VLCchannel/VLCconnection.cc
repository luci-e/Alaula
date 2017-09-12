/*
 * VLCconnection.cpp
 *
 *  Created on: Aug 8, 2017
 *      Author: casper
 */

#include <VLCconnection.h>
#include <VLCpacket_m.h>
#include <VLCchannel.h>
#include <math.h>
#include <map>
#include <string>
#include <vector>
#include <VLCtransmissionModels.h>
#include <VLCtransmitter.h>
#include <VLCnoiseDevice.h>
#include <VLCemitter.h>
#include <VLCcommons.h>
#include <Log.h>

namespace VLC {

long unsigned int VLCconnection::connectionCounter = 0;

VLCconnection::VLCconnection(VLCdevice *  transmitter, VLCdevice *  receiver, VLCchannel* channel) : transmitter(dynamic_cast<VLCtransmitter*>(transmitter)), receiver(dynamic_cast<VLCreceiver*>(receiver)), channel(channel){
    // Dummy connections are built with NULL that would cause a segfault
    if( channel != NULL){
        // Assign an Id to this connection
        this->connectionId = connectionCounter;
        connectionCounter++;

        this->connGainConstantPart = (( this->transmitter->getLambertianOrder() + 1.0 ) * this->receiver->getPhotoDetectorArea()) / ( 2.0 * M_PI );
        //ev<<"LambertianOrder: "<<this->transmitter->getLambertianOrder()<<" PhotoDetectorArea: "<<this->receiver->getPhotoDetectorArea()<<"\n";
        this->transmissionInfo = this->transmitter->getCurrentTransmissionInfo();
    }
}
// Add a new value to the SINR trend
void VLCconnection::calculateNextValue() {
    this->SINRTrend.push_back(VLCtimeSINR(simTime().dbl(), this->SINRdB));
    VLCdevViewInfo viewInfo = this->channel->getDevViewInfo(this->transmitter, this->receiver);
    LOGN << this->connectionId << ";"\
            << viewInfo.device1 << ";"\
            << viewInfo.device2 << ";"\
            << simTime().dbl() << ";"\
            << "PositionSINRdB" << ";"\
            << this->receiver->getNodePosition().y << ";"\
            << SINRdB << ";"\
            << 0;
}

// Updates the values used to calculate the SINR
void VLCconnection::updateConnection() const{
    VLCdevViewInfo viewInfo = this->channel->getDevViewInfo(this->transmitter, this->receiver);
    this->lastView = viewInfo;
    //ev<<"Distance is now "<<viewInfo.distance<<"\n";
    // TODO: Find the function for the optical filter gain and put it as part of the equation!
    this->connectionGain = (this->connGainConstantPart / (viewInfo.distance * viewInfo.distance)) * std::pow(cos(viewInfo.angle1), transmitter->getLambertianOrder()) * 1.0 * this->receiver->opticalGain(viewInfo.angle2) * cos(viewInfo.angle2);
    double receivedSignalPower = this->connectionGain * std::pow(10.0, ((this->transmissionInfo[TRANSMISSION_POWER]) - 30) / 10.0);
    // TODO: magic responsivity number
    double signal =  ((receivedSignalPower * 0.003) * (receivedSignalPower * 0.003));
    double noisePlusInterference = this->receiver->getNoiseVariance(receivedSignalPower) + this->totalNoisePower;

    //ev<<"Received signal power is "<<receivedSignalPower<<"\n";
    //ev<<"Noise variance is "<<this->receiver->getNoiseVariance(receivedSignalPower)<<"\n";

    this->SINRdB = 10.0 * log10(signal / noisePlusInterference);

    ev<<"Connection between "<<this->transmitter->getId()<<" and "<<this->receiver->getId()<<"\n";
    ev<<"ReceivedPower: "<<this->connectionGain * this->transmissionInfo[TRANSMISSION_POWER]<<\
        "\nSINRdB: "<<this->SINRdB<<"\n";
    printDevViewInfo(this->lastView);
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
    return VLC::packetTransmitted(this);
}

// Abort this connection
void VLCconnection::abortConnection() const{
    ev<<"oh noes!\n";
}

// Adds a noise source that can be another transmitter or an actual noise source
void VLCconnection::addNoiseSource(VLCdevice* noiseSource) const{
    sourceInfo noiseSourceInfo;

    // Fill the constant fields for this noise source
    noiseSourceInfo.source = noiseSource;

    // Let the updater fill the rest
    this->noiseSources[noiseSource] = noiseSourceInfo;
    this->updateNoiseSource(noiseSource);
}

// Recalculates the values for this noise source
void VLCconnection::updateNoiseSource(VLCdevice* noiseSource) const{
    sourceInfo noiseSourceInfo = this->noiseSources[noiseSource];
    double lambertianOrder, emitterPower;

    // We can't just treat the noiseSource as an emitter because of multiple inheritance
    // therefore we must check at runtime what we've been passed and perform the necessary
    // castings.
    switch(noiseSource->getDeviceType()){
        case TRANSMITTER_DEVICE:{
            lambertianOrder = ((VLCtransmitter*) noiseSource)->getLambertianOrder();
            emitterPower = ((VLCtransmitter*) noiseSource)->getEmitterPower();
            break;
        }
        case NOISE_DEVICE:{
            lambertianOrder = ((VLCnoiseDevice*) noiseSource)->getLambertianOrder();
            emitterPower = ((VLCnoiseDevice*) noiseSource)->getEmitterPower();
            break;
        }
        default:
            // Shoo shoo
            break;
    }

    noiseSourceInfo.gainConstantPart = ((lambertianOrder + 1.0 ) * this->receiver->getPhotoDetectorArea()) / ( 2.0 * M_PI );

    // Recalculate the structure for this noise source
    VLCdevViewInfo viewInfo = this->channel->getDevViewInfo(noiseSource, this->receiver);
    noiseSourceInfo.sourceGain = (noiseSourceInfo.gainConstantPart / (viewInfo.distance * viewInfo.distance)) * std::pow(cos(viewInfo.angle1), lambertianOrder) * 1.0 * this->receiver->opticalGain(viewInfo.angle2) * cos(viewInfo.angle2);

    double receivedSignalPower = noiseSourceInfo.sourceGain  * std::pow(10.0, (emitterPower - 30) / 10.0);
    noiseSourceInfo.signalPower = ((receivedSignalPower * 0.003) * (receivedSignalPower * 0.003));

    this->noiseSources[noiseSource] = noiseSourceInfo;
    this->calculateTotalNoise();
}

// Removes the noise source from the map of this connection
void VLCconnection::removeNoiseSource(VLCdevice* noiseSource) {
    this->noiseSources.erase(noiseSource);
    this->calculateTotalNoise();
}

// Calculates the total noise power
void VLCconnection::calculateTotalNoise() const{
    double totalNoise = 0;
    for( auto& ei : this->noiseSources){
        totalNoise += ei.second.signalPower;
    }
    this->totalNoisePower = totalNoise;
}

std::vector<VLCtimeSINR>& VLCconnection::getSINRTrend() {
    return this->SINRTrend;
}

std::map<transmissionKeys, double>& VLCconnection::getTransmissionInfo() {
    return this->transmissionInfo;
}

const VLCdevViewInfo& VLCconnection::getLastView() const {
    return lastView;
}

unsigned long int VLCconnection::getConnectionId() const {
    return connectionId;
}

} /* namespace VLC */


