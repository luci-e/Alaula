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

#ifndef VLCLINEMOBILITYMANAGER_H_
#define VLCLINEMOBILITYMANAGER_H_

#include <VLCmobilityManager.h>

namespace VLC{
    class VLClineMobilityManager : public VLC::VLCmobilityManager{
        protected:
            void initialize();
            void handleMessage(cMessage* cMsg);

        public:
            VLClineMobilityManager();
            ~VLClineMobilityManager();

            void moveNode();
            void rotateNode();
    };
    Define_Module(VLClineMobilityManager);
}

#endif /* VLCLINEMOBILITYMANAGER_H_ */
