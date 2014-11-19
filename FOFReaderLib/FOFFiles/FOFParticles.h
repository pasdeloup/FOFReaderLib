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
    FOFParticles(std::string filename,int npart, std::streamoff position, int mode = READ_POS | READ_VEL);
    
    virtual ~FOFParticles();
    
    const static int DONT_READ_PARTICLES = 0;
    const static int READ_POS = 1;
    const static int READ_VEL = 2;
    const static int READ_IDS = 4;
    const static int READ_ALL = READ_POS | READ_VEL | READ_IDS;
    
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
    
    long long id(int i) {return _id[i];}
    
// Reader    
    void setStreampos();
    void readParticles(int mode = READ_POS | READ_VEL); // Read particles    
    void skipParticles();
    void releaseParticles(); // Remove particles to free memory
    
protected:
    int _npart;
    std::vector<float> _position;
    std::vector<float> _velocity;
    std::vector<long long> _id;  
    std::streamoff _streampos; // position of the start of particles in the file
};

#endif	/* FOFPARTICLES_H */

