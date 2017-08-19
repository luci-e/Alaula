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

#include <VLCchannel.h>
#include <VLCdevice.h>
#include <cgate.h>
#include <cchannel.h>
#include <VLCchannelMsg_m.h>
#include <VLCconnection.h>
#include <list>
#include <set>
#include <algorithm>


void VLC::VLCchannel::initialize(){};

void VLC::VLCchannel::handleMessage(cMessage *msg){
    if(msg->isSelfMessage()){

    }else{
        VLCchannelMsg *chMsg = dynamic_cast<VLCchannelMsg*>(msg);
        switch(chMsg->getMessageType()){
            case CH_MOVE_MSG:{
                VLCmoveMsg *moveMsg = dynamic_cast<VLCmoveMsg*>(msg);
                this->notifyChange((VLCdevice*)sim->getModule(moveMsg->getNodeId()));
                break;
            }
            case CH_BEGIN_COMM_MSG:{
                VLCchannelSignalBegin *msgBegin = dynamic_cast<VLCchannelSignalBegin*>(msg);
                VLCdevice * transmitter = (VLCdevice*) sim->getModule(msgBegin->getNodeId());
                this->transmitterMessages[transmitter] = dynamic_cast<VLCpacket*>(msgBegin->decapsulate());
                this->startTransmission(transmitter);
                break;
            }
            case CH_END_COMM_MSG:{
                VLCchannelSignalEnd *msgEnd = dynamic_cast<VLCchannelSignalEnd*>(msg);
                VLCdevice * transmitter = (VLCdevice*) sim->getModule(msgEnd->getNodeId());
                this->endTransmission(transmitter);
                break;
            }
        }
    }
    delete msg;
};

// Nothing to do here
VLC::VLCchannel::VLCchannel() {}
VLC::VLCchannel::~VLCchannel() {}

// Adds a new device to the channel
void VLC::VLCchannel::addDevice(VLCdevice* device, cGate *deviceGateIn, cGate *deviceGateOut) {
    this->VLCdevices.insert(device);

    // Expand the gateVector to accommodate the new device
    int newGateVSize = gateSize("devicePort")+1;
    setGateSize("devicePort", newGateVSize);

    // Create the channel to and fro the device
    cIdealChannel *channelIn = cIdealChannel::create(VLC::randomString(16));
    cIdealChannel *channelOut = cIdealChannel::create(VLC::randomString(16));

    // Connect them
    gate("devicePort$o", newGateVSize-1)->connectTo(deviceGateIn, channelOut);
    deviceGateOut->connectTo(gate("devicePort$i", newGateVSize-1), channelIn);

    channelIn->callInitialize();
    channelOut->callInitialize();

    // Recompute the state of the network
    this->VLCcurrentViews[device] = new std::set<VLCdevViewInfo>();
    //this->notifyChange(device);

    // Add the current view to the map
    VLCdeviceGates[device] = newGateVSize-1;
}

// Get the list of devices in the Field of View of the given device
std::set<VLC::VLCdevViewInfo>* VLC::VLCchannel::devicesInFoVOf(VLC::VLCdevice* device) {
    std::set<VLCdevViewInfo> *deviceList = new std::set<VLCdevViewInfo>();

    for( auto& currentDevice : this->VLCdevices ){
        if(device != currentDevice){
            VLCdevViewInfo dvi = devsPerspective(device, currentDevice);
            if( dvi.seeEachOther){
                deviceList->insert(dvi);
            }

        }
    }

    return deviceList;
}

// Creates a new VLCdevViewInfo structure between device1 and 2. The devices need not be a tx rx pair.
VLC::VLCdevViewInfo VLC::VLCchannel::devsPerspective(VLCdevice* device1, VLCdevice* device2){

    VLCnodePosition dev1Position = device1->getNodePosition();
    VLCnodeDirection dev1Direction = device1->getNodeDirection();
    double dev1FoV = device1->getSemiAngle();

    //ev<<"Device1 with id "<<device1->getId()<<" position: ";
    //VLC::printPosition(dev1Position);

    //ev<<"Device1 with id "<<device1->getId()<<" vector: ";
    //VLC::printVector(dev1Direction);

    VLCnodePosition dev2Position = device2->getNodePosition();
    VLCnodeDirection dev2Direction = device2->getNodeDirection();
    double dev2FoV = device2->getSemiAngle();

    //ev<<"Device2 with id "<<device2->getId()<<" position: ";
    //VLC::printPosition(dev2Position);

    //ev<<"Device2 with id "<<device2->getId()<<" vector: ";
    //VLC::printVector(dev2Direction);

    VLCdevViewInfo devsPer;
    devsPer.device1 = device1->getId();
    devsPer.device2 = device2->getId();

    devsPer.distance = distance(dev1Position, dev2Position);

    //ev<<"Devices distance is "<<devsPer.distance<<"\n";

    // Calculate if the second device is in the FoV of the first one
    vector3d distanceVector = {dev2Position.x-dev1Position.x, dev2Position.y-dev1Position.y, dev2Position.z-dev1Position.z};
    vector3d normalisedDistance = normalise(distanceVector);

    //ev<<"1 to 2 normalised vector:";
    //VLC::printVector(normalisedDistance);

    // since v1 dot v2 = norm(v1) * norm(v2) cos theta but norm(v1) = norm(v2) = 1
    devsPer.angle1 = acos(dotProduct3d(dev1Direction, normalisedDistance));
    bool can1see2 =  devsPer.angle1  <= dev1FoV;

    //ev<<"Can 1 see 2? "<<can1see2<<"\n";

    // Do the same for the second device
    distanceVector = opposite(distanceVector);
    normalisedDistance = normalise(distanceVector);

    //ev<<"2 to 1 normalised vector:";
    //VLC::printVector(normalisedDistance);

    devsPer.angle2 = acos(dotProduct3d(dev2Direction, normalisedDistance));
    bool can2see1 = devsPer.angle2 <= dev2FoV;

    //ev<<"Can 2 see 1? "<<can2see1<<"\n";

    devsPer.seeEachOther = can1see2 && can2see1;

    return devsPer;
}

