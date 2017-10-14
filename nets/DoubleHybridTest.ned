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


network DoubleHybridTest
{
    @display("bgb=531,608");
    submodules:
        vlcChannel: VLCchannel {
            @display("p=272,308;b=250,50");
        }
        vlcNetController: VLCnetController {
            @display("p=272,134;b=250,50");
        }
        vlcApp: VLCapp {
            @display("p=172,44;b=50,50");
        }
        transmitterNode: VLCtransmitterNode {
            @display("p=172,224;b=50,50");
        }
        transmitterNode1: VLCtransmitterNode {
            @display("p=372,224;b=50,50");
        }

        receiverNode: VLCreceiverNode {
            @display("p=372,512;b=50,50");
        }
        vlcReceiverController: VLCreceiverController {
            @display("p=372,431;b=50,50");
        }
        vlcApp1: VLCapp {
            @display("p=488,431;b=50,50");
        }
        receiverNode1: VLCreceiverNode {
            @display("p=172,512;b=50,50");
        }
        vlcApp2: VLCapp {
            @display("p=50,431;b=50,50");
        }
        vlcReceiverController1: VLCreceiverController {
            @display("p=172,431;b=50,50");
        }
        vlcApp3: VLCapp {
            @display("p=378,44;b=50,50");
        }
    connections:
        transmitterNode.transmitterPort <--> vlcNetController.VLCport++;
        transmitterNode1.transmitterPort <--> vlcNetController.VLCport++;
        vlcApp.appGate++ <--> vlcNetController.appPort++;
        vlcReceiverController.devicePort <--> receiverNode.receiverPort;
        vlcReceiverController.appPort <--> vlcApp1.appGate++;
        vlcReceiverController.wirelessPort <--> DatarateChannel {  datarate = 10Mbps; } <--> vlcNetController.wirelessPort++;
        vlcReceiverController1.devicePort <--> receiverNode1.receiverPort;
        vlcReceiverController1.appPort <--> vlcApp2.appGate++;
        vlcReceiverController1.wirelessPort <--> DatarateChannel {  datarate = 10Mbps; } <--> vlcNetController.wirelessPort++;

        vlcApp3.appGate++ <--> vlcNetController.appPort++;
}
