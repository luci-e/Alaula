/*
 * VLCmobilityManager.cpp
 *
 *  Created on: Jul 31, 2017
 *      Author: casper
 */

#include <VLCmobilityManager.h>
#include <VLCchannel.h>
#include <math.h>

void VLC::VLCmobilityManager::initialize() {
    this->channel = dynamic_cast<VLC::VLCchannel*>(cSimulation::getActiveSimulation()->getModuleByPath(VLC_CHANNEL_NAME));
    this->channel->addMobility(gate("channelPort"));
}

void VLC::VLCmobilityManager::setTargetAngle(double alpha, double beta, double angularSpeed) {
}

void VLC::VLCmobilityManager::setNodePosition(double x, double y, double z, double alpha, double beta) {
    this->nodePosition = {x, y, z, alpha, beta};
    this->calculateDirection();
}

void VLC::VLCmobilityManager::setNodePosition(
        VLC::VLCnodePosition nodePosition) {
    this->nodePosition = nodePosition;
    this->calculateDirection();
}

const VLC::VLCnodePosition VLC::VLCmobilityManager::getNodePosition() const {
    return this->nodePosition;
}

const VLC::VLCnodeDirection  VLC::VLCmobilityManager::getNodeDirection() const {
    return this->nodeDirection;
}

// Calculate the normalised vector
void VLC::VLCmobilityManager::calculateDirection() {
    double alpha = this->nodePosition.alpha;
    double beta = this->nodePosition.beta;

    this->nodeDirection = {
            cos(beta)*sin(alpha),
            cos(beta)*cos(alpha),
            sin(beta)
    };
}

// Updates the target coordinates and start the translation
void VLC::VLCmobilityManager::setTargetCoordinates(double x, double y, double z,
        double speed) {
    this->targetPosition = {x, y, z, this->targetPosition.alpha, this->targetPosition.beta};
    this->speed = speed;
    VLCupdateMovMsg* movMsg = new VLCupdateMovMsg();
    movMsg->setType(STEP_TRANSLATION);
    this->scheduleAt(simTime(), movMsg);
}

void VLC::VLCmobilityManager::setNodeId(int nodeId) {
    this->nodeId = nodeId;
}
