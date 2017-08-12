/*
 * VLCtransmitter.cc
 *
 *  Created on: Jul 30, 2017
 *      Author: casper
 */

#include <VLCdevice.h>
#include <VLCchannelMsg_m.h>
#include <VLCmobilityManager.h>

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
    scheduleAt(simTime() + 500, new cMessage(NULL, 1));
}

void VLC::VLCtransmitter::handleMessage(cMessage *msg){

    switch(msg->getKind()){
        case 1:{
            ev<<"Sending channel message\n";
            VLCchannelSignalBegin *csb = new VLCchannelSignalBegin();
            csb->setMessageType(CH_BEGIN_COMM_MSG);
            csb->setTransmitterNodeId(this->getId());
            csb->setPower(0.0);
            csb->setCarrierFreq(0.0);
            csb->setModulationType(0);
            send(csb, "channelPort$o");
            scheduleAt(simTime()+500, new cMessage(NULL, 2));
            break;
        }
        case 2:{
            this->mobilityManager->moveNode();
            scheduleAt(simTime()+500, new cMessage(NULL, 3));
            break;
        }
        case 3:{
            VLCchannelSignalEnd *cse = new VLCchannelSignalEnd();
            cse->setTransmitterNodeId(this->getId());
            cse->setMessageType(CH_END_COMM_MSG);
            sendDelayed(cse, 1000.0, "channelPort$o");
            break;
        }
    }
    delete msg;
};



