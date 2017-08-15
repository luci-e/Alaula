/*
 * VLCdevice.h
 *
 *  Created on: Jul 30, 2017
 *      Author: casper
 */

#ifndef VLCDEVICE_H_
#define VLCDEVICE_H_

#include <omnetpp.h>
#include <VLCcommons.h>


#define TRANSMITTER_DEVICE 0
#define RECEIVER_DEVICE 1


namespace VLC{
    // Forward declarations
    class VLCchannel;
    class VLCmobilityManager;

    class VLCdevice : public ::cSimpleModule{

        protected:
            // The type of the device
            int deviceType;
            // The semiangle of the FoV of the device
            double semiAngle;
            // A pointer to the VLCchannel the device will use to communicate
            VLCchannel* channel;
            // A pointer to the mobilityManager of this device
            VLCmobilityManager* mobilityManager;

            void initialize();
            virtual void handleMessage(cMessage *msg) = 0;


        public:
            VLCdevice();
            virtual ~VLCdevice();

            // Returns a structure of type VLCnodePosition containing info about the node position and orientation
            VLCnodePosition getNodePosition();
            // Returns a unit vector pointing in the same direction as the device
            VLCnodeDirection getNodeDirection();

            double getSemiAngle() const;
            void setSemiAngle(double semiAngle);
            int getDeviceType() const;
};
}


#endif /* VLCDEVICE_H_ */
