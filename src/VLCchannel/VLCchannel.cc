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
#include <VLCpacket_m.h>
#include <VLCconnection.h>
#include <list>
#include <set>
#include <algorithm>
#include <Log.h>
#include <VLCformatter.h>

VLC::VLCchannel::VLCchannel() {}
VLC::VLCchannel::~VLCchannel() {}

void VLC::VLCchannel::initialize(){
    // Initialize the logger and the connection counter

    std::string logFolder= par("logFolder").stdstringValue();

    plog::init<plog::VLCformatter>(plog::none, (logFolder+"SINRdata.csv").c_str(), 1000000, 1);
    plog::init<plog::VLCformatter, 1>(plog::none, (logFolder+"BERdata.csv").c_str(), 1000000, 1);
    plog::init<plog::VLCformatter, 2>(plog::none, (logFolder+"throughputData.csv").c_str(), 1000000, 1);

    scheduleAt(simTime() + this->updateInterval, new cMessage());
};

void VLC::VLCchannel::handleMessage(cMessage *msg){
    if(msg->isSelfMessage()){
        this->updateChannel();
        scheduleAt(simTime() + this->updateInterval, new cMessage());
    }else{
        VLCpacket *chMsg = dynamic_cast<VLCpacket*>(msg);
        switch(chMsg->getMessageType()){
            case VLC_CTRL_MSG:{
                VLCctrlMsg* ctrlMsg = dynamic_cast<VLCctrlMsg*>(msg);
                switch(ctrlMsg->getCtrlCode()){
                    case DEVICE_MOVED:{
                        this->notifyChange((VLCdevice*)sim->getModule(ctrlMsg->getNodeId()));
                        break;
                    }
                    case TRANSMISSION_BEGIN:{
                        VLCdevice * transmitter = (VLCdevice*) sim->getModule(ctrlMsg->getNodeId());
                        this->transmitterMessages[transmitter] = dynamic_cast<VLCpacket*>(ctrlMsg->decapsulate());
                        this->startTransmission(transmitter);
                        break;
                    }
                    case TRANSMISSION_END:{
                        VLCdevice * transmitter = (VLCdevice*) sim->getModule(ctrlMsg->getNodeId());
                        this->endTransmission(transmitter);
                        break;
                    }
                    case TRANSMISSION_ABORT:{
                        VLCdevice * transmitter = (VLCdevice*) sim->getModule(ctrlMsg->getNodeId());
                        this->abortTransmission(transmitter);
                        break;
                    }
                    case NOISE_DEVICE_CHANGED:{
                        this->notifyChange((VLCdevice*) sim->getModule(ctrlMsg->getNodeId()));
                        break;
                    }
                }
            }
        }
    }
    delete msg;
};


// Adds a new device to the channel
void VLC::VLCchannel::addDevice(VLCdevice* device, cGate *deviceGateIn, cGate *deviceGateOut) {
    ev<<"Adding device "<<device->getId()<<"\n";
    this->VLCdevices.insert(device);

    // Expand the gateVector to accommodate the new device
    int newGateVSize = gateSize("devicePort")+1;
    setGateSize("devicePort", newGateVSize);

    // Create the channel to and fro the device
    cIdealChannel *channelIn = cIdealChannel::create(NULL);
    cIdealChannel *channelOut = cIdealChannel::create(NULL);

    // Connect them
    gate("devicePort$o", newGateVSize-1)->connectTo(deviceGateIn, channelOut);
    deviceGateOut->connectTo(gate("devicePort$i", newGateVSize-1), channelIn);

    channelIn->callInitialize();
    channelOut->callInitialize();

    // Recompute the state of the network
    this->VLCcurrentViews[device] = this->devicesInFoVOf(device);
    this->recomputeView(this->VLCcurrentViews[device]);

    // Add the current view to the map
    VLCdeviceGates[device] = newGateVSize-1;
}

// Recomputes the view for all the devices in the set
void VLC::VLCchannel::recomputeView(std::set<VLCdevViewInfo> * devices) {
    std::pair<std::set<VLCdevViewInfo>::iterator, bool> viewResult;
    VLCdevViewInfo reverseView;
    for( auto &view : *devices){
        VLCdevice* other = (VLCdevice*) this->sim->getModule(view.device2);
        reverseView = invertedView(view);
        viewResult = this->VLCcurrentViews[other]->insert(reverseView);
        // If the element already existed update it
        if(!viewResult.second){
            (*viewResult.first).copyMutables(reverseView);
        }
    }
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
    //ev<<"Radiance angle is "<<devsPer.angle1<<"\n";

    // Do the same for the second device
    distanceVector = opposite(distanceVector);
    normalisedDistance = normalise(distanceVector);

    //ev<<"2 to 1 normalised vector:";
    //VLC::printVector(normalisedDistance);

    devsPer.angle2 = acos(dotProduct3d(dev2Direction, normalisedDistance));
    bool can2see1 = devsPer.angle2 <= dev2FoV;

    //ev<<"Can 2 see 1? "<<can2see1<<"\n";
    //ev<<"Incidence angle is "<<devsPer.angle2<<"\n";;

    devsPer.seeEachOther = can1see2 && can2see1;

    return devsPer;
}

