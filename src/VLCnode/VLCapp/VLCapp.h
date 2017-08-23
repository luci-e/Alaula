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

#ifndef VLCAPP_H_
#define VLCAPP_H_

#include <omnetpp.h>

namespace VLC{
    class VLCapp : public ::cSimpleModule{
        private:
            int packetSize = 32;
            double transmissionInterval = 100;
        public:
            VLCapp();
            virtual ~VLCapp();
        protected:
            void initialize();
            virtual void handleMessage(cMessage *msg);
    };

    Define_Module(VLCapp);
}

#endif /* VLCAPP_H_ */
