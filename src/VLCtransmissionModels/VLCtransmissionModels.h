/*
 * VLCtransmissionModels.h
 *
 *  Created on: Aug 19, 2017
 *      Author: casper
 */

#ifndef VLCTRANSMISSIONMODELS_H_
#define VLCTRANSMISSIONMODELS_H_

#include <vector>
#include <map>
#include <string>
#include <VLCcommons.h>
#include <VLCconnection.h>

namespace VLC{
    // returns true if the packet can be successfully transmitter, false otherwise
    bool packetTransmitted(VLCconnection* conn);

    // Calculates the average SINR from the trend
    double averageSINR(std::vector<VLC::VLCtimeSINR> & SINRTrend);

    // Bit Error Rate for Variable Pulse Position Modulation
    double BERVPPM(VLCconnection* conn);

    // Symbol Error Rate for Pulse Amplitude Modulation
    double SERPAM(VLCconnection* conn);

    // Packet Error Rate for Variable Pulse Position Modulation returns true if the randomly generated number is less than the PER
    bool PERVPPM(VLCconnection* conn);

    // Packet Error Rate for Pulse Amplitude Modulation returns true if the randomly generated number is less than the PER
    bool PERPAM(VLCconnection* conn);
}


#endif /* VLCTRANSMISSIONMODELS_H_ */
