/*
 * VLCnetScheduler.h
 *
 *  Created on: Sep 25, 2017
 *      Author: casper
 */

#ifndef VLCNETSCHEDULER_H_
#define VLCNETSCHEDULER_H_

#include <queue>
#include <vector>
#include <map>
#include <VLCpacket_m.h>

namespace VLC {

class VLCnetController;

class VLCnetScheduler{
    protected:
        VLCnetController *netController;
        std::vector<int> destinations;
        int currentDestination = 0;

        int getNextServed();
        mutable std::map<int, std::queue<dataPacket*>> packetQueues;
        mutable std::queue<dataPacket*> NoWiFiPacketQueue;


    public:
        VLCnetScheduler(VLCnetController *controller);
        virtual ~VLCnetScheduler();

        void addPacket(dataPacket* packet);
        void processNextPacket();
        void processWithMAC();
        void processNoMAC();
        bool VLCbroadcast(dataPacket* packet);

        void addDestination(int destination);

};

} /* namespace VLC */

#endif /* VLCNETSCHEDULER_H_ */
