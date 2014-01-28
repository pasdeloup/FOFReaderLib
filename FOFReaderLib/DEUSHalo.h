/* ********************************** CELL ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        DEUS_SERVER
// TITLE :          DEUSHalo
// DESCRIPTION :    Mesh cells integrating particles
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2013)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           DEUSHalo.h
/// \brief          Mesh cells integrating particles
/// \author         Jean Pasdeloup (jean.pasdeloup@obspm.fr)
/// \date           2013
/// \copyright      CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/

#ifndef DEUSHALO_H
#define	DEUSHALO_H

#include "FOFParticles.h"

class DEUSHalo {
public:
    DEUSHalo();
    DEUSHalo(float x, float y, float z, int mass, int fileindex, int haloindex): _x(x), _y(y), _z(z), _mass(mass), _fileindex(fileindex), _haloindex(haloindex) {}
    DEUSHalo(const DEUSHalo& orig);
    virtual ~DEUSHalo();
    
    float x() {return _x;}
    float y() {return _y;}
    float z() {return _z;}
    float mass() {return _mass;}
    float fileindex() {return _fileindex;}
    float haloindex() {return _haloindex;}
    FOFParticles *particles(){return _particles;}
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

