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
#include <VLClineMobilityManager.h>
#include <math.h>

VLC::VLCdevice::~VLCdevice() {
    // TODO: cleanup
}

VLC::VLCdevice::VLCdevice(){
    // TODO: type of mobility manager must be a parameter
    this->mobilityManager = (VLCmobilityManager*) new VLClineMobilityManager();
}

VLC::VLCnodePosition VLC::VLCdevice::getNodePosition(){
    return this->mobilityManager->getNodePosition();
}

void VLC::VLCdevice::initialize() {
    this->channel = dynamic_cast<VLC::VLCchannel*> (cSimulation::getActiveSimulation()->getModuleByPath(VLC_CHANNEL_NAME));
    this->nodeId = this->getId();

    std::vector<double> devicePars = cStringTokenizer(par("devPars").stringValue()).asDoubleVector();

    // Set the position of the transmitter
    this->mobilityManager->setNodePosition(devicePars[0],
                                           devicePars[1],
                                           devicePars[2],
                                           devicePars[3],
                                           devicePars[4]);

    // Set the semiangle of the device
    this->semiAngle = devicePars[5];

    this->mobilityManager->setNodeId(nodeId);
}

VLC::VLCnodeDirection VLC::VLCdevice::getNodeDirection() {
    return this->mobilityManager->getNodeDirection();
}

double VLC::VLCdevice::getSemiAngle() const {
    return semiAngle;
}

int VLC::VLCdevice::getNodeId() const {
    return nodeId;
}
