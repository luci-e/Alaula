/*
 * VLCconstantNoiseController.h
 *
 *  Created on: Sep 7, 2017
 *      Author: casper
 */

#ifndef VLCCONSTANTNOISECONTROLLER_H_
#define VLCCONSTANTNOISECONTROLLER_H_

#include <omnetpp.h>
#include <VLCnoiseController.h>

namespace VLC {

class VLCconstantNoiseController : public VLCnoiseController{
    double noisePower;

    protected:
        bool stepNoise(double time);
        void initialize() override;

    public:
        VLCconstantNoiseController();
        ~VLCconstantNoiseController();
    };

    Define_Module(VLCconstantNoiseController);


} /* namespace VLC */

#endif /* VLCCONSTANTNOISECONTROLLER_H_ */
