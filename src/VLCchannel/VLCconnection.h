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

    // A connection equals another iff the transmitter and receiver are the same
    inline bool operator==(const VLCconnection &c2) const;

    // C1 is lt C2 iff (c1.transmitter < c2.transmitter) or ((c1.transmitter == c2.transmitter) and (c1.receiver < c2.receiver ))
    bool operator<(const VLCconnection &c2) const;

    // Add a new value to the SINR trend
    void addValue(VLC::VLCtimeSINR ts);

    // Compute the outcome of this transmission, returns true if it was successful false otherwise
    bool getOutcome();

    // Abort this connection
    void abortConnection() const;

};

} /* namespace VLC */

#endif /* VLCCONNECTION_H_ */
