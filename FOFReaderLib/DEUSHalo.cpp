/* ********************************** CELL ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        DEUS_SERVER
// TITLE :          DEUSHalo
// DESCRIPTION :    Mesh cells integrating particles
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2013)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           DEUSHalo.cpp
/// \brief          Mesh cells integrating particles
/// \author         Jean Pasdeloup (jean.pasdeloup@obspm.fr)
/// \date           2013
/// \copyright      CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/

#include "DEUSHalo.h"

DEUSHalo::DEUSHalo()
{
}

DEUSHalo::DEUSHalo(const DEUSHalo& orig)
{
}

DEUSHalo::~DEUSHalo()
{
}

void DEUSHalo::calculateAvgVelocity(float *coords)
{
    if(this->_particles == 0) { // Particles needed
        return;
    }
    coords[0] = coords[1] = coords[2] = 0.0f;
    for(int i=0; i<this->_mass; i++) {
        coords[0] += this->_particles->velX(i);
        coords[1] += this->_particles->velY(i);
        coords[2] += this->_particles->velZ(i);
    }
    coords[0] /= this->_mass;
    coords[1] /= this->_mass;
    coords[2] /= this->_mass;
    return;    
}


