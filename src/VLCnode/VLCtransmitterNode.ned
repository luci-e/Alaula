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
import ned.IdealChannel;
import vlc.src.VLCnode.**.*;

module VLCtransmitterNode
{
    parameters:
        string deviceParameters;

        string mobilityType;
        string mobilityParameters;
        @display("bgb=271,165");

    gates:
        inout transmitterPort[];

    submodules:
        device: VLCtransmitter {
            parameters:
                devPars = deviceParameters;
                @display("p=66,118");
        }

        mobilityManager: <mobilityType> like VLCmobilityManager {
            mobilityPars = mobilityParameters;
            @display("p=198,118");
        }
        
        vlCnodeQueue: VLCnodeQueue {
            @display("p=66,43;b=40,40");
        }
        
    connections:
        vlCnodeQueue.devicePort <--> device.queuePort;
        for i=0..sizeof(transmitterPort)-1 {
    		transmitterPort[i] <--> vlCnodeQueue.queuePort++;
        }
}
