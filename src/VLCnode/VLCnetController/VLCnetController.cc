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

#include "VLCnetController.h"
#include <VLCreceiverController.h>
#include <VLCnetScheduler.h>

void VLC::VLCnetController::initialize(int stage){
    if( stage == 0){
        this->address = par("address");
        this->WiFiAvailable = par("WiFiAvailable").boolValue();
        this->useWiFiDl = par("useWiFiDl").boolValue();
    }else if(stage == 2){
        if(this->WiFiAvailable){
            int numDevices = gateSize("wirelessPort");
            for(int i = 0; i < numDevices; i++){
                cGate* g = gate("wirelessPort$o", i);
                VLCreceiverController * rctrl = (VLCreceiverController*) (g->getPathEndGate()->getOwnerModule());
                this->addLink(this->address, rctrl->receiverAddress, WIFI_LINK, g);
                ev<<"Receiver address is "<<rctrl->receiverAddress<<"\n";
                this->netScheduler->addDestination(rctrl->receiverAddress);
            }

            scheduleAt(simTime() + 1, new cMessage());
        }
    }
}

int VLC::VLCnetController::numInitStages() const{
    return 3;
}


void VLC::VLCnetController::addVLCtransmitter(int transmitterAddress, int transmitterId, cGate* gate) {
    this->transmitterTable[transmitterAddress]= (transmitterInfo){transmitterAddress, transmitterId, READY, simTime() - this->beaconInterval, gate};
}

void VLC::VLCnetController::addLink(int transmitterAddress, int destinationAddress, linkType type, cGate * gate){
    std::set<link> &linkSet = this->linkTable[destinationAddress];

    // Remove any previous VLC link. THERE CAN BE ONLY ONE!
    if(type == VLC_LINK){
        for(auto &link : linkSet){
            if( link.destinationAddress == destinationAddress && link.type == VLC_LINK){
                linkSet.erase(link);
                break;
            }
        }
    }

    linkSet.insert((link){transmitterAddress, destinationAddress, type, gate});
}

void VLC::VLCnetController::removeLink(int destinationAddress, cGate * gate){
    try{
        this->linkTable.at(destinationAddress).erase((link){-1, destinationAddress, ANY_LINK, gate});
    }catch(const std::out_of_range& oor){
        ev<<"Meh\n";
    }
}

cGate * VLC::VLCnetController::getTransmitterGate(int transmitterAddress){
    return this->transmitterTable[transmitterAddress].transmitterGate;
}

void VLC::VLCnetController::handleMessage(cMessage *msg)
{
    if(!msg->isSelfMessage()){
        VLCpacket * VLCmsg = (VLCpacket*) msg;
        switch(VLCmsg->getMessageType()){
            case VLC_DATA_MSG:{
                this->netScheduler->addPacket((dataPacket*)msg);
                this->netScheduler->processNextPacket();
                return;
            }
            case VLC_CTRL_MSG:{
                VLCctrlMsg * ctrlMsg = (VLCctrlMsg*) VLCmsg;
                switch(ctrlMsg->getCtrlCode()){
                    case TRANSMISSION_END:{
                        this->transmitterTable[ctrlMsg->getNodeAddress()].tState = READY;
                        this->netScheduler->processNextPacket();
                        break;
                    }
                }
            }
            case VLC_MAC_MSG:{
                VLCMACMsg * MACMsg = (VLCMACMsg*) VLCmsg;
                switch(MACMsg->getMACCode()){
                    case SUBSCRIBE_MSG:{
                        ev<<"Yo "<<MACMsg->getReceiverNodeAddress()<<" I subscribed you to "<<MACMsg->getTransmitterNodeAddress()<<"\n";
                        this->addLink(MACMsg->getTransmitterNodeAddress(), MACMsg->getReceiverNodeAddress(), VLC_LINK, this->getTransmitterGate(MACMsg->getTransmitterNodeAddress()));
                        break;
                    }
                    case UNSUBSCRIBE_MSG:{
                        ev<<"Yo "<<MACMsg->getReceiverNodeAddress()<<" I unsubscribed you from "<<MACMsg->getTransmitterNodeAddress()<<"\n";
                        this->removeLink(MACMsg->getReceiverNodeAddress(), this->getTransmitterGate(MACMsg->getTransmitterNodeAddress()));
                        break;
                    }
                }
            }
        }
    }else{
        if(this->WiFiAvailable){
            this->sendBeacons();
            scheduleAt(simTime() + this->beaconInterval, new cMessage());
        }
    }
    delete msg;
}

VLC::link VLC::VLCnetController::getRoute(int destinationAddress) {
    ev<<"Getting route for "<<destinationAddress<<"\n";
    std::set<link> linkSet = this->linkTable[destinationAddress];
    link WiFiLink = {-1, -1, ANY_LINK, NULL};
    link VLClink = {-1, -1, ANY_LINK, NULL};

    for(auto& l: linkSet){
        ev<<"Link tx: "<<l.transmitterAddress<<" rx: "<<l.destinationAddress<<" link Type: "<<l.type<<"\n";
        if(l.type == WIFI_LINK){
            WiFiLink = l;
        }else{
            VLClink = l;
        }
    }

    if( (VLClink.destinationAddress == -1) && this->useWiFiDl){
        return WiFiLink;
    }else{
        return VLClink;
    }
}

VLC::VLCnetController::VLCnetController() {
    this->netScheduler = new VLCnetScheduler(this);
}

VLC::VLCnetController::~VLCnetController() {
    delete this->netScheduler;
}

void VLC::VLCnetController::sendBeacons() {
    for(auto& tr : this->transmitterTable){
        transmitterInfo tInfo = tr.second;
        if(tInfo.tState == READY){
            if( (simTime() - tInfo.lastBeaconTime).dbl() >= this->beaconInterval){
                VLCBeaconMsg * beaconMsg = new VLCBeaconMsg();
                beaconMsg->setMessageType(VLC_MAC_MSG);
                beaconMsg->setMACCode(BEACON_MSG);
                beaconMsg->setTransmitterNodeAddress(tInfo.transmitterAddress);
                beaconMsg->setModulationType(VPPM);
                beaconMsg->setTransmissionPower(1.0);
                beaconMsg->setByteLength(16.0);
                tInfo.lastBeaconTime = simTime();
                tInfo.tState = BUSY;
                send(beaconMsg, tInfo.transmitterGate);
            }
        }
    }
}

void VLC::VLCnetController::registerTransmitter(int transmitterAddress, int transmitterId, cGate* gate) {
    this->addVLCtransmitter(transmitterAddress, transmitterId, gateHalf(gate->getBaseName(), cGate::OUTPUT, gate->getIndex()));
}
