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
#include <VLCreceiver.h>
#include <VLCtransmitter.h>
#include <VLCemitter.h>
#include <vector>
#include <map>
#include <string>
#include <VLCpacket_m.h>

namespace VLC {

class VLCchannel;

class VLCconnection {

    struct sourceInfo{
        VLCdevice * source;
        double gainConstantPart;
        double sourceGain;
        double signalPower;
    };

    private:
        long unsigned int connectionId;
        mutable std::vector<VLCtimeSINR> SINRTrend;

        mutable std::map<VLCdevice*, sourceInfo> noiseSources;
        mutable double totalNoisePower = 0;

        // Info about the transmission as per the last update of this connection
        mutable double connGainConstantPart;
        mutable double connectionGain;
        mutable double SINRdB;

        mutable VLCdevViewInfo lastView;

        mutable std::map<transmissionKeys, double> transmissionInfo;



    public:
        static long unsigned int connectionCounter;

        VLC::VLCtransmitter *transmitter;
        VLC::VLCreceiver *receiver;
        VLC::VLCchannel *channel;

        VLCconnection(VLCdevice * transmitter, VLCdevice * receiver, VLCchannel * channel);
        virtual ~VLCconnection();

        // A connection equals another iff the transmitter and receiver are the same
        inline bool operator==(const VLCconnection &c2) const;

        // C1 is lt C2 iff (c1.transmitter < c2.transmitter) or ((c1.transmitter == c2.transmitter) and (c1.receiver < c2.receiver ))
        bool operator<(const VLCconnection &c2) const;

        // Updates the values used to calculate the SINR
        void updateConnection() const;

        // Add a new value to the SINR trend
        void calculateNextValue();

        // Compute the outcome of this transmission, returns true if it was successful false otherwise
        bool getOutcome();

        // Abort this connection
        void abortConnection() const;

        // Adds a noise source that can be another transmitter or an actual noise source
        void addNoiseSource(VLCdevice * noiseSource) const;

        // Recalculates the values for this noise source
        void updateNoiseSource(VLCdevice * noiseSource) const;

        // Removes the noise source from the map of this connection
        void removeNoiseSource(VLCdevice * noiseSource);

        // Calculates the total noise power
        void calculateTotalNoise() const;


        std::vector<VLCtimeSINR>& getSINRTrend();
        std::map<transmissionKeys, double>& getTransmissionInfo();
        const VLCdevViewInfo& getLastView() const;

        unsigned long int getConnectionId() const;


    };

} /* namespace VLC */

#endif /* VLCCONNECTION_H_ */
