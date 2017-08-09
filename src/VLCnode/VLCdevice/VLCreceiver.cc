/*
 * VLCtransmitter.cc
 *
 *  Created on: Jul 30, 2017
 *      Author: casper
 */

#include <VLCdevice.h>

namespace VLC{
    class VLCreceiver : public VLCdevice{
        protected:
            void initialize() override;
            void handleMessage(cMessage *msg) override;

        public:
            VLCreceiver(){};
            ~VLCreceiver(){};

            double getSemiAngle() const;
            void setSemiAngle(double semiAngle);

    };
    Define_Module(VLCreceiver);
}


void VLC::VLCreceiver::initialize(){
    VLCdevice::initialize();
    this->deviceType = RECEIVER_DEVICE;
}

void VLC::VLCreceiver::handleMessage(cMessage *msg){
    ev<<"Received a message from the VLCchannel\n";
    delete msg;
};
