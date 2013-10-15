/* ********************************** CELL ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        FOF_READER_LIB
// TITLE :          FOFParticles
// DESCRIPTION :    Mesh cells integrating particles
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2013)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           FOFParticles.h
/// \brief          Mesh cells integrating particles
/// \author         Jean Pasdeloup (jean.pasdeloup@obspm.fr)
/// \date           2013
/// \copyright      CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/

#ifndef FOFPARTICLES_H
#define	FOFPARTICLES_H

#include "FOFFile.h"

class FOFParticles : protected FOFFile
{
public:
    FOFParticles();
    FOFParticles(const FOFParticles& orig);
    FOFParticles(FortranFile<unsigned int> *_fortranFile);
    virtual ~FOFParticles();
    
    // Getters
    int npart() {return _npart;}
    std::vector<float> position() {return _position;}
    std::vector<float> velocity() {return _velocity;}
    std::vector<long long int> id() {return _id;}
    
    // Setter
    void npart(int npart) {this->_npart = npart;}
    
    // Enhanced getters
    float posX(int i) {return _position[i * 3];}
    float posY(int i) {return _position[i * 3 + 1];}
    float posZ(int i) {return _position[i * 3 + 2];}
    
    float velX(int i) {return _velocity[i * 3];}
    float velY(int i) {return _velocity[i * 3 + 1];}
    float velZ(int i) {return _velocity[i * 3 + 2];}
    float velNorm(int i) {return _velocity[i * 3] * _velocity[i * 3] + _velocity[i * 3 + 1] * _velocity[i * 3 + 1] + _velocity[i * 3 + 2] * _velocity[i * 3 + 2];}
    
    float id(int i) {return _id[i];}
    
// Reader
    void readParticles(int len, bool readIds=false);    
    
protected:
    int _npart;    
    std::vector<float> _position;
    std::vector<float> _velocity;
    std::vector<long long> _id;
    
};

#endif	/* FOFPARTICLES_H */

