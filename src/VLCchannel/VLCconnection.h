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

    void abortConnection() const;

    struct comparator{
        bool operator()(const VLCconnection& c1, const VLCconnection& c2){
            if(c1.transmitter->getId() < c2.transmitter->getId()){
                return true;
            }

            if(c1.transmitter->getId() == c2.transmitter->getId()){
                return c1.receiver->getId() < c2.receiver->getId();
            }

            return false;
        }
    };
};

} /* namespace VLC */

#endif /* VLCCONNECTION_H_ */
