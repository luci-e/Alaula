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

namespace VLC{
    // returns true if the packet can be successfully transmitter, false otherwise
    bool packetTransmitted(std::vector<VLC::VLCtimeSINR> & SINRTrend, std::map<std::string, double> & transmissionInfo);

    // Calculates the average SINR from the trend
    double averageSINR(std::vector<VLC::VLCtimeSINR> & SINRTrend);

    // Bit Error Rate for Variable Pulse Position Modulation
    double BERVPPM(double avgSINR, std::map<std::string, double> & transmissionInfo);

    // Symbol Error Rate for Pulse Amplitude Modulation
    double SERPAM(double avgSINR, std::map<std::string, double> & transmissionInfo);

    // Packet Error Rate for Variable Pulse Position Modulation returns true if the randomly generated number is less than the PER
    bool PERVPPM(double avgSINR, std::map<std::string, double> & transmissionInfo);

    // Packet Error Rate for Pulse Amplitude Modulation returns true if the randomly generated number is less than the PER
    bool PERPAM(double avgSINR, std::map<std::string, double> & transmissionInfo);
}


#endif /* VLCTRANSMISSIONMODELS_H_ */
