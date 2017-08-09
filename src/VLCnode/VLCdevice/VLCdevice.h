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
            int deviceType;
            double semiAngle;
            VLCchannel* channel;
            VLCmobilityManager* mobilityManager;

            void initialize();
            virtual void handleMessage(cMessage *msg) = 0;


        public:
            VLCdevice();
            virtual ~VLCdevice();

            VLCnodePosition getNodePosition();
            VLCnodeDirection getNodeDirection();

            double getSemiAngle() const;
            void setSemiAngle(double semiAngle);
    };
}


#endif /* VLCDEVICE_H_ */