// Creates a connection between the tx and rx
int VLC::VLCchannel::createConnection(VLCdevice * transmitter, VLCdevice * receiver) {
    VLC::VLCconnection* conn = this->connectionExists(transmitter, receiver);
    if( !conn ){
        VLC::VLCconnection newConn(transmitter, receiver, this);
        this->VLCconnections.insert(newConn);
        return 0;
    }
    return -1;
}

// Terminates the connection between the tx and rx because the tx has sent the VLCchannelSignalEnd
int VLC::VLCchannel::dropConnection(VLCdevice * transmitter, VLCdevice * receiver) {
    VLC::VLCconnection* conn = this->connectionExists(transmitter, receiver);
    if(conn){
        this->VLCconnections.erase((*conn));
        return 0;
    }
    return -1;
}

// Aborts the connection between tx and rx because the devices are no longer able to communicate
// this can be because they are too far apart or no longer in their respective FoVs
int VLC::VLCchannel::abortConnection(VLCdevice* transmitter, VLCdevice* receiver) {
    VLC::VLCconnection* conn = this->connectionExists(transmitter, receiver);
    if(conn){
        conn->abortConnection();
        this->VLCconnections.erase(*conn);
        ev<<"Erased the connection\n";
        return 0;
    }
    return -1;
}

// Returns the connection between the devices if it exists, NULL otherwise
VLC::VLCconnection* VLC::VLCchannel::connectionExists(VLCdevice * transmitter, VLCdevice * receiver) {
    VLCconnection toFind(transmitter, receiver, NULL);
    std::set <VLC::VLCconnection>::iterator conn = this->VLCconnections.find(toFind);
    if( conn != this->VLCconnections.end()){
        return const_cast<VLCconnection*>(&(*conn));
    }
    return NULL;
}

// Signal the channel that the transmitter has begun transmitting
void VLC::VLCchannel::startTransmission(VLCdevice* transmitter) {
    std::set<VLCdevViewInfo> * receiversInFoV = this->devicesInFoVOf(transmitter);
    for( std::set<VLCdevViewInfo>::iterator receiverIt = receiversInFoV->begin(); receiverIt != receiversInFoV->end(); receiverIt++){
        VLCdevice * receiver = (VLCdevice*) this->sim->getModule((*receiverIt).device2);
        if( receiver->getDeviceType() == RECEIVER_DEVICE){
            this->createConnection(transmitter, receiver);
            ev<<"created connection between "<<transmitter->getId()<<" and "<<receiver->getId()<<"\n";
        }
    }
}

// Signal the channel that the transmitter has stopped transmitting
void VLC::VLCchannel::endTransmission(VLCdevice* transmitter) {
    // Get this transmitter packet
    VLCpacket *pkt = this->transmitterMessages[transmitter];

    for( std::set <VLC::VLCconnection>::iterator conn = this->VLCconnections.begin(); conn != this->VLCconnections.end();){
        VLCconnection c = *conn;
        if(c.transmitter == transmitter){
            if( c.getOutcome() ){
                cGate * receiverGate = gate("devicePort$o", this->VLCdeviceGates[const_cast<VLCdevice*>((VLCdevice*) c.receiver)]);
                send(pkt->dup(), receiverGate);
            }

            // Close the connection
            this->VLCconnections.erase(conn++);
            continue;
        }
        conn++;
    }

    // Remove the packet from the map
    this->transmitterMessages.erase(transmitter);
}

// Compute all the necessary computations to step the simulation time forward, i.e., calculating the SINR for every
// active connection
void VLC::VLCchannel::updateChannel(){
    for( std::set<VLCconnection>::iterator conn = this->VLCconnections.begin(); conn != this->VLCconnections.end(); conn++){
        VLCconnection c = *conn;
        // Calculate the SINR between the devices in the connection
        // Update the connection by adding a new value to the SINRtrend
    }
}


