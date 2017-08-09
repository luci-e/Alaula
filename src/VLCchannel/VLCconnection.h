/*
 * VLCconnection.h
 *
 *  Created on: Aug 8, 2017
 *      Author: casper
 */

#ifndef VLCCONNECTION_H_
#define VLCCONNECTION_H_

#include <VLCcommons.h>
#include <VLCdevice.h>
#include <list>

namespace VLC {

class VLCconnection {
public:
    VLCdevice const *transmitter, *receiver;
    std::list<VLC::VLCtimeSINR> SINRTrend;

    VLCconnection(VLCdevice * transmitter, VLCdevice * receiver);
    virtual ~VLCconnection();

    bool operator == (const VLCconnection &c2);

    void addValue(VLC::VLCtimeSINR ts);
    bool getOutcome();
};

} /* namespace VLC */

#endif /* VLCCONNECTION_H_ */
