/*
 * VLCtransmitter.cc
 *
 *  Created on: Jul 30, 2017
 *      Author: casper
 */

#include <math.h>
#include <VLCpacket_m.h>
#include <VLCreceiver.h>
#include <Log.h>

void VLC::VLCreceiver::initialize(){
    VLCdevice::initialize();

    // Set the receiver parameters
    std::vector<double> receiverPars = cStringTokenizer(par("devPars").stringValue()).asDoubleVector();

    if(receiverPars.size() == 3){
        this->photoDetectorArea = receiverPars[1];
        this->refractiveIndex = receiverPars[2];
    }

    this->address = par("address");
    this->deviceType = RECEIVER_DEVICE;
}

void VLC::VLCreceiver::handleMessage(cMessage *msg){
    send(msg, "controllerPort$o");
}

// Return the optical gain for a given angle of incidence
double VLC::VLCreceiver::opticalGain(double psi) const{
    if( psi > this->semiAngle || psi < 0){
        return 0;
    }

    // TODO what
    double sinOfFoV = sin(this->semiAngle );
    return ( ( this->refractiveIndex * this->refractiveIndex ) / ( sinOfFoV * sinOfFoV ) );
}

double VLC::VLCreceiver::getPhotoDetectorArea() const {
    return photoDetectorArea;
}

double VLC::VLCreceiver::getRefractiveIndex() const {
    return refractiveIndex;
}

// This is taken from the ns3 implementation i have no idea how the formulas are derived but they return a nice number so...
double VLC::VLCreceiver::getNoiseVariance(double Pr) const{
    // Why did they comment this part and set it to a constant is a mistery to me.
    //res = IntegralRes() / IntegralPlanck();
    double res = 0.54;
    double temp = 300.0;
    double I2 = 0.5620; //noise bandwidth factor
    double I3 = 0.0868; //noise bandwidth factor
    double Ib = 5100e-6; //photocurrent due to background radiation [microA]
    double Gol = 10.0; //open-loop voltage gain
    double Cpd = 112e-12; //fixed capacitance of photodetector per unit area [pF/cm^2]
    double gm = 30e-3; //FET transconductance [mS]
    double  gamma = 1.5; //FET channel noise factor
    double B = 100.0e6;

    double shotVar, thermalVar;

    double Areaincm2 =  this->photoDetectorArea*10000.0;

    // shot noise variance
    shotVar = (2.0 * VLC::q * res * Pr * B) + (2.0 * VLC::q * Ib * I2 * B);

    // thermal noise variance
    thermalVar = (8.0 * M_PI * VLC::k * temp * Cpd * Areaincm2 * I2 * (B * B) / Gol)
    + (16.0 * (M_PI * M_PI) * VLC::k * temp * gamma * (Cpd * Cpd) * (Areaincm2 * Areaincm2) * I3 * (B * B * B) / gm);

    return shotVar + thermalVar;
}

double VLC::VLCreceiver::getShotNoiseVariance(double Pr) const {
    double res = 0.54;
    double I2 = 0.5620; //noise bandwidth factor
    double Ib = 5100e-6; //photocurrent due to background radiation [microA]
    double B = 100.0e6;

    double shotVar;
    // shot noise variance
    shotVar = (2.0 * VLC::q * res * Pr * B) + (2.0 * VLC::q * Ib * I2 * B);

    return shotVar;
}

void VLC::VLCreceiver::addConnectionEnd(VLCconnection* connection) {
    this->connectionEnds.insert(connection);
}

std::set<VLC::VLCconnection*>& VLC::VLCreceiver::getConnectionEnds(){
    return connectionEnds;
}

void VLC::VLCreceiver::removeConnectionEnd(VLCconnection* connection) {
    this->connectionEnds.erase(connection);
}

void VLC::VLCreceiver::resetThroughput(){
    //this->totalReceivedData = 0;
    //this->startThroughputTime = simTime().dbl();
}

void VLC::VLCreceiver::signalSINRThreshold() {
    Enter_Method("signalSINRThreshold()");
    if(this->currentTransmitterAddress != -1){
        VLCMACMsg * unsubscribeMsg = new VLCMACMsg();
        unsubscribeMsg->setMessageType(VLC_MAC_MSG);
        unsubscribeMsg->setMACCode(UNSUBSCRIBE_MSG);
        unsubscribeMsg->setTransmitterNodeAddress(this->currentTransmitterAddress);
        unsubscribeMsg->setReceiverNodeAddress(this->address);
        this->currentTransmitterAddress = -1;

        take(unsubscribeMsg);
        send(unsubscribeMsg, "controllerPort$o");
    }
}


