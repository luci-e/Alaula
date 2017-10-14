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

#include "VLCreceiverController.h"
#include <VLCpacket_m.h>
#include <VLCreceiver.h>

void VLC::VLCreceiverController::initialize(int stage){
    if(stage == 1){
        this->receiver = (VLCreceiver*) (gate("devicePort$o")->getPathEndGate()->getOwnerModule());
        this->WiFiAvailable = par("WiFiAvailable").boolValue();
        this->receiverAddress = this->receiver->address;
        this->receiverId = this->receiver->getId();
        this->scheduleBeaconCheck();
    }
}

int VLC::VLCreceiverController::numInitStages() const{
    return 2;
}

void VLC::VLCreceiverController::handleMessage(cMessage *msg){
    VLCpacket * pkt = (VLCpacket*) msg;

    switch(pkt->getMessageType()){
        case VLC_DATA_MSG:{
            dataPacket * dp = (dataPacket*) msg;
            if(dp->getDestinationAddress() == this->receiverAddress){
                // Forward it to the attached application
                send(msg, "appPort$o");
            }
            break;
        }
        case VLC_MAC_MSG:{
            if(this->WiFiAvailable){
                VLCMACMsg * MACMsg = (VLCMACMsg*) pkt;
                switch(MACMsg->getMACCode()){
                    case BEACON_MSG:{
                        this->lastBeaconTime = simTime();
                        this->scheduleBeaconCheck();

                        VLCMACMsg* macMsg = (VLCMACMsg*) msg;
                        if(this->receiver->currentTransmitterAddress != macMsg->getTransmitterNodeAddress()){
                            this->receiver->currentTransmitterAddress = macMsg->getTransmitterNodeAddress();

                            ev<<"Plz subscribe me to "<<this->receiver->currentTransmitterAddress<<"\n";

                            // We know it can only receive beacon messages
                            VLCMACMsg * subscribeMsg = new VLCMACMsg();
                            subscribeMsg->setMessageType(VLC_MAC_MSG);
                            subscribeMsg->setMACCode(SUBSCRIBE_MSG);
                            subscribeMsg->setTransmitterNodeAddress(macMsg->getTransmitterNodeAddress());
                            subscribeMsg->setReceiverNodeAddress(this->receiverAddress);

                            send(subscribeMsg, "wirelessPort$o");
                        }
                        delete msg;
                        break;
                    }

                    case UNSUBSCRIBE_MSG:{
                        send(msg, "wirelessPort$o");
                        break;
                    }
                }
            }
            break;
        }

        case VLC_CTRL_MSG:{
            VLCctrlMsg * ctrlMsg = (VLCctrlMsg*) msg;
            switch(ctrlMsg->getCtrlCode()){
                case CHECK_BEACON:{
                    if((this->receiver->currentTransmitterAddress != -1) && ((simTime()-this->lastBeaconTime).dbl() > this->beaconInterval)){
                        this->unsubscribeFromCurrent();
                    }
                }
            }
            break;
            delete msg;
        }
    }
}

void VLC::VLCreceiverController::unsubscribeFromCurrent() {
    Enter_Method("unsubscribeFromCurrent()");
    if(this->WiFiAvailable){
        VLCMACMsg * unsubscribeMsg = new VLCMACMsg();
        unsubscribeMsg->setMessageType(VLC_MAC_MSG);
        unsubscribeMsg->setMACCode(UNSUBSCRIBE_MSG);
        unsubscribeMsg->setTransmitterNodeAddress(this->receiver->currentTransmitterAddress);
        unsubscribeMsg->setReceiverNodeAddress(this->receiverAddress);
        ev<<"Plz unsubscribe me from "<<this->receiver->currentTransmitterAddress<<"\n";
        this->receiver->currentTransmitterAddress = -1;

        take(unsubscribeMsg);
        send(unsubscribeMsg, "wirelessPort$o");
    }
}

void VLC::VLCreceiverController::scheduleBeaconCheck() {
    VLCctrlMsg * ctrlMsg = new VLCctrlMsg();
    ctrlMsg->setMessageType(VLC_CTRL_MSG);
    ctrlMsg->setCtrlCode(CHECK_BEACON);
    scheduleAt(simTime() + this->beaconInterval*2, ctrlMsg);
}
