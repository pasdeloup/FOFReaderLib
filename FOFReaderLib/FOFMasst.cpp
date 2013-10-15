/* ********************************** CELL ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        DEUS_SERVER
// TITLE :          FOFMasst
// DESCRIPTION :    Mesh cells integrating particles
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2013)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           FOFMasst.cpp
/// \brief          Mesh cells integrating particles
/// \author         Jean Pasdeloup (jean.pasdeloup@obspm.fr)
/// \date           2013
/// \copyright      CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/

#include "FOFMasst.h"
#include "FOFFile.h"

FOFMasst::FOFMasst()
{
}

FOFMasst::FOFMasst(const FOFMasst& orig)
{
}

FOFMasst::FOFMasst(std::string filename)
{
    this->readMasstFile(filename);
}

FOFMasst::~FOFMasst()
{
    while (!this->_halos.empty()) delete this->_halos.back(), this->_halos.pop_back();
}

void FOFMasst::readMasstFile(std::string filename) // Open file and read masst
{
    bool endianness;
    this->_nHalos = this->openAndReadFirstInt(filename);
    
    // Get endianess
    endianness = this->_fortranFile->endianness();
    
    std::vector<char> temp(24);
    
    this->_halos.reserve(this->_nHalos);
    for (int i = 0; i<this->_nHalos; i++) {
        this->_fortranFile->readVector(temp);
        
        FOFHalo *myHalo = new FOFHalo(
                this->convert<long long>(temp, 0, endianness),
                this->convert<float>(temp, 12, endianness),
                this->convert<float>(temp, 16, endianness),                
                this->convert<float>(temp, 20, endianness),                                      
                this->convert<int>(temp, 8, endianness)
            );
        
        std::cout << "Read halo " << i << " mass=" << myHalo->mass() << std::endl;
        
        this->_halos.push_back(myHalo);    
    }

}


