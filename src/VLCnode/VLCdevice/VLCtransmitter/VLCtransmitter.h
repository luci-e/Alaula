/*
 * VLCtransmitter.h
 *
 *  Created on: Aug 19, 2017
 *      Author: casper
 */

#ifndef VLCTRANSMITTER_H_
#define VLCTRANSMITTER_H_

#include <VLCdevice.h>
#include <VLCemitter.h>
#include <VLCpacket_m.h>
#include <map>
#include <string>

namespace VLC{
    class VLCtransmitter : public VLCdevice, public VLCemitter{
        protected:
            dataPacket lastPacket;

            // A set holding the connection this transmitter is currently in
            mutable std::set<VLC::VLCconnection*> connectionStarts;

            void initialize() override;
            void handleMessage(cMessage *msg) override;

            void startTransmission(dataPacket *dataPacket);
            void stopTransmission();

            double getTransmissionTime(double packetLength, double dataRate);
            double getDataRate();

        public:
            VLCtransmitter(){};
            ~VLCtransmitter() {}

            void addConnectionStart(VLCconnection * connection);
            void removeConnectionStart(VLCconnection* connection);
            std::set<VLC::VLCconnection*>& getConnectionStarts();
};
    Define_Module(VLCtransmitter);
}



#endif /* VLCTRANSMITTER_H_ */
