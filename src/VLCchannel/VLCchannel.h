//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef VLCCHANNEL_H_
#define VLCCHANNEL_H_

#include <omnetpp.h>
#include <VLCconnection.h>
#include <VLCcommons.h>
#include <csimulation.h>
#include <cchannel.h>
#include <VLCpacket_m.h>


namespace VLC{
    // Forward declarations
    class VLCdevice;
    class VLCtransmitter;

    class VLCchannel : public ::cSimpleModule{

    protected:
        cSimulation * sim = cSimulation::getActiveSimulation();
        double updateInterval = 10;

        // Holds all the VLCdevices currently in the network
        std::set <VLC::VLCdevice*> VLCdevices;
        std::map <VLC::VLCdevice*, dataPacket*> transmitterMessages;

        // Holds all connections between a transmitter and receiver currently active
        mutable std::set <VLC::VLCconnection> VLCconnections;

        // A map between a device and the number of the gate that the channel uses to communicate with it
        std::map <VLC::VLCdevice*, int> VLCdeviceGates;

        // A map between a device and a set of VLCdevViewInfo structures, holding what's currently in view of the device
        std::map <VLC::VLCdevice*, std::set<VLCdevViewInfo>*> VLCcurrentViews;

        virtual void initialize();
        virtual void handleMessage(cMessage *msg);

        // Get the list of devices in the Field of View of the given device
        std::set<VLCdevViewInfo>* devicesInFoVOf( VLC::VLCdevice * device );

        // Compute all the necessary computations to step the simulation time forward, i.e., calculating the SINR for every
        // active connection
        void updateChannel();

        // Recomputes the view for all the devices in the set
        void recomputeView( std::set<VLCdevViewInfo> * devices);

        // Signal the channel that the transmitter has begun transmitting
        void startTransmission(VLCdevice * transmitter);
        // Signal the channel that the transmitter has stopped transmitting
        void endTransmission(VLCdevice* transmitter);

        // Returns the connection between the devices if it exists, NULL otherwise
        VLC::VLCconnection* connectionExists(VLCdevice * transmitter, VLCdevice * receiver);
        // Creates a connection between the tx and rx
        int createConnection(VLCdevice * transmitter, VLCdevice * receiver);
        // Terminates the connection between the tx and rx because the tx has sent the VLCchannelSignalEnd
        int dropConnection(VLCdevice * transmitter, VLCdevice * receiver);
        // Aborts the connection between tx and rx because the devices are no longer able to communicate
        // this can be because they are too far apart or no longer in their respective FoVs
        int abortConnection(VLCdevice * transmitter, VLCdevice * receiver);


    public:
        VLCchannel();
        virtual ~VLCchannel();

        // Creates a new VLCdevViewInfo structure between device1 and 2. The devices need not be a tx rx pair.
        VLC::VLCdevViewInfo devsPerspective(VLCdevice* device1, VLCdevice* device2);

        // Adds a new device to the channel
        void addDevice(VLCdevice* device, cGate *deviceGateIn, cGate *deviceGateOut);

        // Adds a new mobility manager
        void addMobility(cGate* mobilityGate);

        // Notifies the channel that the device has changed
        void notifyChange(VLCdevice * device);

        VLCdevViewInfo getDevViewInfo(VLCdevice * transmitter, VLCdevice * receiver);
    };

    Define_Module(VLCchannel);

}


#endif /* VLCCHANNEL_H_ */

