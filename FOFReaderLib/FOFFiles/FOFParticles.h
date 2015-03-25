/* ************************** FOFReaderLib ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        FOFReaderLib
// TITLE :          FOFParticles
// DESCRIPTION :    Intermediate class for formats managing particles
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2013)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           FOFParticles.h
/// \brief          Intermediate class for formats managing particles
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
    std::string getFilename() {return this->_filename;};
    
    // Setter
    void npart(int npart) {this->_npart = npart; if(this->_originalNpart == 0) {this->_originalNpart = npart;}}
    void setPos(int i, float x, float y, float z) { _position[i * 3] = x; _position[i * 3 + 1] = x; _position[i * 3 + 2] = x; }
                
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
    void readParticles(int mode = READ_POS | READ_VEL, bool closefile = true); // Read particles, close file after by default
    void skipParticles();
    void releaseParticles(); // Remove particles to free memory

    // Manipulate data    
    void removeParticle(int i, bool virtually=false); // Remove a specific particle, if virtually=true: put it to infinity position
    void removeParticleInInfinity(); // Remove physically particle put to infinity    
    void divideNpart(int divider = 8) {this->_npart = this->_npart / divider;} // Reduce npart using a ratio, 1/8 by default (=1024^3 -> 512^3 for instance)
    void divideNpart(float divider = 8.0) {this->_npart = (int) this->_npart / divider;} // Reduce npart using a ratio, 1/8 by default (=1024^3 -> 512^3 for instance)
    
protected:
    int _originalNpart;
    int _npart;    
    std::vector<float> _position;
    std::vector<float> _velocity;
    std::vector<long long> _id;  
    std::streamoff _streampos; // position of the start of particles in the file
    void reduceNpart(int newNpart); // Reduce npart by removing randomly particles
};

#endif	/* FOFPARTICLES_H */

