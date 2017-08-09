/*
 * VLCcommons.cc
 *
 *  Created on: Aug 1, 2017
 *      Author: casper
 */

#include <VLCcommons.h>
#include <random>
#include <omnetpp.h>


namespace VLC{
    void printPosition(VLCnodePosition np){
        ev<<"X: "<<np.x<<" Y: "<<np.y<<" Z: "<<np.z<<" Alpha: "<<np.alpha<<" Beta: "<<np.beta<<"\n";
    }

    void printVector(vector3d v){
        ev<<"X: "<<v.x<<" Y: "<<v.y<<" Z: "<<v.z<<"\n";
    }

    vector3d normalise(vector3d vector){
        double norm = sqrt( vector.x*vector.x + vector.y*vector.y + vector.z*vector.z);
        return {vector.x / norm, vector.y /norm, vector.z /norm};
    }

    vector3d opposite(vector3d vector){
        return {-vector.x, -vector.y, -vector.z};
    }

    double dotProduct3d(vector3d v1, vector3d v2){
        return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
    }

    double distance(VLCnodePosition pos1, VLCnodePosition pos2){
        return sqrt((pos1.x-pos2.x)*(pos1.x-pos2.x) + (pos1.y-pos2.y)*(pos1.y-pos2.y) + (pos1.z-pos2.z)*(pos1.z-pos2.z));
    }

    char* randomString( size_t length )
    {
        auto randchar = []() -> char
        {
            const char charset[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
            const size_t max_index = (sizeof(charset) - 1);
            return charset[ rand() % max_index ];
        };
        char * str = new char[length+1];
        for(int i = 0; i< length-2; i++){
            str[i] = randchar();
        }
        return str;
    }
}


