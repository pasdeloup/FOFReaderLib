/* ************************** FOFReaderLib ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        FOFReaderLib
// TITLE :          FOFMultiCube
// DESCRIPTION :    FOF MultiCube file management
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2013)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           FOFMultiCube.cpp
/// \brief          FOF MultiCube file management
/// \author         Jean Pasdeloup (jean.pasdeloup@obspm.fr)
/// \date           2013
/// \copyright      CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/

#include "../FOFReaderLib.h"

FOFMultiCube::FOFMultiCube()
{
}

FOFMultiCube::FOFMultiCube(std::string filename, int readParticles)
{ 
    this->_filename = filename;
    this->readMultiCubeFile(readParticles);
}

FOFMultiCube::FOFMultiCube(const FOFMultiCube& orig)
{
}

FOFMultiCube::~FOFMultiCube()
{    
    while(!this->_cubes.empty()) delete this->_cubes.back(), this->_cubes.pop_back();        
}

// Open file and read cube (not multi)
void FOFMultiCube::readMultiCubeFile(int readParticles)
{   
    if(this->isDir()) {        
         std::vector<std::string> files;
         this->getFilesFromDir("cube",&files);
         for(unsigned int i=0; i<files.size();i++) {             
             addMultiCubeFile(files[i], DONT_READ_PARTICLES);  // Never read particles from a directory !
         }
    }    
    else {
        int nCubes = 0;
        
        nCubes = this->openAndReadFirstInt();
        
        if(nCubes >= 0) { // Not a multicube file
            this->_cubes.reserve(this->nCubes() + 1);
            FOFCube *myCube = new FOFCube(this->_fortranFile);            
            myCube->npart(nCubes);
            
            myCube->readCube(true, readParticles);
            this->_cubes.push_back(myCube);
            this->close();
        }
        else {
            // Remember offset of first cube
            std::streamoff firstCubeOffset = this->_fortranFile->readStream()->tellg();            
            // Get file size
            this->_fortranFile->readStream()->seekg (0, this->_fortranFile->readStream()->end);            
            std::streamoff endFileOffset = this->_fortranFile->readStream()->tellg();
            // Go back to first cube
            this->_fortranFile->readStream()->seekg (firstCubeOffset);
#ifdef FOF_DEBUG                        
            std::cout << "Multicube" << std::endl;
#endif                 
            int i=0;
            while(this->_fortranFile->readStream()->tellg() < endFileOffset) {
#ifdef FOF_DEBUG
                std::cout << "Reading cube " << i << std::endl;
#endif
                FOFCube *myCube = new FOFCube(this->_fortranFile);
                myCube->readCube(false, readParticles);            
                if(myCube->npart() > 0) {
                    this->_cubes.push_back(myCube);
               }            
               i++;               
            }    
            this->close();
        }   
    }    
}

// Open file and read cube (not multi)
void FOFMultiCube::addMultiCubeFile(std::string filename, int readParticles)
{   
#ifdef FOF_DEBUG
    std::cout << "Adding " << filename << std::endl;
#endif
    FOFMultiCube *multi;
    
    try {
        multi = new FOFMultiCube(filename, readParticles);
    
        this->_cubes.reserve(this->nCubes() + multi->nCubes());
        for(int i=0; i<multi->nCubes(); i++) {
            this->_cubes.push_back(multi->cubes(i));
        }    
    }
    catch (const std::ios_base::failure& e) {
#ifdef FOF_VERBOSE        
        std::cerr << "Can't read " << filename << std::endl;
#endif
    }    
}


long FOFMultiCube::npart()
{
    long npart=0;
    for(int i=0; i< this->nCubes(); i++) {
        npart += this->cubes(i)->npart();
    }
    return npart;
}

/**
 * Divide all cube npart
 * @param divider
 */
void FOFMultiCube::divideNpart(int divider)
{    
    for(int i=0; i< this->nCubes(); i++) {
        this->cubes(i)->divideNpart(divider);
    }    
}

/**
 * Force npart globally (reduce proportionnaly for each cube)
 * @param npart
 */
void FOFMultiCube::npart(int npart)
{    
    float ratio = float(this->npart()) / (float) npart;    
    for(int i=0; i< this->nCubes(); i++) {
        this->cubes(i)->divideNpart(ratio);
    }    
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