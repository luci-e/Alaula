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

#include <VLCapp/VLCapp.h>
#include <VLCpacket_m.h>
#include <omnetpp.h>

using namespace VLC;

VLCapp::VLCapp() {
    // TODO Auto-generated constructor stub

}

VLCapp::~VLCapp() {
    // TODO Auto-generated destructor stub
}

void VLC::VLCapp::initialize() {
    scheduleAt(simTime() + 10, new cMessage());
}

void VLC::VLCapp::handleMessage(cMessage* msg) {
    dataPacket *newData = new dataPacket();

    newData->setMessageType(VLC_DATA_MSG);
    newData->setByteLength(this->packetSize);
    newData->setModulationType(PAM);
    newData->setModulationOrder(2);
    newData->setTransmissionPower(50.0);

    send(newData, "appGate$o");

    scheduleAt( simTime() + this->transmissionInterval, new cMessage() );
    delete msg;
}
