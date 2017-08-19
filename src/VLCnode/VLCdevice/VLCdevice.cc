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

#include <VLCdevice.h>
#include <VLCchannel.h>
#include <cstringtokenizer.h>
#include <VLCmobilityManager.h>
#include <math.h>

VLC::VLCdevice::~VLCdevice() {
    // TODO: cleanup
}

VLC::VLCdevice::VLCdevice(){
    // TODO: type of mobility manager must be a parameter
}

// Returns a structure of type VLCnodePosition containing info about the node position and orientation
VLC::VLCnodePosition VLC::VLCdevice::getNodePosition(){
    return this->mobilityManager->getNodePosition();
}

void VLC::VLCdevice::initialize() {
    this->mobilityManager = (VLCmobilityManager*) this->getParentModule()->getSubmodule("mobilityManager");
    this->channel = dynamic_cast<VLC::VLCchannel*> (cSimulation::getActiveSimulation()->getModuleByPath(VLC_CHANNEL_NAME));

    std::vector<double> devicePars = cStringTokenizer(par("devPars").stringValue()).asDoubleVector();
    // Set the semiangle of the device
    this->semiAngle = devicePars[0];
    this->mobilityManager->setDevice(this);

    this->channel->addDevice(this, gate("channelPort$i"), gate("channelPort$o"));
    ev<<"Connected to channel: "<<channel->getFullName()<<"\n";
}

// Returns a unit vector pointing in the same direction as the device
VLC::VLCnodeDirection VLC::VLCdevice::getNodeDirection() {
    return this->mobilityManager->getNodeDirection();
}

double VLC::VLCdevice::getSemiAngle() const {
    return semiAngle;
}

void VLC::VLCdevice::setSemiAngle(double semiAngle) {
    this->semiAngle = semiAngle;
}

int VLC::VLCdevice::getDeviceType() const {
    return deviceType;
}
