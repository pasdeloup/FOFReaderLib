/* ************************** FOFReaderLib ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        FOFReaderLib
// TITLE :          FOFParticles
// DESCRIPTION :    Intermediate class for formats managing particles
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2013)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           FOFParticles.cpp
/// \brief          Intermediate class for formats managing particles
/// \author         Jean Pasdeloup (jean.pasdeloup@obspm.fr)
/// \date           2013
/// \copyright      CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/

#include <vector>
#include <algorithm>
#include <math.h>

#include "../FOFReaderLib.h"

FOFParticles::FOFParticles()
{
    this->_npart = this->_originalNpart = 0;
}

FOFParticles::FOFParticles(FortranFile<unsigned int> *fortranFile)
{    
    this->_fortranFile = fortranFile;
    this->_filename = fortranFile->name();
    this->_fortranFileMaster = false;
    this->_streampos = 0;    
    this->_npart = this->_originalNpart = 0;
}

/**
 * Constructeur
 * @param filename
 * @param npart
 * @param position
 * @param mode 0=Both 1=Don't read Ids -1=Ids Only
 */
FOFParticles::FOFParticles(std::string filename, int npart, std::streamoff position, int mode)
{
    this->_streampos = position;
    this->_filename = filename;
    this->_npart = this->_originalNpart = npart;
    
    this->openAndReadFirstInt(); // just to check Endianness    
    this->readParticles(mode);    
}

FOFParticles::FOFParticles(const FOFParticles& orig)
{
}

FOFParticles::~FOFParticles()
{
    this->releaseParticles();
}

/**
 * Read the particles
 * @param readIds read or skip ids (faster to skip, not ever usefuls)
 */
void FOFParticles::readParticles(int mode, bool closefile)
{
    unsigned int len = this->_originalNpart;
#ifdef FOF_DEBUG    
    std::cout << "Len = " << len << std::endl;
#endif
    
    if(!this->_fortranFile->readStream()->is_open()) {
        this->_fortranFile->openRead(this->_filename);
    }
    
    if(this->_streampos > 0) {
#ifdef FOF_DEBUG        
        std::cout << "Seeking to " << _streampos << std::endl;
#endif
        this->_fortranFile->readStream()->seekg(this->_streampos);
    }
    
    if(mode & READ_POS) {
        this->_position.reserve(len * 3);
        //std::cout << "Reading position " << _streampos << std::endl;
        this->_fortranFile->readVector(this->_position, false);
        //std::cout << "Reading OK " << std::endl;
        if (this->_position.size() != len * 3) {
            throw std::ios_base::failure("ERROR : FOFParticles read position len");
        }
    }
    else {
        this->_fortranFile->readIgnore();
    }
    
    if(mode & READ_VEL) {
        this->_velocity.reserve(len * 3);
        this->_fortranFile->readVector(this->_velocity, false);
        if (this->_velocity.size() != len * 3) {
            throw std::ios_base::failure("ERROR : FOFParticles read velocity len");
        }
    }
    else {
        this->_fortranFile->readIgnore();
    }

    if(mode & READ_IDS) {
        this->_id.reserve(len);
        try {
            this->_fortranFile->readVector(this->_id, false);
            if (this->_id.size() != len) {
                throw std::ios_base::failure("ERROR : FOFParticles read id len");            
            }
        }
        catch (const std::ios_base::failure& e) {
#ifdef FOF_VERBOSE        
            std::cerr << "Can't read ids" << std::endl;
#endif
        }   
    }
    else {
         //this->_fortranFile->readIgnore();
    }
    
    if(closefile) {
        this->_fortranFile->close();
    }    
    
    // If modified npart, remove randomly particles
    if(this->_npart < this->_originalNpart) {
        this->reduceNpart(this->_npart);
    }
}



/**
 * Release particles to free memory (need to re-read if needed again)
 */
void FOFParticles::releaseParticles()
{
    this->_position.clear();
    this->_velocity.clear();
    this->_id.clear();
}


/**
 * Set current stream position
 */
void FOFParticles::setStreampos()
{
     this->_streampos = this->_fortranFile->readStream()->tellg();
     //std::cout << "Set pos to " << _streampos << std::endl;
}

/**
 * Skip Particles by reading the 3 fields
 */
void FOFParticles::skipParticles()
{
    this->_fortranFile->readIgnore();
    this->_fortranFile->readIgnore();
    try {
        this->_fortranFile->readIgnore();
    }
    catch (const std::ios_base::failure& e) {
    }      
}

/**
 * Remove a specific particle either physically (reduced npart) or virtually (put to infinity)
 * @param i
 */
void FOFParticles::removeParticle(int i, bool virtually)
{
    if(virtually) {
        this->_position[i*3 + 0] = INFINITY;
        this->_position[i*3 + 1] = INFINITY;
        this->_position[i*3 + 2] = INFINITY;
    }
    else {
        this->_position.erase(this->_position.begin()+(3*i-1), this->_position.begin()+(3*i+2));
        this->_velocity.erase(this->_velocity.begin()+(3*i-1), this->_velocity.begin()+(3*i+2));
        this->_id.erase(this->_id.begin()+(i-1));
        this->_npart--;
    }
    
}

/**
 * Remove particles put to infinity (rebuild the particles vector)
 */
void FOFParticles::removeParticleInInfinity()
{
    // create new vectors    
    std::vector<float> position;
    std::vector<float> velocity;
    std::vector<long long> id;    
    position.reserve(this->_npart * 3);
    velocity.reserve(this->_npart * 3);
    id.reserve(this->_npart);
    
    // put only the correct particles in it
    for(int i=0; i<this->_npart; i++ ) {
        if(this->_position[i*3] != INFINITY && this->_position[i*3 +1] != INFINITY && this->_position[i*3 +2] != INFINITY) {
            position.push_back(this->_position[i*3 + 0]);
            position.push_back(this->_position[i*3 + 1]);
            position.push_back(this->_position[i*3 + 2]);
            velocity.push_back(this->_velocity[i*3 + 0]);
            velocity.push_back(this->_velocity[i*3 + 1]);
            velocity.push_back(this->_velocity[i*3 + 2]);
            id.push_back(this->_id[i]);
        }
    }
    
    // swap vectors
    this->_position.swap(position);
    this->_velocity.swap(velocity);
    this->_id.swap(id);
    this->_npart = this->_id.size();
    
    // remove the old ones
    position.clear();
    velocity.clear();
    id.clear();
}

/**
 * Reduce npart by removing randomly particles
 * @param newNpart
 */
void FOFParticles::reduceNpart(int newNpart)
{
    if(newNpart >= this->_npart) { // Don't try to reduce if less particle than needed
        return;
    }
    int toRemove = this->_npart - newNpart;
    
    std::vector<unsigned int> randomindex;
    for (int i=0; i<this->_npart; ++i) randomindex.push_back(i);

    std::random_shuffle ( randomindex.begin(), randomindex.end() );

    for(int i=0; i<toRemove; i++) {
        this->removeParticle(i, true);
    }
    this->removeParticleInInfinity();
}
