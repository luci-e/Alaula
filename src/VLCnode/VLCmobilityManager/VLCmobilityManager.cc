/*
 * VLCmobilityManager.cc
 *
 *  Created on: Jul 31, 2017
 *      Author: casper
 */

#include <VLCmobilityManager.h>
#include <VLCmobilityMsg_m.h>
#include <VLCpacket_m.h>
#include <VLCchannel.h>
#include <math.h>
#include <VLCcommons.h>

void VLC::VLCmobilityManager::initialize() {
    this->channel = dynamic_cast<VLC::VLCchannel*>(cSimulation::getActiveSimulation()->getModuleByPath(VLC_CHANNEL_NAME));
    this->channel->addMobility(gate("channelPort"));

    std::vector<double> mobilityPars = cStringTokenizer(par("mobilityPars").stringValue()).asDoubleVector();
    if( mobilityPars.size() >= 5){
        // Set the position of the device
        this->nodePosition = {  mobilityPars[0],
                                mobilityPars[1],
                                mobilityPars[2],
                                mobilityPars[3],
                                mobilityPars[4]};

        // Start moving if the parameters have been set

        this->calculateDirection();
        this->notifyChannel();

        if(mobilityPars.size() >= 11){
            this->targetPosition = {mobilityPars[5], mobilityPars[6], mobilityPars[7], mobilityPars[8], mobilityPars[9]};
        }
    }
}

void VLC::VLCmobilityManager::setTargetAngle(double alpha, double beta) {
}

void VLC::VLCmobilityManager::setNodePosition(double x, double y, double z, double alpha, double beta) {
    this->nodePosition = {x, y, z, alpha, beta};
    ev<<"I just set node Position to : ";
    printPosition(this->nodePosition);
    this->calculateDirection();
}

void VLC::VLCmobilityManager::setNodePosition(VLC::VLCnodePosition nodePosition) {
    this->nodePosition = nodePosition;
    this->calculateDirection();
}

const VLC::VLCnodePosition VLC::VLCmobilityManager::getNodePosition() const {
    return this->nodePosition;
}

void VLC::VLCmobilityManager::notifyChannel() {
    // Notify the channel of the change
    VLCmoveMsg *moveMessage = new VLCmoveMsg("Node: has moved!");
    moveMessage->setNodeId(this->device->getId());
    send(moveMessage, gate("channelPort"));
}

const VLC::VLCnodeDirection  VLC::VLCmobilityManager::getNodeDirection() const {
    return this->nodeDirection;
}

// Calculates the versor of the device
void VLC::VLCmobilityManager::calculateDirection() {
    double alpha = this->nodePosition.alpha;
    double beta = this->nodePosition.beta;

    this->nodeDirection = calculateVersor(alpha, beta);
}

// Updates the target coordinates and start the translation
void VLC::VLCmobilityManager::setTargetCoordinates(double x, double y, double z) {
    this->targetPosition = {x, y, z, this->targetPosition.alpha, this->targetPosition.beta};
}

void VLC::VLCmobilityManager::setDevice(VLCdevice * device) {
    this->device = device;
}