// Notifies the channel that the device has changed
void VLC::VLCchannel::notifyChange(VLCdevice * device) {
    // Calculate what the device is currently seeing
    std::set<VLCdevViewInfo> *newView = this->devicesInFoVOf(device);
    //ev<<"New View:\n";
    //printDevicesInFoV(newView);

    // Get what was the last view
    std::set<VLCdevViewInfo> *oldView = this->VLCcurrentViews[device];
    //ev<<"Old View:\n";
    //printDevicesInFoV(oldView);

    // Get the devices that have come into the FoV of the device
    std::set<VLCdevViewInfo> newDevices;
    std::set_difference(newView->begin(), newView->end(), oldView->begin(), oldView->end(),  std::inserter(newDevices, newDevices.begin()) );

    //ev<<"New devices\n";
    //printDevicesInFoV(&newDevices);

    // Get the devices that went of the FoV of the device
    std::set<VLCdevViewInfo> outDevices;
    std::set_difference(oldView->begin(), oldView->end(), newView->begin(), newView->end(), std::inserter(outDevices, outDevices.begin()) );

    //ev<<"Out devices\n";
    //printDevicesInFoV(&outDevices);


    VLCdevViewInfo devInfo;

    // Loop through the connections
    if( device->getDeviceType() == TRANSMITTER_DEVICE ){
        for(std::set<VLCconnection>::iterator c = this->VLCconnections.begin(); c != this->VLCconnections.end();){
            VLCconnection *conn = const_cast<VLCconnection*>(&(*c));
            // If it's part of this connection
            if( conn->transmitter == device){
                // Build a devViewInfo for this connection
                devInfo = (VLCdevViewInfo) {conn->transmitter->getId(), conn->receiver->getId(), 0, 0.0, 0.0, 0.0};
                // If it is one of the devices that have gone out of view delete it and abort the connection
                if(outDevices.find(devInfo) != outDevices.end()){
                    conn->abortConnection();
                    this->VLCconnections.erase(c++);
                    continue;
                }else{
                    conn->updateConnection();
                    conn->calculateNextValue();
                }
            }
            c++;
        }
    }else if(device->getDeviceType() == RECEIVER_DEVICE){
        for(std::set<VLCconnection>::iterator c = this->VLCconnections.begin(); c != this->VLCconnections.end();){
            VLCconnection *conn = const_cast<VLCconnection*>(&(*c));
            // If it's part of this connection
            if( conn->receiver == device){
                // Build a devViewInfo for this connection
                devInfo = (VLCdevViewInfo) {conn->transmitter->getId(), conn->receiver->getId(), 0, 0.0, 0.0, 0.0};
                // If it is one of the devices that have gone out of view delete it and abort the connection
                if(outDevices.find(devInfo) != outDevices.end()){
                    conn->abortConnection();
                    this->VLCconnections.erase(c++);
                    continue;
                }else{
                    conn->updateConnection();
                    conn->calculateNextValue();
                }
            }
            c++;
        }
    }

    // Update the view of all the objects that can now see each other
    for( std::set<VLCdevViewInfo>::iterator newDevs = newDevices.begin(); newDevs != newDevices.end(); newDevs++){
        this->VLCcurrentViews[(VLCdevice*) this->sim->getModule(newDevs->device2)]->insert(invertedView(*newDevs));
    }

    // Update the view of all the objects that can no longer see each other
    for( std::set<VLCdevViewInfo>::iterator outDevs = outDevices.begin(); outDevs != outDevices.end(); outDevs++){
        this->VLCcurrentViews[(VLCdevice*) this->sim->getModule(outDevs->device2)]->erase(invertedView(*outDevs));
    }

    // Update the map for the device views
    delete this->VLCcurrentViews[device];
    this->VLCcurrentViews[device] = newView;

    // Update the channel
    this->updateChannel();
}

// Connect the VLCchannel to the mobility manager through an ideal channel
void VLC::VLCchannel::addMobility(cGate* mobilityGate) {
    setGateSize("mobilityPort", gateSize("mobilityPort")+1);
    cIdealChannel *c = cIdealChannel::create(VLC::randomString(16));
    mobilityGate->connectTo(gate("mobilityPort", gateSize("mobilityPort")-1), c);
    c->callInitialize();
}

VLC::VLCdevViewInfo VLC::VLCchannel::getDevViewInfo(VLCdevice * transmitter, VLCdevice * receiver){
    // Build a devViewInfo for this connection
    VLCdevViewInfo devInfo = (VLCdevViewInfo) {transmitter->getId(), receiver->getId(), 0, 0.0, 0.0, 0.0};
    return *(this->VLCcurrentViews[transmitter]->find(devInfo));
}
