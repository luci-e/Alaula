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


@namespace(VLC);

network VLCnetwork
{
    @display("bgb=605,383");
    submodules:
        vlcChannel: VLCchannel {
            @display("p=298,322;b=574,61");
        }
        vlCnode: VLCnode {
            @display("p=76,184;b=131,110");
        }
        vlCnode1: VLCnode {
            @display("p=297,184;b=131,110");
        }
        vlCnode2: VLCnode {
            @display("p=519,184;b=131,110");
        }
}
