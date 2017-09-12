/*
 * VLCreceiver.h
 *
 *  Created on: Aug 19, 2017
 *      Author: casper
 */

#ifndef VLCRECEIVER_H_
#define VLCRECEIVER_H_

#include <VLCdevice.h>

namespace VLC{
    class VLCreceiver : public VLCdevice{


        protected:
            double photoDetectorArea;
            double refractiveIndex;
            double noiseVariance;

            void initialize() override;
            void handleMessage(cMessage *msg) override;


        public:
            VLCreceiver(){};
            ~VLCreceiver(){};

            // A set holding the connection this receiver is currently in
            mutable std::set<VLC::VLCconnection*> connectionEnds;

            double getSemiAngle() const;
            void setSemiAngle(double semiAngle);
            double getLambertianOrder() const;
            double getPhotoDetectorArea() const;
            double getRefractiveIndex() const;
            double getNoiseVariance(double Pr) const;
            double opticalGain(double psi) const;

            void addConnectionEnd( VLCconnection * connection);
            void removeConnectionEnd( VLCconnection * connection);
            std::set<VLC::VLCconnection*>& getConnectionEnds();
};
    Define_Module(VLCreceiver);
}



#endif /* VLCRECEIVER_H_ */
