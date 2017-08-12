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

    VLCdevViewInfo invertedView( VLCdevViewInfo view);

    typedef struct VLCtimeSINR{
        double time;
        double SINR;
    }VLCtimeSINR;

    vector3d normalise(vector3d vector);

    vector3d opposite(vector3d vector);

    double dotProduct3d(vector3d v1, vector3d v2);

    double distance(VLCnodePosition pos1, VLCnodePosition pos2);

    char* randomString( size_t length );
}

#endif /* VLCCONSTS_H_ */
