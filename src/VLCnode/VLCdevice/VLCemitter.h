/*
 * VLCemitter.h
 *
 *  Created on: Jul 30, 2017
 *      Author: casper
 */

#ifndef VLCEMITTER_H_
#define VLCEMITTER_H_

#include <omnetpp.h>
#include <VLCcommons.h>
#include <set>
#include <string>

namespace VLC{

    enum transmissionKeys : int{
        TRANSMISSION_POWER = 0,
        MODULATION_TYPE = 1,
        PACKET_LENGTH = 2,
        MODULATION_ORDER = 3,
        DUTY_CYCLE = 4
    };

    class VLCemitter{

        protected:
            double lambertianOrder;
            std::map<transmissionKeys, double> currentTransmissionInfo;

        public:
            VLCemitter();
            double getLambertianOrder() const;
            std::map<transmissionKeys, double> & getCurrentTransmissionInfo();
            double getEmitterPower();

    };
}

#endif /* VLCEMITTER_H_ */
