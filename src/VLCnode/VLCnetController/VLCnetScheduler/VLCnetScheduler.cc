/*
 * VLCnetScheduler.cc
 *
 *  Created on: Sep 25, 2017
 *      Author: casper
 */

#include <VLCnetScheduler.h>
#include <VLCnetController.h>
#include <queue>
#include <map>

namespace VLC {

    VLCnetScheduler::VLCnetScheduler(VLCnetController *controller) {
        this->netController = controller;
    }

    VLCnetScheduler::~VLCnetScheduler() {
        // TODO Auto-generated destructor stub
    }

    void VLCnetScheduler::addPacket(dataPacket* packet) {
        if(this->netController->WiFiAvailable){
            int destinationAddress = packet->getDestinationAddress();
            this->packetQueues[destinationAddress].push(packet);
        }else{
            this->NoWiFiPacketQueue.push(packet);
        }
    }

    void VLCnetScheduler::processNextPacket() {
        // Holy fairness Batman, process the packets in a round Robin way!
        if(this->netController->WiFiAvailable){
            this->processWithMAC();
        }else{
            this->processNoMAC();
        }
    }

    void VLCnetScheduler::processWithMAC() {
        int nextServed = this->getNextServed();
        for(int i = 0; i < (int) this->destinations.size(); i++){
           // Fetch the queue associated with the destination
           std::queue<dataPacket*> & currentQueue = this->packetQueues[nextServed+i];
           if(!currentQueue.empty()){
               dataPacket *pkt = currentQueue.front();
               int destinationAddress = pkt->getDestinationAddress();
               link pktLink = this->netController->getRoute(destinationAddress);

               // If there is a route to the address
               if(pktLink.destinationAddress != -1){
                   ev<<"There is a route for "<<pktLink.destinationAddress<<"\n";
                   // If it's not a WIFI_LINK check whether it should be sending a beacon
                   if(pktLink.type != WIFI_LINK){
                       transmitterInfo& tInfo  = this->netController->transmitterTable[pktLink.transmitterAddress];
                       // If the transmitter is in the READY state it can either transmit data or a beacon
                       if( tInfo.tState == READY){
                           ev<<"Transmitter is ready \n";
                           // Reserve this VLC transmitter
                           tInfo.tState = BUSY;
                           if( (simTime() - tInfo.lastBeaconTime).dbl() >= this->netController->beaconInterval){
                               VLCBeaconMsg * beaconMsg = new VLCBeaconMsg();
                               beaconMsg->setMessageType(VLC_MAC_MSG);
                               beaconMsg->setMACCode(BEACON_MSG);
                               beaconMsg->setTransmitterNodeAddress(tInfo.transmitterAddress);
                               beaconMsg->setModulationType(VPPM);
                               beaconMsg->setTransmissionPower(1.0);
                               beaconMsg->setByteLength(16.0);
                               tInfo.lastBeaconTime = simTime();
                               this->netController->send(beaconMsg, tInfo.transmitterGate);
                           }else{
                               // RAPTOOOOORS
                               goto sendPacket;
                           }
                       }
                   }else{
                       if(!pktLink.gate->getChannel()->isBusy()){
                           sendPacket:
                               if(pktLink.type == WIFI_LINK && !this->netController->useWiFiDl){return;}
                               currentQueue.pop();
                               this->netController->send(pkt, pktLink.gate);
                       }
                   }
               }
           }
        }
    }

    void VLCnetScheduler::processNoMAC() {
        if(!this->NoWiFiPacketQueue.empty()){
            dataPacket *pkt = this->NoWiFiPacketQueue.front();
            if( this->VLCbroadcast(pkt)){
                this->NoWiFiPacketQueue.pop();
            };
        }
    }

    void VLCnetScheduler::addDestination(int destination) {
        this->destinations.push_back(destination);
    }

    int VLCnetScheduler::getNextServed() {
        int next = this->destinations[this->currentDestination];
        this->currentDestination = (this->currentDestination+1) % (int) this->destinations.size();
        return next;
    }

    bool VLCnetScheduler::VLCbroadcast(dataPacket* packet) {
        ev<<"This next packet is for "<<packet->getDestinationAddress()<<"\n";
        // This is terrible and I'll have to fix this

        bool everyoneReady = true;
        for(auto& t : this->netController->transmitterTable){
            everyoneReady &= (t.second.tState == READY);
        }

        if(everyoneReady){
            for(auto& t : this->netController->transmitterTable){
                t.second.tState = BUSY;
                cGate * g = t.second.transmitterGate;
                this->netController->send(packet->dup(), g);
            }
            delete packet;
            return true;
        }

        return false;

    }
} /* namespace VLC */

