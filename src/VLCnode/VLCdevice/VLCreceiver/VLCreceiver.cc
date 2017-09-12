/*
 * VLCtransmitter.cc
 *
 *  Created on: Jul 30, 2017
 *      Author: casper
 */

#include <math.h>
#include <VLCpacket_m.h>
#include <VLCreceiver.h>

void VLC::VLCreceiver::initialize(){
    VLCdevice::initialize();

    // Set the receiver parameters
    std::vector<double> receiverPars = cStringTokenizer(par("devPars").stringValue()).asDoubleVector();

    if(receiverPars.size() == 3){
        this->photoDetectorArea = receiverPars[1];
        this->refractiveIndex = receiverPars[2];
    }

    this->deviceType = RECEIVER_DEVICE;
}

void VLC::VLCreceiver::handleMessage(cMessage *msg){
    dataPacket * dp = (dataPacket*) msg;

    double duration = simTime().dbl() - dp->getTransmissionStartTime();
    ev<<"Message is: "<<dp->getContent()<<" Transmission took "<<duration<<"ms\n";

    if(!msg->isSelfMessage()){
        VLCpacket *pkt = dynamic_cast<VLCpacket*>(msg);
    }

    delete msg;
}

// Return the optical gain for a given angle of incidence
double VLC::VLCreceiver::opticalGain(double psi) const{
    if( psi > this->semiAngle){
        return 0;
    }

    double sinOfFoV = sin( this->semiAngle );
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
    double res = 0.003;
    double temp = 295;
    static const double q = 1.602176487e-19;        //electronic charge [Coulombs]
    static const double k = 1.38064852e-23;     //Boltzmann constant [m^2 kg s^-2 K^-1]
    static const double I2 = 0.5620; //noise bandwidth factor
    double I3 = 0.0868; //noise bandwidth factor
    double Ib = 5100e-6; //photocurrent due to background radiation [microA]
    double Gol = 10; //open-loop voltage gain
    double Cpd = 112e-12; //fixed capacitance of photodetector per unit area [pF/cm^2]
    double gm = 30e-3; //FET transconductance [mS]
    double  gamma = 1.5; //FET channel noise factor
    double B = 10;

    double shotVar, thermalVar;

    // shot noise variance
    shotVar = (2 * q * res * Pr * B) + (2 * q * Ib * I2 * B);

    // thermal noise variance
    thermalVar = (8 * M_PI * k * temp * Cpd * this->photoDetectorArea * I2 * (B * B) / Gol)
    + (16 * (M_PI * M_PI) * k * temp * gamma * (Cpd * Cpd) * (this->photoDetectorArea * this->photoDetectorArea) * I3 * (B * B * B) / gm);

    return shotVar + thermalVar;
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
