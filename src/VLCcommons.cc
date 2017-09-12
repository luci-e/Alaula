/*
 * VLCcommons.cc
 *
 *  Created on: Aug 1, 2017
 *      Author: casper
 */

#include <VLCcommons.h>
#include <random>
#include <omnetpp.h>
#include <set>
#include <cmath>
#include <vector>


namespace VLC{
    void printDevicesInFoV(std::set<VLCdevViewInfo> *deviceSet){
        for( std::set<VLCdevViewInfo>::iterator dev = deviceSet->begin(); dev != deviceSet->end(); dev++){
            VLCdevViewInfo devView = *dev;
            printDevViewInfo(devView);
        }
    }


    void printDevViewInfo( VLCdevViewInfo devView){
        ev<<"{\n\tdevice1: "<<devView.device1<<"\n\tdevice2: "<<devView.device2<<"\n\tseeEachOther: "<<devView.seeEachOther<<"\n\tangle1: "<<devView.angle1<<"\n\tangle2: "<<devView.angle2<<"\n\tdistance: "<<devView.distance<<"\n}\n";
    }
    // Inverts the given view, that is, device1 swaps with 2, angle1 swaps with 2
    VLCdevViewInfo invertedView( VLCdevViewInfo view){
        return {view.device2, view.device1, view.seeEachOther, view.distance, view.angle2, view.angle1};
    }

    void printPosition(VLCnodePosition np){
        ev<<"X: "<<np.x<<" Y: "<<np.y<<" Z: "<<np.z<<" Alpha: "<<np.alpha<<" Beta: "<<np.beta<<"\n";
    }

    void printVector(vector3d v){
        ev<<"X: "<<v.x<<" Y: "<<v.y<<" Z: "<<v.z<<"\n";
    }

    // Normalise the vector
    vector3d normalise(vector3d vector){
        double norm = sqrt( vector.x*vector.x + vector.y*vector.y + vector.z*vector.z);
        return {vector.x / norm, vector.y /norm, vector.z /norm};
    }

    // Returns the opposite of the given vector
    vector3d opposite(vector3d vector){
        return {-vector.x, -vector.y, -vector.z};
    }

    // Returns the value of the dot product between the 2 vectors
    double dotProduct3d(vector3d v1, vector3d v2){
        return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
    }

    // Returns the distance between the to nodes
    double distance(VLCnodePosition pos1, VLCnodePosition pos2){
        return sqrt((pos1.x-pos2.x)*(pos1.x-pos2.x) + (pos1.y-pos2.y)*(pos1.y-pos2.y) + (pos1.z-pos2.z)*(pos1.z-pos2.z));
    }

    // Performs scalar multiplication between the given scalar and vector
    vector3d scalarMult3d(double scalar, vector3d vector) {
        return {scalar*vector.x, scalar*vector.y, scalar*vector.z};
    }

    // Calculate the versor given by the alpha and beta angles in spherical coordinates
    vector3d calculateVersor(double alpha, double beta){
        return {
            sin(beta)*cos(alpha),
            sin(beta)*sin(alpha),
            cos(beta)
        };
    }

    // Generates a random string of length length
    char* randomString( size_t length )
    {
        auto randchar = []() -> char
        {
            const char charset[] =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
            const size_t max_index = (sizeof(charset) - 1);
            return charset[ rand() % max_index ];
        };
        char * str = new char[length];
        for(int i = 0; i < length - 1; i++){
            str[i] = randchar();
        }

        return str;
    }

    // The Q function
    double Qfunction(double x){
        return 0.5 * erfc(x / M_SQRT1_2);
    }

    // Explode the string into tokens with given delimiter, in rare cases explode the computer instead
    const std::vector<std::string> explode(const std::string& s, const char& c)
    {
        std::string buff{""};
        std::vector<std::string> v;

        for(auto n:s)
        {
            if(n != c) buff+=n; else
            if(n == c && buff != "") { v.push_back(buff); buff = ""; }
        }
        if(buff != "") v.push_back(buff);

        return v;
    }
}


