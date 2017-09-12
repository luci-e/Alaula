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

    struct VLCwayPoint{
        VLCnodePosition position;
        double linearSpeed;
    };

    class VLCmobilityManager: public ::cSimpleModule {
        protected:
            // The device that this moblityManager manages
            VLCdevice * device;
            // The current nodePosition
            VLCnodePosition nodePosition;
            // The current node direction
            VLCnodeDirection nodeDirection;

            // The list of wayPoints that the node must touch
            std::vector<VLCwayPoint> wayPoints;
            int currentWayPoint = 0, totalWayPoints = 0;

            // The target position at which the node will arrive at the end of the movement
            VLCnodePosition targetPosition;

            double linearVelocity;
            double xStep, yStep, zStep;
            double alphaStep, betaStep;

            // The global VLCchannel
            VLCchannel* channel;

            // The time tick the position gets updated in ms
            double updateInterval = 10;
            double initialDelay = 0;

            // Calculates the versor of the device
            void calculateDirection();

            void initialize();
            void handleMessage(cMessage *msg);

            // Notifies the channel of a movement
            void notifyChannel();

            // Parse the file with the mobility parameters
            void parseMobilityFile(std::string mobilityFilePath);

            // Parse the string of waypoints into a list of waypoints
            void parseWayPoints(std::string wayPointString);

            // Calculates the values for the next movement
            void calculateNextMovement();

            // Call the function associated to the function name with fiven args
            void callFunction(std::string funName, std::string funArgs);


        public:
            void stepMovement();

            void setTargetCoordinates(double x, double y, double z);
            void setTargetAngle(double alpha, double beta);

            void setNodePosition(VLCnodePosition nodePosition);
            void setNodePosition(double x, double y, double z, double alpha, double beta);
            void setNodePosition(std::string nodePosition);

            const VLCnodePosition getNodePosition() const;
            void setDevice(VLCdevice * device);

            // Returns the unit vector pointing in the same direction as the device
            const VLCnodeDirection getNodeDirection() const;
    };

    Define_Module(VLCmobilityManager);
}


#endif /* VLCMOBILITYMANAGER_H_ */

