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

#include <VLCnodeQueue.h>
#include <VLCpacket_m.h>

using namespace VLC;

VLCnodeQueue::VLCnodeQueue() {}
VLCnodeQueue::~VLCnodeQueue() {}

void VLCnodeQueue::finish() {
    for(int i = 0; i < this->packetQueue.size(); i++){
        VLCpacket* packet = this->packetQueue.front();
        this->packetQueue.pop();
        delete packet;
    }
}

void VLCnodeQueue::initialize() {
}

void VLCnodeQueue::handleMessage(cMessage* msg) {
    if(!msg->isSelfMessage()){
        if( msg->getArrivalGate() == gate("devicePort$i")){
            VLCctrlMsg* ctrlMsg = (VLCctrlMsg*) msg;
            switch( ctrlMsg->getCtrlCode() ){
                case TRANSMISSION_DONE:{
                    this->transmissionSuccessful();
                    delete msg;
                    break;
                }

                case TRANSMISSION_ABORTED:{
                    this->transmissionAborted();
                    delete msg;
                    break;
                }
            }
        }else{
            dataPacket* newPacket = (dataPacket*) msg;
            this->packetQueue.push(newPacket);

            if( this->currentState == WAITING){
                this->currentState = TRANSMITTING;
                this->sendNextPacket();
            }
        }
    }

}


void VLC::VLCnodeQueue::sendNextPacket() {
    if( this->packetQueue.size() > 0){
        dataPacket *nextPacket = this->packetQueue.front();
        this->packetQueue.pop();
        this->currentState = TRANSMITTING;
        send(nextPacket, "devicePort$o");
    }
}

void VLC::VLCnodeQueue::transmissionSuccessful() {
    ev<<"Transmission done\n";
    this->currentState = WAITING;
    this->sendNextPacket();
}

void VLC::VLCnodeQueue::transmissionAborted() {
    ev<<"Transmission aborted\n";
    this->currentState = WAITING;
    this->sendNextPacket();
}


