/* ********************************** CELL ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        DEUS_SERVER
// TITLE :          FOFStrct
// DESCRIPTION :    Mesh cells integrating particles
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2013)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           FOFStrct.cpp
/// \brief          Mesh cells integrating particles
/// \author         Jean Pasdeloup (jean.pasdeloup@obspm.fr)
/// \date           2013
/// \copyright      CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/

#include "FOFStrct.h"

FOFStrct::FOFStrct()
{
}

FOFStrct::FOFStrct(const FOFStrct& orig)
{
}

FOFStrct::FOFStrct(std::string filename, bool readIds)
{
    this->_filename = filename;
    this->readStrctFile(readIds);    
}

FOFStrct::~FOFStrct()
{    
    while(!this->_halos.empty()) delete this->_halos.back(), this->_halos.pop_back();        
}

void FOFStrct::readStrctFile(bool readIds, bool readParticles) // Open file and read strct
{    
    this->_nHalos = this->openAndReadFirstInt();
    
    this->_halos.reserve(this->_nHalos);
    for(int i=0; i<this->_nHalos; i++) {            
        FOFParticles *myHalo = new FOFParticles(this->_fortranFile);
        int npart;
        this->_fortranFile->read(npart);
        myHalo->npart(npart);
        if(npart > 0) {
            if(readParticles) {
                myHalo->readParticles(readIds);
            }            
            this->_halos.push_back(myHalo);                    
       }            
    }    
 
}

