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

#ifndef __VLC_VLCRECEIVERCONTROLLER_H_
#define __VLC_VLCRECEIVERCONTROLLER_H_

#include <omnetpp.h>
#include <VLCreceiver.h>

namespace VLC{
    class VLCreceiverController : public cSimpleModule{
        public:
            int receiverAddress, receiverId;
            bool WiFiAvailable;

        protected:

            VLCreceiver * receiver;
            simtime_t lastBeaconTime;
            double beaconInterval = 50;

            virtual void initialize(int stage);
            int numInitStages() const override;

            void unsubscribeFromCurrent();
            void scheduleBeaconCheck();

            virtual void handleMessage(cMessage *msg);
    };

    Define_Module(VLCreceiverController);
}

#endif
