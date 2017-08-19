/*
 * VLCtransmissionModels.cc
 *
 *  Created on: Aug 19, 2017
 *      Author: casper
 */

#include <VLCtransmissionModels.h>
#include <VLCcommons.h>
#include <list>
#include <map>
#include <string>
#include <math.h>
#include <time.h>

// returns true if the packet can be successfully transmitter, false otherwise
bool VLC::packetTransmitted(std::list<VLC::VLCtimeSINR> & SINRTrend, std::map<std::string, double> & transmissionInfo){
    switch((int) transmissionInfo["modulationType"]){
        case VPPM:{
            return VLC::PERVPPM(VLC::averageSINR(SINRTrend), transmissionInfo);
        }
        case PAM:{
            return VLC::PERPAM(VLC::averageSINR(SINRTrend), transmissionInfo);
        }
    }
    return false;
}

// Calculates the average SINR from the trend
double VLC::averageSINR(std::list<VLC::VLCtimeSINR> & SINRTrend){
    double totalSINR = 0.0, totalTime = 0.0;
    double lastTime = SINRTrend.begin()->time.dbl();

    std::list<VLC::VLCtimeSINR>::iterator val = SINRTrend.begin();
    std::advance(val, 1);

    for(; val != SINRTrend.end(); val ++){
        double diff = ( val->time.dbl() - lastTime);
        totalSINR += val->SINR * diff;
        totalTime += diff;
    }

    return totalSINR / totalTime;
}

// Bit Error Rate for Variable Pulse Position Modulation
double VLC::BERVPPM(double avgSINR, std::map<std::string, double> & transmissionInfo) {
    double x;
    double alpha = transmissionInfo["dutyCycle"];
    double beta = 1; // Another magic value

    if (alpha <= 0.5)
        x = std::sqrt(avgSINR / (2 * beta * alpha));
    else
        x = std::sqrt(avgSINR * (1 - alpha) / (2 * beta * alpha * alpha));

    // Calculate BER = Q(x)
    // Q-function is the tail probability of the standard normal distribution
    double Q = 1 - phi(x);
    return Q;
}

// Symbol Error Rate for Pulse Amplitude Modulation
double VLC::SERPAM(double avgSINR, std::map<std::string, double> & transmissionInfo) {
    int modulationOrder = (int) transmissionInfo["modulationOrder"];

    double x = std::sqrt(avgSINR/(modulationOrder - 1));
    double SER = ((2*(modulationOrder - 1)) / modulationOrder)*( 1 - phi(x));

    return SER;
}

// Packet Error Rate for Variable Pulse Position Modulation returns true if the randomly generated number is less than the PER
bool VLC::PERVPPM(double avgSINR, std::map<std::string, double> & transmissionInfo) {
    double PER = 1 - std::pow((1 - VLC::BERVPPM(avgSINR, transmissionInfo)), 8 * transmissionInfo["packetLength"]);

    srand(time(0));
    double prob = (double)rand() / RAND_MAX;

    return (prob < PER);
}

// Packet Error Rate for Pulse Amplitude Modulation returns true if the randomly generated number is less than the PER
bool VLC::PERPAM(double avgSINR, std::map<std::string, double> & transmissionInfo) {
    double PER = 1 - std::pow( (1 - VLC::SERPAM(avgSINR, transmissionInfo)), ((8 * transmissionInfo["packetLength"]) / std::log2(transmissionInfo["modulationOrder"])));

    srand(time(0));
    double prob = (double)rand() / RAND_MAX;

    return (prob < PER);
}


