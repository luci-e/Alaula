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

package vlc.src.VLCnode;
import ned.DelayChannel;
import ned.IdealChannel;

import vlc.src.VLCnode.*.*;
import vlc.src.VLCnode.*.*.*;


module VLCreceiverNode
{
    parameters:
        string deviceParameters;

        string mobilityParameters;
        @display("bgb=257,170");

    gates:
        inout receiverPort[];

    submodules:
        device: VLCreceiver {
            parameters:
                devPars = deviceParameters;
                @display("p=58,119");
        }

        mobilityManager: VLCmobilityManager {
            mobilityPars = mobilityParameters;
            @display("p=186,119");
        }
        vlCnodeQueue: VLCnodeQueue {
            @display("p=58,38;b=40,41");
        }
    connections:
        vlCnodeQueue.devicePort <--> device.queuePort;
        for i=0..sizeof(receiverPort)-1 {
    		receiverPort[i] <--> vlCnodeQueue.queuePort++;
        }
}
