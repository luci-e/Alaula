/*
 * VLCcommons.h
 *
 *  Created on: Jul 30, 2017
 *      Author: casper
 */

#ifndef VLCCONSTS_H_
#define VLCCONSTS_H_

#include <math.h>
#include <string>
#include <set>
#include <simtime.h>

#define VLC_CHANNEL_NAME "vlcChannel"

// Constants for messages to channel identification
#define CH_MOVE_MSG 0
#define CH_BEGIN_COMM_MSG 1
#define CH_END_COMM_MSG 2

namespace VLC{
    typedef struct VLCnodePosition{
        double x, y, z;
        double alpha, beta;
    }VLCnodePosition;

    void printPosition(VLCnodePosition np);


    typedef struct vector3d{
        double x, y, z;
    }vector3d;

    void printVector(vector3d v);

    typedef vector3d VLCnodeDirection;

    struct VLCdevViewInfo{
        int device1, device2;
        bool seeEachOther;
        double distance;
        double angle1, angle2;

        inline bool operator()(const VLCdevViewInfo& vi1, const VLCdevViewInfo& vi2) const{
            if( vi1.device1 < vi2.device1 ){
                return true;
            }

            if( vi1.device1 == vi2.device1 ){
                return vi1.device2 < vi2.device2;
            }

            return false;
        }

        inline bool operator<(const VLCdevViewInfo& vi2) const{
            if( device1 < vi2.device1 ){
                return true;
            }

            if( device1 == vi2.device1 ){
                return device2 < vi2.device2;
            }

            return false;
        }

        inline bool operator==(const VLCdevViewInfo& vi2) const{
            return (device1 == vi2.device1) && (device2 == vi2.device2);
        }

        inline VLCdevViewInfo& operator=(const VLC::VLCdevViewInfo& other){
            device1 = other.device1;
            device2 = other.device2;
            seeEachOther = other.seeEachOther;
            distance = other.distance;
            angle1 = other.angle1;
            angle2 = other.angle2;

            return *this;
        }
    };

    void printDevViewInfo( VLCdevViewInfo devView);

    void printDevicesInFoV(std::set<VLCdevViewInfo> *deviceSet);

    // Inverts the given view, that is, device1 swaps with 2, angle1 swaps with 2
    VLCdevViewInfo invertedView( VLCdevViewInfo view);

    typedef struct VLCtimeSINR{
        SimTime time;
        double SINR;
    }VLCtimeSINR;

    // Normalise the vector
    vector3d normalise(vector3d vector);

    // Returns the opposite of the given vector
    vector3d opposite(vector3d vector);

    // Returns the value of the dot product between the 2 vectors
    double dotProduct3d(vector3d v1, vector3d v2);

    // Performs scalar multiplication between the given scalar and vector
    vector3d scalarMult3d(double scalar, vector3d vector);

    // Returns the distance between the to nodes
    double distance(VLCnodePosition pos1, VLCnodePosition pos2);

    // Calculate the versor given by the alpha and beta angles in spherical coordinates
    vector3d calculateVersor(double alpha, double beta);

    // Generates a random string of length length
    char* randomString( size_t length );

    // The phi function aka ϕunction
    double phi(double x);
}

#endif /* VLCCONSTS_H_ */
