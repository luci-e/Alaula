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

#include <VLCchannel.h>
#include <VLCdevice.h>
#include <cgate.h>
#include <cchannel.h>


void VLC::VLCchannel::initialize(){};
void VLC::VLCchannel::handleMessage(cMessage *msg){};

VLC::VLCchannel::VLCchannel() {
    // TODO Auto-generated constructor stub

}

VLC::VLCchannel::~VLCchannel() {
    // TODO Auto-generated destructor stub
}

void VLC::VLCchannel::addDevice(int deviceId, VLC::VLCdevice* device, cGate* deviceGate) {
    this->VLCdevices.insert(this->VLCdevices.begin(), std::pair<int, VLCdevice*>(deviceId, device));
    setGateSize("deviceIn", gateSize("deviceIn")+1);
    cIdealChannel *c = cIdealChannel::create(VLC::randomString(16));
    deviceGate->connectTo(gate("deviceIn", gateSize("deviceIn")-1), c);
    c->callInitialize();
}

std::list<VLC::VLCdevViewInfo>* VLC::VLCchannel::devicesInFoVOf(int deviceId) {
    VLCdevice *device;
    // Get the device
    if(this->VLCdevices.find(deviceId) != VLCdevices.end()){
        device = this->VLCdevices[deviceId];
    }else{ return NULL; }

    std::list <VLC::VLCdevViewInfo> *deviceList = new std::list<VLC::VLCdevViewInfo>();

    for( auto& idDev : this->VLCdevices ){
        int currentId = idDev.first;
        VLCdevice *currentDevice = idDev.second;

        if(currentId != deviceId){
            VLCdevViewInfo dvi = devsPerspective(device, currentDevice);
            if( dvi.seeEachOther){
                deviceList->push_back(dvi);
            }

        }
    }

    return deviceList;
}

VLC::VLCdevViewInfo VLC::VLCchannel::devsPerspective(VLCdevice* device1, VLCdevice* device2){
    VLCnodePosition dev1Position = device1->getNodePosition();
    VLCnodeDirection dev1Direction = device2->getNodeDirection();
    double dev1FoV = device1->getSemiAngle();

    VLCnodePosition dev2Position = device2->getNodePosition();
    VLCnodeDirection dev2Direction = device2->getNodeDirection();
    double dev2FoV = device2->getSemiAngle();

    VLCdevViewInfo devsPer;
    devsPer.device1 = device1->getId();
    devsPer.device2 = device2->getId();

    devsPer.distance = distance(dev1Position, dev2Position);

    // Calculate if the second device is in the FoV of the first one
    vector3d distanceVector = {dev2Position.x-dev1Position.x, dev2Position.y-dev1Position.y, dev2Position.z-dev1Position.z};
    vector3d normalisedDistance = normalise(distanceVector);

    devsPer.angle1 = acos(dotProduct3d(dev1Direction, normalisedDistance));
    bool can1see2 =  devsPer.angle1  <= dev1FoV;

    // Do the same for the second device
    distanceVector = opposite(distanceVector);
    normalisedDistance = normalise(distanceVector);

    devsPer.angle2 = acos(dotProduct3d(dev2Direction, normalisedDistance));
    bool can2see1 = devsPer.angle2 <= dev2FoV;

    devsPer.seeEachOther = can1see2 && can2see1;

    return devsPer;
}

void VLC::VLCchannel::createConnection(int transmitterId, int receiverId) {
}

void VLC::VLCchannel::dropConnection(int transmitterId, int receiverId) {
}

void VLC::VLCchannel::notifyChange(int deviceId) {
}

// Connect the VLCchannel to the mobility manager through an ideal channel
void VLC::VLCchannel::addMobility(cGate* mobilityGate) {
    setGateSize("mobilityPort", gateSize("mobilityPort")+1);
    cIdealChannel *c = cIdealChannel::create(VLC::randomString(16));
    mobilityGate->connectTo(gate("mobilityPort", gateSize("mobilityPort")-1), c);
    c->callInitialize();
}
