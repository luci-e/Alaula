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

#ifndef __VLC_VLCNETCONTROLLER_H_
#define __VLC_VLCNETCONTROLLER_H_

#include <omnetpp.h>
#include <deque>
#include <list>
#include <map>
#include <VLCpacket_m.h>
#include <VLCnetScheduler.h>
#include <VLCtransmitter.h>

namespace VLC{
    enum linkType : int{
        ANY_LINK = 0,
        VLC_LINK = 1,
        WIFI_LINK = 2
    };

    struct link{
        int transmitterAddress, destinationAddress;
        linkType type;
        cGate * gate;

        inline bool operator<(const link& l2) const{
            // l1 < l2 iff destinationAddress < l2.destinationAddress || l1.gate < l2.gate, l1.gate != l2.gate foreach l1, l2
            return (destinationAddress < l2.destinationAddress)?true:(gate<l2.gate);
        }

        inline bool operator==(const link& l2) const{
            return (destinationAddress == l2.destinationAddress && gate == l2.gate);
        }

        inline void operator=(const link& l2){
            transmitterAddress = l2.transmitterAddress;
            destinationAddress = l2.destinationAddress;
            type = l2.type;
            gate = l2.gate;
        }
    };

    struct transmitterInfo{
        int transmitterAddress, transmitterId;
        VLC::transmitterState tState;
        simtime_t lastBeaconTime;
        cGate * transmitterGate;

        inline bool operator<(const transmitterInfo& t2) const{
            if( transmitterAddress < t2.transmitterAddress ){
                return true;
            }
            return false;
        }

        inline bool operator==(const transmitterInfo& t2) const{
            return (transmitterAddress == t2.transmitterAddress);
        }
    };

    class VLCnetController : public cSimpleModule{
        friend class VLCnetScheduler;
        private:
            int address;
            bool useWiFiDl;
            bool WiFiAvailable;
            double beaconInterval = 50;

            void addVLCtransmitter(int transmitterAddress, int transmitterId, cGate * gate);

            void addLink(int transmitterAddress, int destinationAddress, linkType type, cGate * gate);
            void removeLink(int destinationAddress, cGate * gate);

            void sendBeacons();

            link getRoute(int destinationAddress);

            cGate * getTransmitterGate(int transmitterAddress);

        protected:
            mutable std::map<int, std::set<link>> linkTable;
            mutable std::map<int, transmitterInfo> transmitterTable;
            VLCnetScheduler *netScheduler;

            virtual void initialize(int stage);
            int numInitStages() const override;

            virtual void handleMessage(cMessage *msg);

        public:
            VLCnetController();
            ~VLCnetController();
            void registerTransmitter(int transmitterAddress, int transmitterId, cGate * gate);
    };
    Define_Module(VLCnetController);
}
#endif
