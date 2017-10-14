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

enum VLCmsgType{
    VLC_CTRL_MSG = 0;
    VLC_DATA_MSG = 1;
    VLC_MAC_MSG = 2;
};

enum VLCctrlCode{
	// Codes for the status of the transmission
	TRANSMISSION_BEGIN = 0;
    TRANSMISSION_END = 1;
	TRANSMISSION_ABORT = 2;
    
		
	// Codes for the status of the device		
	DEVICE_BUSY = 3; 
	DEVICE_MOVED = 4;
	NOISE_DEVICE_CHANGED = 5;
	
	// Codes for controlling the transmission
	ABORT_TRANSMISSION = 6;
	
	// Codes for controlling the transmission
	VPPM_CYCLE_DOWN = 7;
	
	// Codes for the app
	NEW_PACKET = 8;
	
	//Codes for the receiver
	CHECK_BEACON = 9;
	
};

enum VLCMACCode{
    BEACON_MSG = 0;
    SUBSCRIBE_MSG = 1;
    UNSUBSCRIBE_MSG = 2;
}

enum VLCmodulationType{
    PAM = 0;
    VPPM = 1;
}

packet VLCpacket{
	int messageType @enum(VLCmsgType);
};

packet VLCctrlMsg extends VLCpacket{
    int nodeId;
    int nodeAddress;
    int ctrlCode @enum(VLCctrlCode);
};

packet VLCnoiseControlMsg extends VLCctrlMsg{
    double noisePower;
};

packet VLCMACMsg extends VLCpacket{
    int MACCode @enum(VLCMACCode);
    int transmitterNodeId;
    int transmitterNodeAddress;
    int receiverNodeIde;
    int receiverNodeAddress;
};

packet VLCBeaconMsg extends VLCMACMsg{
    int modulationType @enum(VLCmodulationType);
    double transmissionPower;
    int modulationOrder;
    double dutyCycle;
}

packet dataPacket extends VLCpacket{
    int modulationType @enum(VLCmodulationType);
    double transmissionPower;
    int modulationOrder;
    double dutyCycle;
	string content;
	double transmissionStartTime;
	int sourceAddress;
	int destinationAddress;
};
    
