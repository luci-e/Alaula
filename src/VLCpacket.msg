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
    VLC_MOVE_MSG = 0;
    
    VLC_SIG_BEGIN_MSG = 1;
    VLC_SIG_END_MSG = 2;
    
    VLC_CTRL_MSG = 3;
    VLC_DATA_MSG = 4;
    
    VLC_NOISE_MSG = 5;
};

enum VLCctrlCode{
	// Codes for the status of the transmission
	TRANSMISSION_DONE = 0;
	TRANSMISSION_ABORTED = 1;
		
	// Codes for the status of the device		
	DEVICE_BUSY = 2; 
	
	// Codes for controlling the transmission
	ABORT_TRANSMISSION = 3;
};

enum VLCmodulationType{
    PAM = 0;
    VPPM = 1;
}

packet VLCpacket{
	int messageType @enum(VLCmsgType);
};

packet VLCmoveMsg extends VLCpacket{
    int nodeId;
};

packet VLCchannelSignalBegin extends VLCpacket{
    int nodeId;
};

packet VLCchannelSignalEnd extends VLCpacket{
    int nodeId;
};

packet VLCnoiseMsg extends VLCpacket{
    int nodeId;
};

packet VLCctrlMsg extends VLCpacket{
    int ctrlCode @enum(VLCctrlCode);
};

packet VLCnoiseControlMsg extends VLCctrlMsg{
    double noisePower;
};

packet dataPacket extends VLCpacket{
    int modulationType @enum(VLCmodulationType);
    double transmissionPower;
    int modulationOrder;
    double dutyCycle;
	string content;
	double transmissionStartTime;
};
    
