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

import ned.DatarateChannel;
import vlc.src.VLCchannel.VLCchannel;
import vlc.src.VLCnode.VLCnetController.VLCnetController;
import vlc.src.VLCnode.VLCapp.VLCapp;
import vlc.src.VLCnode.VLCreceiverController.VLCreceiverController;
import vlc.src.VLCnode.VLCreceiverNode;
import vlc.src.VLCnode.VLCtransmitterNode;


network HybridTest
{
    @display("bgb=341,608");
    submodules:
        vlcChannel: VLCchannel {
            @display("p=164,308;b=250,50");
        }
        vlcNetController: VLCnetController {
            @display("p=164,134;b=250,50");
        }
        vlcApp: VLCapp {
            @display("p=164,56;b=50,50");
        }
        transmitterNode: VLCtransmitterNode {
            @display("p=64,224;b=50,50");
        }
        transmitterNode1: VLCtransmitterNode {
            @display("p=264,224;b=50,50");
        }

        receiverNode: VLCreceiverNode {
            @display("p=64,431;b=50,50");
        }
        vlcReceiverController: VLCreceiverController {
            @display("p=264,431;b=50,50");
        }
        vlcApp1: VLCapp {
            @display("p=264,525;b=50,50");
        }
    connections:
        transmitterNode.transmitterPort <--> vlcNetController.VLCport++;
        transmitterNode1.transmitterPort <--> vlcNetController.VLCport++;
        vlcApp.appGate++ <--> vlcNetController.appPort++;
        vlcReceiverController.devicePort <--> receiverNode.receiverPort;
        vlcReceiverController.appPort <--> vlcApp1.appGate++;
        vlcReceiverController.wirelessPort <--> DatarateChannel {  datarate = 10Mbps; } <--> vlcNetController.wirelessPort++;
}
