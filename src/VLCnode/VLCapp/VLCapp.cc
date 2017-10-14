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
#include <ctime>
#include <cstdlib>
#include <Log.h>

using namespace VLC;

VLCapp::VLCapp() {}
VLCapp::~VLCapp() {}

void VLC::VLCapp::initialize() {
    if(par("type").doubleValue() == 1.0){
        this->destinationAddresses = cStringTokenizer(par("destinationAddresses").stringValue()).asDoubleVector();

        VLCctrlMsg * newPkt = new VLCctrlMsg();
        newPkt->setMessageType(VLC_CTRL_MSG);
        newPkt->setCtrlCode(NEW_PACKET);

        scheduleAt(simTime(), newPkt);
    }else{
        VLCpacket * logPkt = new VLCpacket();
        logPkt->setMessageType(-1);

        scheduleAt(simTime(), logPkt);
    }

    this->address = par("address");

    srand(time(NULL));

}

void VLC::VLCapp::handleMessage(cMessage* msg) {
    VLCpacket* pkt = (VLCpacket*) msg;

    switch(pkt->getMessageType()){
        case VLC_DATA_MSG:{
            ev<<"Received a packet for "<<this->address<<"\n";
            dataPacket *dp = (dataPacket*) msg;
            //double duration = simTime().dbl() - dp->getTransmissionStartTime();
            this->totalReceivedData += dp->getByteLength();
            //ev<<"Received a packet for "<<this->address<<" total data is "<<this->totalReceivedData<<"\n";
            delete msg;
            break;
        }

        case VLC_CTRL_MSG:{
            VLCctrlMsg * ctrl = (VLCctrlMsg*) pkt;
            switch(ctrl->getCtrlCode()){
                case NEW_PACKET:{
                    dataPacket *newData = new dataPacket();

                    newData->setMessageType(VLC_DATA_MSG);
                    newData->setByteLength(this->packetSize);
                    newData->setModulationType(VPPM);
                    newData->setDutyCycle(0.5);
                    newData->setTransmissionPower(1.0);
                    newData->setContent(this->getName());

                    int destAddress = (int) this->destinationAddresses[rand() % this->destinationAddresses.size()];
                    newData->setDestinationAddress(destAddress);

                    send(newData, "appGate$o", 0);

                    scheduleAt( simTime() + this->transmissionInterval, ctrl);
                    break;
                }
            }
            break;
        }

        default:{
            LOGN_(2)   << this->address << ";"\
                   << 0 << ";"\
                   << 0 << ";"\
                   << simTime().dbl()<< ";"\
                   << "Data" << ";"\
                   << this->totalReceivedData << ";"\
                   << 0 << ";"\
                   << 0 << ";"\
                   << 0 << ";"\
                   << 0 << ";"\
                   << 0;
            scheduleAt( simTime() + this->logUpdateInterval, pkt);
            break;
        }
    }
}
