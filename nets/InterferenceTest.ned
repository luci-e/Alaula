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

package vlc.nets;
import ned.*;
import vlc.src.VLCchannel.*;

import vlc.src.VLCnode.*;
import vlc.src.VLCnode.*.*;
import vlc.src.VLCnode.*.*.*;


@namespace(VLC);

network InterferenceTest
{
    @display("bgb=605,543");
    submodules:
        vlcChannel: VLCchannel {
            @display("p=300,322;b=570,61");
        }
        packetSource: VLCapp {
            @display("p=43,65;b=56,57");
        }
        receiverNode: VLCreceiverNode {
            @display("p=297,457;b=131,110");
        }
        transmitterNode: VLCtransmitterNode {
            @display("p=80,184;b=131,110");
        }
        transmitterNode1: VLCtransmitterNode {
            @display("p=519,184;b=131,110");
        }
        packetSource1: VLCapp {
            @display("p=557,65;b=56,57");
        }
    connections:
        packetSource.appGate <--> transmitterNode.transmitterPort++;
        packetSource1.appGate <--> transmitterNode1.transmitterPort++;
}
