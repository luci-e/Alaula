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
            // The device that this moblityManager manages
            VLCdevice * device;
            // The current nodePosition
            VLCnodePosition nodePosition;
            // The current node direction
            VLCnodeDirection nodeDirection;

            // The target position at which the node will arrive at the end of the movement
            VLCnodePosition targetPosition;

            // The global VLCchannel
            VLCchannel* channel;

            // The time tick the position gets updated in ms
            double updateInterval = 10;

            // Calculates the versor of the device
            void calculateDirection();

            void initialize();
            virtual void handleMessage(cMessage *msg) = 0;

            // Notifies the channel of a movement
            void notifyChannel();

        public:
            virtual void stepMovement() = 0;

            void setTargetCoordinates(double x, double y, double z);
            void setTargetAngle(double alpha, double beta);

            void setNodePosition(VLCnodePosition nodePosition);
            void setNodePosition(double x, double y, double z, double alpha,
                    double beta);

            const VLCnodePosition getNodePosition() const;
            void setDevice(VLCdevice * device);

            // Returns the unit vector pointing in the same direction as the device
            const VLCnodeDirection getNodeDirection() const;
    };
}


#endif /* VLCMOBILITYMANAGER_H_ */

