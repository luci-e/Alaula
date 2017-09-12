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
#include <iostream>
#include <fstream>
#include <map>
#include <regex>

void VLC::VLCmobilityManager::initialize() {
    this->channel = dynamic_cast<VLC::VLCchannel*>(cSimulation::getActiveSimulation()->getModuleByPath(VLC_CHANNEL_NAME));
    this->channel->addMobility(gate("channelPort"));

    this->parseMobilityFile(par("mobilityPars").stringValue());
    this->notifyChannel();

    if(this->currentWayPoint < this->totalWayPoints){
        this->calculateNextMovement();
        scheduleAt(simTime() + this->initialDelay, new cMessage());
    }
}

void VLC::VLCmobilityManager::handleMessage(cMessage* msg) {
    this->stepMovement();
    delete msg;
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

void VLC::VLCmobilityManager::setNodePosition(std::string nodePosition) {
    int readValues = sscanf(nodePosition.c_str() , "%lf %lf %lf %lf %lf", &this->nodePosition.x,
                                                                          &this->nodePosition.y,
                                                                          &this->nodePosition.z,
                                                                          &this->nodePosition.alpha,
                                                                          &this->nodePosition.beta);
    if(readValues != 5){
        ev<<"Invalid position\n";
        return;
    }

    ev<<"I just set node Position to : ";
    printPosition(this->nodePosition);
    this->calculateDirection();
    printVector(this->nodeDirection);

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

void VLC::VLCmobilityManager::parseMobilityFile(std::string mobilityFilePath) {
    std::ifstream mobilityFile;
    std::string line;

    mobilityFile.open(mobilityFilePath);

    if( mobilityFile.is_open()){
        bool foundMySettings = false;

        std::regex moduleName("^\[[A-z0-9]+\]$");
        std::string myModuleName = std::string("[")+this->getParentModule()->getName()+std::string("]");

        while ( getline (mobilityFile,line) ){
           // Explode the line into its tokens, call the appropriate function
           // throws out of range exception if .at fails

            if(regex_match(line, moduleName)){
                if(line == myModuleName){
                    foundMySettings = true;
                }else{
                    if(foundMySettings){
                        break;
                    }
                }
            }else{
                if(foundMySettings){
                    std::vector<std::string> tokenized = explode(line, ':');
                    this->callFunction(tokenized[0], tokenized[1]);
                }
            }
         }
    }else{
        ev<<"Error with mobility file parsing!\n";
        cSimulation::getActiveSimulation()->callFinish();
    }

    mobilityFile.close();
}

void VLC::VLCmobilityManager::parseWayPoints(std::string wayPointString) {
    std::vector<std::string> tokenized = explode(wayPointString, ';');
    VLCwayPoint nextWayPoint;

    // Read the wayPoints from the string
    for( std::vector<std::string>::iterator wp = tokenized.begin(); wp != tokenized.end(); wp++){
        int readValues = sscanf((*wp).c_str() , "%lf %lf %lf %lf %lf %lf", &nextWayPoint.position.x,
                                                                           &nextWayPoint.position.y,
                                                                           &nextWayPoint.position.z,
                                                                           &nextWayPoint.position.alpha,
                                                                           &nextWayPoint.position.beta,
                                                                           &nextWayPoint.linearSpeed);
        if(readValues != 6){
            ev<<"Invalid waypoint\n";
        }else{
            this->wayPoints.push_back(nextWayPoint);
            this->totalWayPoints++;
        }
    }
}

void VLC::VLCmobilityManager::stepMovement() {
    // Update the position
    this->nodePosition = {
            this->nodePosition.x + this->xStep,
            this->nodePosition.y + this->yStep,
            this->nodePosition.z + this->zStep,
            this->nodePosition.alpha,
            this->nodePosition.beta
    };
    this->calculateDirection();

    ev<<"Current position : ";
    printPosition(this->nodePosition);

    this->notifyChannel();

    // If it's more distant than the step keep moving
    if(distance(this->nodePosition, this->targetPosition) >= (this->linearVelocity*this->updateInterval/1000.0)){
        scheduleAt(simTime() + this->updateInterval, new cMessage());
    }else{
        if( this->currentWayPoint < this->totalWayPoints){
            this->calculateNextMovement();
            scheduleAt(simTime() + this->updateInterval, new cMessage());
        }
    }
}

void VLC::VLCmobilityManager::calculateNextMovement() {
    VLCwayPoint nextWayPoint = this->wayPoints[this->currentWayPoint++];
    this->targetPosition = nextWayPoint.position;
    this->linearVelocity = nextWayPoint.linearSpeed;

    //Calculate the distance vector, normalise it, scalar multiply it by the linear velocity, compute the x,y,z step at each interval
    vector3d distanceVector = {this->targetPosition.x - this->nodePosition.x, this->targetPosition.y - this->nodePosition.y, this->targetPosition.z - this->nodePosition.z};
    ev<<"Distance vector is:";
    printVector(distanceVector);

    ev<<"Current position : ";
    printPosition(this->nodePosition);

    ev<<"Target position : ";
    printPosition(this->targetPosition);

    vector3d normalised = normalise(distanceVector);
    vector3d linearVelocityVector = scalarMult3d(this->linearVelocity, normalised);

    this->xStep = linearVelocityVector.x * this->updateInterval/1000.0;
    this->yStep = linearVelocityVector.y * this->updateInterval/1000.0;
    this->zStep = linearVelocityVector.z * this->updateInterval/1000.0;

    ev<<"Linear velocity is : "<<this->linearVelocity<<" x: "<<this->xStep<<" y: "<<this->yStep<<" z: "<<this->zStep<<"\n";
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

void VLC::VLCmobilityManager::callFunction(std::string funName, std::string funArgs){
    if(funName == "START_POSITION"){
        this->setNodePosition(funArgs);
    }else if(funName == "WAYPOINTS"){
        this->parseWayPoints(funArgs);
    }else if(funName == "START_TIME"){
        this->initialDelay = std::stod(funArgs);
    }
}

