/* ********************************** CELL ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        FOF_READER_LIB
// TITLE :          FOFParticles
// DESCRIPTION :    Mesh cells integrating particles
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2013)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           FOFParticles.cpp
/// \brief          Mesh cells integrating particles
/// \author         Jean Pasdeloup (jean.pasdeloup@obspm.fr)
/// \date           2013
/// \copyright      CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/

#include "FOFParticles.h"
#include "FOFFile.h"
#include "FOFCube.h"

FOFParticles::FOFParticles()
{
}

FOFParticles::FOFParticles(FortranFile<unsigned int> *fortranFile)
{
    this->_fortranFile = fortranFile;
    this->_fortranFileMaster = false;
    this->_streampos = 0;
}

FOFParticles::FOFParticles(std::string filename, int npart, std::streamoff position)
{
    this->_streampos = position;
    this->_filename = filename;
    this->_npart = npart;
        
    this->readParticles();    
}

FOFParticles::FOFParticles(const FOFParticles& orig)
{
}

FOFParticles::~FOFParticles()
{   
}

/**
 * Read the particles
 * @param readIds read or skip ids (faster to skip, not ever usefuls)
 */
void FOFParticles::readParticles(bool readIds)
{
    int len = this->_npart;
#ifdef DEBUG_FOF    
    std::cout << "Len = " << len << std::endl;
#endif
    
    if(!this->_fortranFile->readStream()->is_open()) {
#ifdef DEBUG_FOF    
    std::cout << "Reopen " << this->_filename << std::endl;
#endif        
        this->_fortranFile->openRead(this->_filename);
    }
    
    if(this->_streampos > 0) {
#ifdef DEBUG_FOF        
        std::cout << "Seeking to " << _streampos << std::endl;
#endif
        this->_fortranFile->readStream()->seekg(this->_streampos);
    }
    
    this->_position.reserve(len * 3);
    //std::cout << "Reading position " << _streampos << std::endl;
    this->_fortranFile->readVector(this->_position, false);
    //std::cout << "Reading OK " << std::endl;
    if (this->_position.size() != len * 3) {
        throw std::ios_base::failure("ERROR : FOFParticles read position len");
    }

    this->_velocity.reserve(len * 3);
    this->_fortranFile->readVector(this->_velocity, false);
    if (this->_velocity.size() != len * 3) {
        throw std::ios_base::failure("ERROR : FOFParticles read velocity len");
    }

    if(readIds) {
        this->_id.reserve(len);
        this->_fortranFile->readVector(this->_id, false);
        if (this->_id.size() != len) {
            throw std::ios_base::failure("ERROR : FOFParticles read id len");            
        }
    }
    else {
         this->_fortranFile->readIgnore();
    }
    
    this->_fortranFile->close();
}

/**
 * Get current stream position
 */
void FOFParticles::setStreampos()
{
     this->_streampos = this->_fortranFile->readStream()->tellg();
     //std::cout << "Set pos to " << _streampos << std::endl;
}

/**
 * Skip Particles by reading the 3 fiels
 */
void FOFParticles::skipParticles()
{
    this->_fortranFile->readIgnore();
    this->_fortranFile->readIgnore();
    this->_fortranFile->readIgnore();
}