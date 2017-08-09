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


namespace VLC{
    // Forward declarations
    class VLCdevice;

    class VLCchannel : public ::cSimpleModule{

    protected:
        cSimulation * sim = cSimulation::getActiveSimulation();

        std::list <VLC::VLCdevice*> VLCdevices;
        std::list <VLC::VLCconnection> VLCconnections;
        std::map <VLC::VLCdevice*, int> VLCdeviceGates;



        virtual void initialize();
        virtual void handleMessage(cMessage *msg);

        // Get the list of devices in the Field of View of the given device
        std::list <VLCdevViewInfo>* devicesInFoVOf( VLC::VLCdevice * device );

        void updateChannel();

        void startTransmission(VLCdevice * transmitter);
        void endTransmission(VLCdevice* transmitter);

        VLC::VLCconnection* connectionExists(VLCdevice * transmitter, VLCdevice * receiver);
        int createConnection(VLCdevice * transmitter, VLCdevice * receiver);
        int dropConnection(VLCdevice * transmitter, VLCdevice * receiver);


    public:
        VLCchannel();
        virtual ~VLCchannel();

        VLC::VLCdevViewInfo devsPerspective(VLCdevice* device1, VLCdevice* device2);

        // Adds a new device to the channel
        void addDevice(VLCdevice* device, cGate *deviceGateIn, cGate *deviceGateOut);

        // Adds a new mobility manager
        void addMobility(cGate* mobilityGate);

        // Notifies the channel that the device has changed
        void notifyChange(VLCdevice * device);
    };

    Define_Module(VLCchannel);

}


#endif /* VLCCHANNEL_H_ */
