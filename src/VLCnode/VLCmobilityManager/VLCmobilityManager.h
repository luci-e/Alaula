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

#ifndef VLCMOBILITYMANAGER_H_
#define VLCMOBILITYMANAGER_H_

#include <omnetpp.h>
#include <csimulation.h>
#include <VLCmobilityMsg_m.h>
#include <VLCcommons.h>


// The ids for the self messages
#define STEP_TRANSLATION 0
#define STEP_ROTATION 1

namespace VLC {
    // Forward declarations
    class VLCchannel;
    class VLCdevice;

    class VLCmobilityManager: public ::cSimpleModule {
        protected:
            int nodeId;
            VLCnodePosition nodePosition;
            VLCnodeDirection nodeDirection;

            VLCnodePosition targetPosition;
            double speed;
            double angularSpeed;

            // The global VLCchannel
            VLCchannel* channel;

            // The time tick the position gets updated in ms
            double updateInterval = 100;

            void calculateDirection();

            void initialize();
            virtual void handleMessage(cMessage *msg) = 0;

        public:
            virtual void moveNode() = 0;
            void setTargetCoordinates(double x, double y, double z, double speed);

            virtual void rotateNode() = 0;
            void setTargetAngle(double alpha, double beta, double angularSpeed);

            void setNodePosition(VLCnodePosition nodePosition);
            void setNodePosition(double x, double y, double z, double alpha,
                    double beta);

            const VLCnodePosition getNodePosition() const;
            void setNodeId(int nodeId);

            const VLCnodeDirection getNodeDirection() const;
    };
}


#endif /* VLCMOBILITYMANAGER_H_ */

