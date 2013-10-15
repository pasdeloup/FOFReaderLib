/* ********************************** CELL ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        DEUS_SERVER
// TITLE :          FOFMultiCube
// DESCRIPTION :    Mesh cells integrating particles
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2013)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           FOFMultiCube.cpp
/// \brief          Mesh cells integrating particles
/// \author         Jean Pasdeloup (jean.pasdeloup@obspm.fr)
/// \date           2013
/// \copyright      CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/

#include "FOFMultiCube.h"
#include "FOFCube.h"
#include "FOFFile.h"
#include "fortranfile.h"

FOFMultiCube::FOFMultiCube()
{
}

FOFMultiCube::FOFMultiCube(std::string filename, bool readIds)
{
    this->readMultiCubeFile(filename, readIds);
}

FOFMultiCube::FOFMultiCube(const FOFMultiCube& orig)
{
}

FOFMultiCube::~FOFMultiCube()
{    
    while(!this->_cubes.empty()) delete this->_cubes.back(), this->_cubes.pop_back();        
}

// Open file and read cube (not multi)
void FOFMultiCube::readMultiCubeFile(std::string filename, bool readIds)
{   
    int nCubes = 0;
    nCubes = this->openAndReadFirstInt(filename);
    
    if(nCubes > 0) { // Not a multicube file
        this->_cubes.reserve(1);
        FOFCube *myCube = new FOFCube(this->_fortranFile);
        myCube->npart(nCubes);
        myCube->readCube(true, readIds);
        this->_cubes.push_back(myCube);
    }
    else {
        nCubes = -nCubes;        
        this->_cubes.reserve(nCubes);
        for(int i=0; i<nCubes; i++) {            
            FOFCube *myCube = new FOFCube(this->_fortranFile);
            myCube->readCube(false, readIds);
            
            if(myCube->npart() > 0) {
                this->_cubes.push_back(myCube);                    
           }            
        }    
    }    
}

int FOFMultiCube::npart()
{
    int npart=0;
    for(int i=0; i< this->nCubes(); i++) {
        npart += this->cubes(i)->npart();
    }
    return npart;
}

float FOFMultiCube::boundaries(int j)
{
    float boundary;
    if(j%2 == 0) { //min
        boundary = 1.0;
        for(int i=0; i< this->nCubes(); i++) {        
            boundary = std::min(boundary, this->cubes(i)->boundaries(j));
        }
    }
    else {
        boundary = -1.0;
        for(int i=0; i< this->nCubes(); i++) {        
            boundary = std::max(boundary, this->cubes(i)->boundaries(j));
        }
    }
    return boundary;
}