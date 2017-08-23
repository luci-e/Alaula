//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

#include <VLClineMobilityManager.h>
#include <VLCmobilityManager.h>
#include <VLCchannel.h>
#include <VLCmobilityMsg_m.h>
#include <VLCpacket_m.h>
#include <VLCcommons.h>
#include <math.h>
#include <string>

VLC::VLClineMobilityManager::VLClineMobilityManager() {}

VLC::VLClineMobilityManager::~VLClineMobilityManager() {}

void VLC::VLClineMobilityManager::initialize() {
    VLCmobilityManager::initialize();
    std::vector<double> mobilityPars = cStringTokenizer(par("mobilityPars").stringValue()).asDoubleVector();

    if(mobilityPars.size() == 13){
        scheduleAt(simTime() + mobilityPars[10], new cMessage("Started moving!"));

        // The linear velocity is the 7th parameter
        this->linearVelocity = mobilityPars[11];

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

        // The angular velocity is the 12th parameter
        double angularVelocity = mobilityPars[12];

        // And it's a bit more complicated than i thought so maybe later
        double angle = acos(dotProduct3d(this->nodeDirection, calculateVersor(this->targetPosition.alpha, this->targetPosition.beta)));
    }
}

void VLC::VLClineMobilityManager::handleMessage(cMessage* cMsg){
    delete cMsg;
    this->stepMovement();
}


void VLC::VLClineMobilityManager::stepMovement(){
    // Update the position
    this->nodePosition = {
            this->nodePosition.x + this->xStep,
            this->nodePosition.y + this->yStep,
            this->nodePosition.z + this->zStep,
            this->nodePosition.alpha,
            this->nodePosition.beta
    };
    this->calculateDirection();

    //ev<<"Current position : ";
    //printPosition(this->nodePosition);

    this->notifyChannel();

    // If it's more distant than the step keep moving
    if(distance(this->nodePosition, this->targetPosition) > (this->linearVelocity*this->updateInterval/1000.0)){
        scheduleAt(simTime() + this->updateInterval, new cMessage());
    }
}

