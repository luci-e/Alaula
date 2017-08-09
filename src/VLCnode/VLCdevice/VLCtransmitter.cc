/*
 * VLCtransmitter.cc
 *
 *  Created on: Jul 30, 2017
 *      Author: casper
 */

#include <VLCdevice.h>
#include <VLCchannelMsg_m.h>

namespace VLC{
    class VLCtransmitter : public VLCdevice{
        protected:
            void initialize() override;
            void handleMessage(cMessage *msg) override;

        public:
            VLCtransmitter(){};
            ~VLCtransmitter(){};
    };
    Define_Module(VLCtransmitter);
}


void VLC::VLCtransmitter::initialize(){
    VLCdevice::initialize();
    this->deviceType = TRANSMITTER_DEVICE;
    scheduleAt(simTime() + 1000, new cMessage());
}

void VLC::VLCtransmitter::handleMessage(cMessage *msg){
    ev<<"Sending channel message\n";
    VLCchannelSignalBegin *csb = new VLCchannelSignalBegin();
    csb->setMessageType(CH_BEGIN_COMM_MSG);
    csb->setTransmitterNodeId(this->getId());
    csb->setPower(0.0);
    csb->setCarrierFreq(0.0);
    csb->setModulationType(0);
    send(csb, "channelPort$o");
    delete msg;
};