// Creates a connection between the tx and rx
int VLC::VLCchannel::createConnection(VLCdevice * transmitter, VLCdevice * receiver) {
    VLC::VLCconnection* conn = this->connectionExists(transmitter, receiver);
    //ev<<"Creating connection\n";
    if( !conn ){
        std::pair<std::set<VLCconnection>::iterator, bool> inserted = this->VLCconnections.insert(VLCconnection(transmitter, receiver, this));

       // Yeah cast that constness away, promise I won't change them
        ((VLCtransmitter*) transmitter)->addConnectionStart(const_cast<VLCconnection*>(&(*inserted.first)));
        ((VLCreceiver*) receiver)->addConnectionEnd(const_cast<VLCconnection*>(&(*inserted.first)));

        // Add all the noise sources for this connection
        for( auto& view : *this->VLCcurrentViews[receiver]){
            VLCdevice* inView = (VLCdevice*) sim->getModule(view.device2);
            if( inView != transmitter){
                VLCdeviceType devType = inView->getDeviceType();
                if( devType == TRANSMITTER_DEVICE || devType == NOISE_DEVICE ){
                    inserted.first->addNoiseSource(inView);
                }
            }
        }

        inserted.first->updateConnection();
        this->updateChannel();

        return 0;
    }
    return -1;
}

// Terminates the connection between the tx and rx because the tx has sent the VLCchannelSignalEnd
int VLC::VLCchannel::dropConnection(VLCdevice * transmitter, VLCdevice * receiver) {
    VLC::VLCconnection* conn = this->connectionExists(transmitter, receiver);
    if(conn){

        ((VLCtransmitter*) transmitter)->removeConnectionStart(conn);
        ((VLCreceiver*) receiver)->removeConnectionEnd(conn);
        this->VLCconnections.erase((*conn));

        return 0;
    }
    return -1;
}

// Aborts the connection between tx and rx because the devices are no longer able to communicate
// this can be because they are too far apart or no longer in their respective FoVs
int VLC::VLCchannel::abortConnection(VLCdevice* transmitter, VLCdevice* receiver) {
    Enter_Method("abortConnection()");
    VLC::VLCconnection* conn = this->connectionExists(transmitter, receiver);
    if(conn){
        conn->abortConnection();
        ((VLCtransmitter*) transmitter)->removeConnectionStart(conn);
        ((VLCreceiver*) receiver)->removeConnectionEnd(conn);
        this->VLCconnections.erase(*conn);
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
        VLCconnection &c = *const_cast<VLCconnection*>(&(*conn));
        c.calculateNextValue();
        if(c.transmitter == transmitter){
            if( c.getOutcome() ){
                ev<<"Packet transmitted\n";
                cGate * receiverGate = gate("devicePort$o", this->VLCdeviceGates[const_cast<VLCdevice*>((VLCdevice*) c.receiver)]);
                send(pkt->dup(), receiverGate);
            }else{
                ev<<"Negative outcome\n";
            }

            // Close the connection
            conn->receiver->removeConnectionEnd(const_cast<VLCconnection*>(&(*conn)));
            conn->transmitter->removeConnectionStart(const_cast<VLCconnection*>(&(*conn)));
            this->VLCconnections.erase(conn++);

            continue;
        }
        conn++;
    }

    // Free the packet and remove it from the map
    delete this->transmitterMessages[transmitter];
    this->transmitterMessages.erase(transmitter);
}

// Signal the channel that the device has abruptly stopped transmitting
void VLC::VLCchannel::abortTransmission(VLCdevice* transmitter) {
    for( std::set <VLC::VLCconnection>::iterator conn = this->VLCconnections.begin(); conn != this->VLCconnections.end();){
        VLCconnection &c = *const_cast<VLCconnection*>(&(*conn));
        if(c.transmitter == transmitter){
            // Close the connection
            conn->abortConnection();
            conn->receiver->removeConnectionEnd(const_cast<VLCconnection*>(&(*conn)));
            conn->transmitter->removeConnectionStart(const_cast<VLCconnection*>(&(*conn)));
            this->VLCconnections.erase(conn++);
            continue;
        }
        conn++;
    }

    // Free the packet and remove it from the map
    delete this->transmitterMessages[transmitter];
    this->transmitterMessages.erase(transmitter);
}

