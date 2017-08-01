/*
 * VLCtransmitter.cc
 *
 *  Created on: Jul 30, 2017
 *      Author: casper
 */

#include <VLCdevice.h>

namespace VLC{
    class VLCtransmitter : public VLCdevice{
        protected:
            void initialize() override;
            void handleMessage(cMessage *msg) override;

        public:
            VLCtransmitter(){};
            ~VLCtransmitter(){};

            double getSemiAngle() const;
            void setSemiAngle(double semiAngle);

    };

}

Define_Module(VLC::VLCtransmitter);

void VLC::VLCtransmitter::initialize(){
    VLCdevice::initialize();
    this->deviceType = TRANSMITTER_DEVICE;
}

void VLC::VLCtransmitter::handleMessage(cMessage *msg){};

double VLC::VLCtransmitter::getSemiAngle() const {
    return semiAngle;
}

void VLC::VLCtransmitter::setSemiAngle(double semiAngle) {
    this->semiAngle = semiAngle;
}
