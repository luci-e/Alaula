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
        int receiverAddress;

        string mobilityParameters;
        @display("bgb=225,86");

    gates:
        inout receiverPort;

    submodules:
        device: VLCreceiver {
            parameters:
                devPars = deviceParameters;
                address = receiverAddress;
                @display("p=47,35");
        }

        mobilityManager: VLCmobilityManager {
            mobilityPars = mobilityParameters;
            @display("p=150,35");
        }
    connections:
        receiverPort <--> device.controllerPort;
}
