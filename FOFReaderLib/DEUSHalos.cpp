/* ********************************** CELL ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        DEUS_SERVER
// TITLE :          DEUSHalos
// DESCRIPTION :    Mesh cells integrating particles
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2013)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           DEUSHalos.cpp
/// \brief          Mesh cells integrating particles
/// \author         Jean Pasdeloup (jean.pasdeloup@obspm.fr)
/// \date           2013
/// \copyright      CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/

#include "DEUSHalos.h"

DEUSHalos::DEUSHalos(std::string directory)
{
    this->_directory = new FOFFile(directory);
    this->loadMasst();
}

DEUSHalos::DEUSHalos(const DEUSHalos& orig)
{
}

DEUSHalos::~DEUSHalos()
{
}

void DEUSHalos::loadMasst()
{    
    if(_directory->isDir()) {
         std::vector<std::string> files;
         bool res=_directory->getFilesFromDir("masst",&files);
         for(int i=0; i<files.size();i++) {     
             _masstFilename.push_back(files[i]);
             FOFMasst *masst = new FOFMasst(files[i]);
             _halos.reserve(_halos.size() + masst->nHalos());
             int index=24; // 4 int + 2*4  + 3*4
             for(int j=0; j<masst->nHalos(); j++) {                 
                 DEUSHalo *halo = new DEUSHalo(
                         masst->halos(j)->x(),
                         masst->halos(j)->y(),
                         masst->halos(j)->z(),
                         masst->halos(j)->mass(),
                         i,
                         index
                 );
                 index += 36 + 32* masst->halos(j)->mass();// 3*2*4 + mass * 6*4+8 = 24 + mass * 36
                 _halos.push_back(halo);
             }
             delete masst;
         }
    }    
    else {
        std::cout << "Error, arg1 should be a directory" << std::endl;
        exit(1);
    }    
}

/*
 * Load particles for halo i
 */
void DEUSHalos::loadParticles(int i)
{
    //1- Get the right filename
    std::string filename = this->_masstFilename[this->halos(i)->fileindex()];    
    this->_directory->replaceAll(filename, "masst", "strct");
        
    //2- Load the particle from this file according to halos datas
    FOFParticles *loadedParticles = new FOFParticles(filename,this->halos(i)->mass(), this->halos(i)->haloindex());
        
    this->halos(i)->particles(loadedParticles);
    
    delete loadedParticles;
}

