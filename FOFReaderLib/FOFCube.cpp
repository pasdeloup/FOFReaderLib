/* ********************************** CELL ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        FOF_READER_LIB
// TITLE :          FOFCube
// DESCRIPTION :    FOF Cube file reader
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2013)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           FOFCube.cpp
/// \brief          FOF Cube file reader
/// \author         Jean Pasdeloup (jean.pasdeloup@obspm.fr)
/// \date           2013
/// \copyright      CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/

#include <cassert>

#include "fortranfile.h"
#include "FOFFile.h"
#include "FOFParticles.h"
#include "FOFCube.h"

FOFCube::FOFCube() : _boundaries(0)
{
}

FOFCube::FOFCube(std::string filename, bool readIds, bool readParticles)
{
    this->_streampos = 0;
    this->_filename = filename;
    this->readCubeFile(readIds, readParticles);
}

FOFCube::FOFCube(FortranFile<unsigned int> *fortranFile)
{
    this->_fortranFile = fortranFile; 
    this->_streampos = 0;
}

FOFCube::FOFCube(const FOFCube& orig)
{
}

FOFCube::~FOFCube()
{
    delete this->_boundaries;
}

// Read cube from already opened file (can use external FortranFile for multicube reading)
void FOFCube::readCube(bool skipNpart, bool readIds, bool readParticles)
{
    unsigned int len = 0;
    
    if(not skipNpart) {        
        this->_fortranFile->read(this->_npart);
    }
    
    this->_fortranFile->read(this->_procid);                    

    this->_boundaries = new float[6];
    this->_fortranFile->readArray<float>(this->_boundaries, len); // min/max
    assert(len == 6);
    this->setStreampos();
    if(readParticles) {
        this->readParticles(readIds);
    }
    else { // Else ignore to go to next cube
        this->_fortranFile->readIgnore();
        this->_fortranFile->readIgnore();
        this->_fortranFile->readIgnore();
    }
}

// Open file and read cube (not multi)
void FOFCube::readCubeFile(bool readIds, bool readParticles)
{       
    this->_npart = this->openAndReadFirstInt();
    if(npart() < 0) {
        throw std::ios_base::failure("ERROR : FOFCube multicube format");
    }
    this->readCube(true, readIds, readParticles);
}
