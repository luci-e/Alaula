/*
 * VLCtransmissionModels.cc
 *
 *  Created on: Aug 19, 2017
 *      Author: casper
 */

#include <VLCtransmissionModels.h>
#include <VLCpacket_m.h>
#include <VLCcommons.h>
#include <vector>
#include <map>
#include <string>
#include <math.h>
#include <time.h>

// returns true if the packet can be successfully transmitter, false otherwise
bool VLC::packetTransmitted(std::vector<VLC::VLCtimeSINR> & SINRTrend, std::map<std::string, double> & transmissionInfo){
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
double VLC::averageSINR(std::vector<VLC::VLCtimeSINR> & SINRTrend){
    double totalSINR = 0.0, totalTime = 0.0;
    double lastTime = SINRTrend.begin()->time;

    std::vector<VLC::VLCtimeSINR>::iterator val = SINRTrend.begin();
    //ev<<"SINR: "<<val->SINR<<"time: "<<val->time<<"\n";
    std::advance(val, 1);


    for(; val != SINRTrend.end(); val++){
        //ev<<"SINR: "<<val->SINR<<"time: "<<val->time<<"\n";
        double diff = ( val->time - lastTime);
        totalSINR += val->SINR * diff;
        totalTime += diff;
        lastTime = val->time;
    }


    //ev<<"TotalSINR: "<<totalSINR<<" totalTime: "<<totalTime<<"\n";
    //ev<<"AVGSINR: "<<totalSINR / totalTime<<"\n";
    return totalSINR / totalTime;
}

// Bit Error Rate for Variable Pulse Position Modulation
double VLC::BERVPPM(double avgSINR, std::map<std::string, double> & transmissionInfo) {
    double x;
    double alpha = transmissionInfo["dutyCycle"];
    double beta = 1.0; // Another magic value

    if (alpha <= 0.5)
        x = std::sqrt(avgSINR / (2.0 * beta * alpha));
    else
        x = std::sqrt(avgSINR * (1.0 - alpha) / (2.0 * beta * alpha * alpha));

    // Calculate BER = Q(x)
    // Q-function is the tail probability of the standard normal distribution
    return Qfunction(x);
}

// Symbol Error Rate for Pulse Amplitude Modulation
double VLC::SERPAM(double avgSINR, std::map<std::string, double> & transmissionInfo) {
    double modulationOrder = transmissionInfo["modulationOrder"];
    //ev<<"Modulation order is: "<<modulationOrder<<"\n";

    double x = std::sqrt(avgSINR)/(modulationOrder - 1.0);
    //ev<<"X is: "<<x<<"\n";

    double SER = ((2.0*(modulationOrder - 1.0)) / modulationOrder)*Qfunction(x);
    //ev<<"SER is: "<<SER<<"\n";

    return SER;
}

// Packet Error Rate for Variable Pulse Position Modulation returns true if the randomly generated number is less than the PER
bool VLC::PERVPPM(double avgSINR, std::map<std::string, double> & transmissionInfo) {
    double PER = 1.0 - std::pow((1.0 - VLC::BERVPPM(avgSINR, transmissionInfo)), 8.0 * transmissionInfo["packetLength"]);
    //ev<<"PERVPPM is: "<<PER<<"\n";

    srand(time(0));
    double prob = (double)rand() / (double)RAND_MAX;

    return (prob < PER);
}

// Packet Error Rate for Pulse Amplitude Modulation returns true if the randomly generated number is less than the PER
bool VLC::PERPAM(double avgSINR, std::map<std::string, double> & transmissionInfo) {
    double PER = 1.0 - std::pow( (1.0 - VLC::SERPAM(avgSINR, transmissionInfo)), ((8.0 * transmissionInfo["packetLength"]) / std::log2(transmissionInfo["modulationOrder"])));
    //ev<<"PERPAM is: "<<PER<<"\n";

    srand(time(0));
    double prob = (double)rand() / (double)RAND_MAX;

    return (prob < PER);
}


