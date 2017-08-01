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

// A move message indicates that either the tx or rx has altered 
// its position or orientation in space.

message VLCmoveMsg{
    int nodeId;
    // The position of the node given in meters
    double x;
    double y;
    double z;
    
    // The angles on the xy and xz planes. We ignore the roll
    double alpha;
    double beta;
}

message VLCchannelSignalBegin{
	int nodeId;
	double power;
	double carrierFreq;
	int modulationType;
}

message VLCchannelSignalEnd{
    int nodeId;
}
