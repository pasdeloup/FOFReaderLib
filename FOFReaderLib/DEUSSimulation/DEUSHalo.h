/* ************************** FOFReaderLib ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        FOFReaderLib
// TITLE :          DEUSHalo
// DESCRIPTION :    Single halo value object
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2014)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           DEUSHalo.h
/// \brief          Single halo value object
/// \author         Jean Pasdeloup (jean.pasdeloup@obspm.fr)
/// \date           2014
/// \copyright      CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/

#ifndef DEUSHALO_H
#define	DEUSHALO_H

#include "../FOFFiles/FOFParticles.h"

class DEUSHalo {
public:
    DEUSHalo();
    DEUSHalo(float x, float y, float z, int mass, int fileindex, int haloindex): _x(x), _y(y), _z(z), _mass(mass), _fileindex(fileindex), _haloindex(haloindex), _particles(0) {}
    DEUSHalo(const DEUSHalo& orig);
    virtual ~DEUSHalo();
    
    float x() {return _x;}
    float y() {return _y;}
    float z() {return _z;}
    float mass() {return _mass;}
    int fileindex() {return _fileindex;}
    int haloindex() {return _haloindex;}
    FOFParticles *particles(){return _particles;}
    void calculateAvgVelocity(float *coords);
    void particles(FOFParticles *particles){_particles = particles;}    
    
private:    
    float _x;
    float _y;
    float _z;
    int  _mass;
    int _fileindex;
    int _haloindex;    
    FOFParticles *_particles;
};

#endif	/* DEUSHALO_H */

