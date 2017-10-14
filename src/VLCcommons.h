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
#include <vector>
#include <string>

#define VLC_CHANNEL_NAME "vlcChannel"

namespace VLC{

    static const double q = 1.602176487e-19;        //electronic charge [Coulombs]
    static const double k = 1.38064852e-23;     //Boltzmann constant [m^2 kg s^-2 K^-1]

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
        mutable bool seeEachOther;
        mutable double distance;
        mutable double angle1, angle2;

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

        inline void copyMutables( VLC::VLCdevViewInfo& other ) const{
            seeEachOther = other.seeEachOther;
            distance = other.distance;
            angle1 = other.angle1;
            angle2 = other.angle2;
        }
    };

    void printDevViewInfo( VLCdevViewInfo devView);

    void printDevicesInFoV(std::set<VLCdevViewInfo> *deviceSet);

    // Inverts the given view, that is, device1 swaps with 2, angle1 swaps with 2
    VLCdevViewInfo invertedView( VLCdevViewInfo view);

    struct VLCtimeSINR{
        double time;
        double SINR;

        VLCtimeSINR(double t, double s){
            time = t;
            SINR = s;
        };
    };

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

    // The Q function
    double Qfunction(double x);

    // Explode the string into tokens with given delimiter, in rare cases explode the computer instead
    const std::vector<std::string> explode(const std::string& s, const char& c);
}

#endif /* VLCCONSTS_H_ */
