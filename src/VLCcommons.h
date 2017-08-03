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

namespace VLC{
    typedef struct VLCnodePosition{
        double x, y, z;
        double alpha, beta;
    }VLCnodePosition;


    typedef struct vector3d{
        double x, y, z;
    }vector3d;

    typedef vector3d VLCnodeDirection;

    typedef struct VLCdevViewInfo{
        int device1, device2;
        bool seeEachOther;
        double distance;
        double angle1, angle2;
    }VLCdevViewInfo;

    vector3d normalise(vector3d vector);

    vector3d opposite(vector3d vector);

    double dotProduct3d(vector3d v1, vector3d v2);

    double distance(VLCnodePosition pos1, VLCnodePosition pos2);

    char* randomString( size_t length );
}

#endif /* VLCCONSTS_H_ */
