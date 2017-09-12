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
#include <set>

namespace VLC{
    // Forward declarations
    class VLCchannel;
    class VLCmobilityManager;
    class VLCconnection;

    enum VLCdeviceType : int{
        TRANSMITTER_DEVICE = 0,
        RECEIVER_DEVICE = 1,
        BLOCKING_DEVICE = 2,
        NOISE_DEVICE = 3
    };

    class VLCdevice : public ::cSimpleModule{

        protected:
            // The type of the device
            VLC::VLCdeviceType deviceType;
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
            VLC::VLCdeviceType getDeviceType() const;
};
}


#endif /* VLCDEVICE_H_ */
