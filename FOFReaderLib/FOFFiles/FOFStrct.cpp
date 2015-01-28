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

FOFStrct::FOFStrct(std::string filename, int readParticles)
{
    this->_filename = filename;
    this->readStrctFile(readParticles);
}

FOFStrct::~FOFStrct()
{
    while (!this->_halos.empty()) delete this->_halos.back(), this->_halos.pop_back();
}

void FOFStrct::readStrctFile(int readParticles) // Open file and read strct
{
    if (this->isDir()) {
        std::vector<std::string> files;
        this->getFilesFromDir("strct", &files);
        for (unsigned int i = 0; i < files.size(); i++) {
            addStrctFile(files[i], FOFParticles::DONT_READ_PARTICLES); // Never read particles from a directory !
        }
    }
    else {
        this->_nHalos = this->openAndReadFirstInt();

        this->_halos.reserve(this->_nHalos);
        for (int i = 0; i<this->_nHalos; i++) {
            FOFParticles *myHalo = new FOFParticles(this->_fortranFile);
            int npart;
            this->_fortranFile->read(npart);
            myHalo->npart(npart);
            
            std::cout << "Found " << npart << " particles" << std::endl;
            
            if (npart > 0) {
                if (readParticles) {
                    myHalo->readParticles(readParticles, false);
                }
                else {
                    myHalo->skipParticles();
                }
                this->_halos.push_back(myHalo);
            }
        }
        this->close();
    }
}

// Open file and read cube (not multi)

void FOFStrct::addStrctFile(std::string filename, int readParticles)
{
#ifdef DEBUG_FOF
    std::cout << "Adding " << filename << std::endl;
#endif
    try {
        FOFStrct *multi;

        multi = new FOFStrct(filename, readParticles);

        this->_halos.reserve(this->nHalos() + multi->nHalos());
        for (int i = 0; i < multi->nHalos(); i++) {
            this->_halos.push_back(multi->halos(i));
        }
    }
    catch (const std::ios_base::failure& e) {
        std::cerr << "Can't read " << filename << std::endl;
    }
}

