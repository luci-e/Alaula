/*
 * VLCtransmitter.h
 *
 *  Created on: Aug 19, 2017
 *      Author: casper
 */

#ifndef VLCTRANSMITTER_H_
#define VLCTRANSMITTER_H_

#include <VLCdevice.h>
#include <VLCpacket_m.h>
#include <map>
#include <string>

namespace VLC{
    class VLCtransmitter : public VLCdevice{
        protected:
            double lambertianOrder;
            std::map<std::string, double> currentTransmissionInfo;
            dataPacket lastPacket;

            void initialize() override;
            void handleMessage(cMessage *msg) override;

            void startTransmission(dataPacket *dataPacket);
            void stopTransmission();

            double getTransmissionTime(double packetLength, double dataRate);
            double getDataRate();

        public:
            VLCtransmitter(){};
            ~VLCtransmitter() {}
            double getLambertianOrder() const;
            std::map<std::string, double> getCurrentTransmissionInfo();
    };
    Define_Module(VLCtransmitter);
}



#endif /* VLCTRANSMITTER_H_ */
