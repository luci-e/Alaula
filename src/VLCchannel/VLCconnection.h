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
#include <vector>
#include <map>
#include <string>
#include <VLCpacket_m.h>

namespace VLC {

class VLCchannel;

class VLCconnection {

    private:
        long unsigned int connectionId;
        std::vector<VLCtimeSINR> SINRTrend;
        double gainConstantPart, connectionGain;
        std::map<std::string, double> transmissionInfo;

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
        void updateConnection();

        // Add a new value to the SINR trend
        void calculateNextValue();

        // Compute the outcome of this transmission, returns true if it was successful false otherwise
        bool getOutcome();

        // Abort this connection
        void abortConnection() const;

    };

} /* namespace VLC */

#endif /* VLCCONNECTION_H_ */
