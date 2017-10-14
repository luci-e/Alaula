/*
 * VLCtransmissionModels.cc
 *
 *  Created on: Aug 19, 2017
 *      Author: casper
 */

#include <VLCtransmissionModels.h>
#include <VLCconnection.h>
#include <VLCpacket_m.h>
#include <VLCcommons.h>
#include <vector>
#include <map>
#include <string>
#include <math.h>
#include <Log.h>
#include <time.h>

// returns true if the packet can be successfully transmitter, false otherwise
bool VLC::packetTransmitted(VLCconnection *conn){
    switch((int) conn->getTransmissionInfo()[MODULATION_TYPE]){
        case VPPM:{
            return VLC::PERVPPM(conn);
        }
        case PAM:{
            return VLC::PERPAM(conn);
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
        totalSINR += std::pow( 10.0, (val->SINR)/10.0) * diff;
        totalTime += diff;
        lastTime = val->time;
    }


    //ev<<"TotalSINR: "<<totalSINR<<" totalTime: "<<totalTime<<"\n";
    //ev<<"AVGSINR: "<<totalSINR / totalTime<<"\n";
    return totalSINR / totalTime;
}

// Bit Error Rate for Variable Pulse Position Modulation
double VLC::BERVPPM(VLCconnection * conn) {
    double x;
    double alpha = conn->getTransmissionInfo()[DUTY_CYCLE];
    double beta = 1.0; // Another magic values

    double BER;

    double avgSINR = 10*log10( averageSINR(conn->getSINRTrend()) );

    if(avgSINR >= 0 ){

        if (alpha <= 0.5){
            x = std::sqrt(avgSINR / (2.0 * beta * alpha));
        }else{
            x = std::sqrt(avgSINR * (1.0 - alpha) / (2.0 * beta * alpha * alpha));
        }

        // Calculate BER = Q(x)
        // Q-function is the tail probability of the standard normal distribution

        BER = Qfunction(x);
    }else{
        BER = 1;
    }

    VLCdevViewInfo viewInfo = conn->getLastView();

    LOGN_(1) << conn->getConnectionId() << ";"\
            << viewInfo.device1 << ";"\
            << viewInfo.device2 << ";"\
            << simTime().dbl() << ";"\
            << "PositionBER" << ";"\
            << conn->receiver->getNodePosition().x << ";"\
            << conn->receiver->getNodePosition().y << ";"\
            << conn->receiver->getNodePosition().z << ";"\
            << viewInfo.angle1<<";"\
            << viewInfo.angle2<<";"\
            << log10(BER);

    return BER;
}

// Symbol Error Rate for Pulse Amplitude Modulation
double VLC::SERPAM(VLCconnection * conn) {

    double avgSINR = VLC::averageSINR(conn->getSINRTrend());
    double modulationOrder = conn->getTransmissionInfo()[MODULATION_ORDER];
    //ev<<"Modulation order is: "<<modulationOrder<<"\n";

    double x = std::sqrt(avgSINR)/(modulationOrder - 1.0);
    //ev<<"X is: "<<x<<"\n";

    double SER = ((2.0*(modulationOrder - 1.0)) / modulationOrder)*Qfunction(x);
    //ev<<"SER is: "<<SER<<"\n";

    return SER;
}

// Packet Error Rate for Variable Pulse Position Modulation returns true if the randomly generated number is less than the PER
bool VLC::PERVPPM(VLCconnection* conn) {
    double PER = 1.0 - std::pow(1.0 - VLC::BERVPPM(conn), 8.0 * conn->getTransmissionInfo()[PACKET_LENGTH]);
    //ev<<"PERVPPM is: "<<PER<<"\n";

    srand(time(0));
    double prob = (double)rand() / (double)RAND_MAX;

    return (prob > PER);
}

// Packet Error Rate for Pulse Amplitude Modulation returns true if the randomly generated number is less than the PER
bool VLC::PERPAM(VLCconnection * conn) {
    std::map<VLC::transmissionKeys, double> & transmissionInfo = conn->getTransmissionInfo();
    double PER = 1.0 - std::pow( (1.0 - VLC::SERPAM(conn)), ((8.0 * transmissionInfo[PACKET_LENGTH]) / std::log2(transmissionInfo[MODULATION_ORDER])));
    //ev<<"PERPAM is: "<<PER<<"\n";

    srand(time(0));
    double prob = (double)rand() / (double)RAND_MAX;

    return (prob < PER);
}


