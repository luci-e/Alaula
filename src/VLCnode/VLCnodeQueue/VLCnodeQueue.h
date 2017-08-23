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

#ifndef VLCNODEQUEUE_H_
#define VLCNODEQUEUE_H_

#include <queue>
#include <omnetpp.h>
#include <VLCpacket_m.h>

namespace VLC{

    enum transmitterState{
        TRANSMITTING = 0,
        WAITING = 1
    };

    class VLCnodeQueue : public ::cSimpleModule{


    std::queue<dataPacket*> packetQueue;
    transmitterState currentState = WAITING;


    private:
        void sendNextPacket();
        void transmissionSuccessful();
        void transmissionAborted();

    protected:
        void initialize();
        virtual void handleMessage(cMessage *msg);
        virtual void finish();

    public:
        VLCnodeQueue();
        virtual ~VLCnodeQueue();
    };

    Define_Module(VLCnodeQueue);
}



#endif /* VLCNODEQUEUE_H_ */