// Compute all the necessary computations to step the simulation time forward, i.e., calculating the SINR for every
// active connection
void VLC::VLCchannel::updateChannel(){
    for( std::set<VLCconnection>::iterator conn = this->VLCconnections.begin(); conn != this->VLCconnections.end(); conn++){
        const VLCconnection &c = *conn;
        const_cast<VLCconnection&>(c).calculateNextValue();
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

    // Get the devices that went out of the FoV of the device
    std::set<VLCdevViewInfo> outDevices;
    std::set_difference(oldView->begin(), oldView->end(), newView->begin(), newView->end(), std::inserter(outDevices, outDevices.begin()) );

    //ev<<"Out devices\n";
    //printDevicesInFoV(&outDevices);

    // Get the devices that stayed into the FoV of the device
    std::set<VLCdevViewInfo> devicesToUpdate;
    std::set_difference(newView->begin(), newView->end(), newDevices.begin(), newDevices.end(),  std::inserter(devicesToUpdate, devicesToUpdate.begin()) );
    std::set_difference(newView->begin(), newView->end(), outDevices.begin(), outDevices.end(),  std::inserter(devicesToUpdate, devicesToUpdate.begin()) );

    //ev<<"Same devices\n";
    //printDevicesInFoV(&deviceToUpdate);

    VLCdevViewInfo devInfo;
    VLCdeviceType devType = device->getDeviceType();

    if( devType == TRANSMITTER_DEVICE || devType == RECEIVER_DEVICE){
        // Behold the power of ternary operators!
        std::set<VLCconnection*> connectionSet = (devType == TRANSMITTER_DEVICE)?((VLCtransmitter*) device)->getConnectionStarts():((VLCreceiver*) device)->getConnectionEnds();

        // Loop through the connections
        for(std::set<VLCconnection*>::iterator c = connectionSet.begin(); c != connectionSet.end(); c++){
            VLCconnection *conn = *c;
            // Build a devViewInfo for this connection
            devInfo = (VLCdevViewInfo) {conn->transmitter->getId(), conn->receiver->getId(), 0, 0.0, 0.0, 0.0};
            // If it is one of the devices that have gone out of view delete it and abort the connection
            if(outDevices.find(devInfo) != outDevices.end()){
                conn->abortConnection();
                ((VLCtransmitter*) device)->removeConnectionStart(conn);
                ((VLCreceiver*) device)->removeConnectionEnd(conn);
                this->VLCconnections.erase(*conn);
            }
        }
    }


    // Loop through the 3 new sets of:
    // Devices that have come into the FoV
    // Devices that stayed into the FoV
    // Devices that have gone out of the FoV
    // Perform the necessary actions for each case. These blocks are big and scary but ultimately they're just code repetition that could
    // have been avoided if one wanted to be more elegant...

    std::pair<std::set<VLCdevViewInfo>::iterator, bool> viewResult;
    VLCdevViewInfo reverseView;

    // Update the state of all the objects that can now see each other
    for( std::set<VLCdevViewInfo>::iterator newDevs = newDevices.begin(); newDevs != newDevices.end(); newDevs++){
        VLCdevice* newDevice = (VLCdevice*) this->sim->getModule(newDevs->device2);
        reverseView = invertedView(*newDevs);
        viewResult = this->VLCcurrentViews[newDevice]->insert(reverseView);
        // If the element somehow already existed update it
        if(!viewResult.second){
            (*viewResult.first).copyMutables(reverseView);
        }

        VLCdeviceType newDeviceType = newDevice->getDeviceType();

        // If the current device is an emitter and the new device is a receiver add it as a noise source to any connection the receiver has
        if( (devType == TRANSMITTER_DEVICE || devType == NOISE_DEVICE) && ( newDeviceType == RECEIVER_DEVICE ) ){
            const std::set<VLC::VLCconnection*>& receiverConnections = ((VLCreceiver*) newDevice)->getConnectionEnds();
            for( auto& conn : receiverConnections){
                conn->addNoiseSource(device);
                conn->updateConnection();
            }
        }
        // Else if the current device is a receiver add every new emitter device as a noise source to its connections
        else if( (devType == RECEIVER_DEVICE)  && ( newDeviceType == TRANSMITTER_DEVICE || newDeviceType == NOISE_DEVICE ) ){
            const std::set<VLC::VLCconnection*>& receiverConnections = ((VLCreceiver*) device)->getConnectionEnds();
            for( auto& conn : receiverConnections){
                conn->addNoiseSource(newDevice);
                conn->updateConnection();
            }
        }
    }

    // Update the state of all the objects that can still see each other
    for( std::set<VLCdevViewInfo>::iterator sameDevs = devicesToUpdate.begin(); sameDevs != devicesToUpdate.end(); sameDevs++){
        VLCdevice* sameDevice = (VLCdevice*) this->sim->getModule(sameDevs->device2);
        reverseView = invertedView(*sameDevs);
        viewResult = this->VLCcurrentViews[sameDevice]->insert(reverseView);
        // If the element already existed update it
        if(!viewResult.second){
            (*viewResult.first).copyMutables(reverseView);
        }

        VLCdeviceType sameDeviceType = sameDevice->getDeviceType();

        // If the current device is an emitter and the device to update is a receiver update it as a noise source to any connection the receiver has
        if( (devType == TRANSMITTER_DEVICE || devType == NOISE_DEVICE) && ( sameDeviceType == RECEIVER_DEVICE ) ){
            const std::set<VLC::VLCconnection*>& receiverConnections = ((VLCreceiver*) sameDevice)->getConnectionEnds();
            for( auto& conn : receiverConnections){
                // If he's the transmitter then it can't be a noise device
                if(conn->transmitter != device){
                    conn->updateNoiseSource(device);
                }
                conn->updateConnection();
            }
        }
        // Else if the current device is a receiver update every emitter device acting as a noise source to its connections
        else if( (devType == RECEIVER_DEVICE)  && ( sameDeviceType == TRANSMITTER_DEVICE || sameDeviceType == NOISE_DEVICE ) ){
            const std::set<VLC::VLCconnection*>& receiverConnections = ((VLCreceiver*) device)->getConnectionEnds();
            for( auto& conn : receiverConnections){
                // If the device is the transmitter then it can't be a noise device
                if(conn->transmitter != sameDevice){
                    conn->updateNoiseSource(sameDevice);
                }
                conn->updateConnection();
            }
        }
    }

    // Update the view of all the objects that can no longer see each other
    for( std::set<VLCdevViewInfo>::iterator outDevs = outDevices.begin(); outDevs != outDevices.end(); outDevs++){
        VLCdevice* outDevice = (VLCdevice*) this->sim->getModule(outDevs->device2);
        reverseView = invertedView(*outDevs);
        this->VLCcurrentViews[outDevice]->erase(reverseView);

        VLCdeviceType outDeviceType = outDevice->getDeviceType();

        // If the current device is an emitter and the out device is a receiver remove it from the noise sources of any connection the receiver has
        if( (devType == TRANSMITTER_DEVICE || devType == NOISE_DEVICE) && ( outDeviceType == RECEIVER_DEVICE ) ){
            const std::set<VLC::VLCconnection*>& receiverConnections = ((VLCreceiver*) outDevice)->getConnectionEnds();
            for( auto& conn : receiverConnections){
                conn->removeNoiseSource(device);
                conn->updateConnection();
            }
        }
        // Else if the current device is a receiver remove every out emitter device from the noise sources to its connections
        else if( (devType == RECEIVER_DEVICE)  && ( outDeviceType == TRANSMITTER_DEVICE || outDeviceType == NOISE_DEVICE ) ){
            const std::set<VLC::VLCconnection*>& receiverConnections = ((VLCreceiver*) device)->getConnectionEnds();
            for( auto& conn : receiverConnections){
                conn->removeNoiseSource(outDevice);
                conn->updateConnection();
            }
        }
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
    cIdealChannel *c = cIdealChannel::create(NULL);
    mobilityGate->connectTo(gate("mobilityPort", gateSize("mobilityPort")-1), c);
    c->callInitialize();
}


VLC::VLCdevViewInfo VLC::VLCchannel::getDevViewInfo(VLCdevice * transmitter, VLCdevice * receiver){
    // Build a devViewInfo for this connection
    VLCdevViewInfo devInfo = (VLCdevViewInfo) {transmitter->getId(), receiver->getId(), 0, 0.0, 0.0, 0.0};
    std::set<VLCdevViewInfo>::iterator devView = (this->VLCcurrentViews[transmitter]->find(devInfo));
    if(devView == this->VLCcurrentViews[transmitter]->end()){
        VLCdevViewInfo viewInfo = this->devsPerspective(transmitter, receiver);
        this->VLCcurrentViews[transmitter]->insert(viewInfo);
        return viewInfo;
    }
    return *devView;

}
