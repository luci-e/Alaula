/*
 * VLCnoiseDevice.h
 *
 *  Created on: Aug 19, 2017
 *      Author: casper
 */

#ifndef VLCNOISEDEVICE_H_
#define VLCNOISEDEVICE_H_

#include <VLCdevice.h>
#include <VLCemitter.h>
#include <VLCpacket_m.h>

namespace VLC{
    class VLCnoiseDevice : public VLCdevice, public VLCemitter{
        protected:
            void initialize() override;
            void handleMessage(cMessage *msg) override;

            // Sets the noise power level to the specified value in dBm
            void setNoisePower(double noisePower);
        public:
            VLCnoiseDevice(){};
            ~VLCnoiseDevice() {}
    };
    Define_Module(VLCnoiseDevice);
}



#endif /* VLCNOISEDEVICE_H_ */
