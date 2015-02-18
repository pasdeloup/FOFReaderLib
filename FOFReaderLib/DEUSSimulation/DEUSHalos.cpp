/* ************************** FOFReaderLib ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        FOFReaderLib
// TITLE :          DEUSHalos
// DESCRIPTION :    Tools to manage halos using masst + strct
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2013)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           DEUSHalos.cpp
/// \brief          Tools to manage halos using masst + strct
/// \author         Jean Pasdeloup (jean.pasdeloup@obspm.fr)
/// \date           2013
/// \copyright      CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/

#include "../FOFReaderLib.h"

DEUSHalos::DEUSHalos()
{
}

DEUSHalos::DEUSHalos(std::string directory)
{
    this->_directory = new FOFFile(directory);
    if(directory != "") {        
        this->loadMasst();
    }    
}

DEUSHalos::DEUSHalos(const DEUSHalos& orig)
{
}

DEUSHalos::~DEUSHalos()
{
}

void DEUSHalos::loadMasst()
{
    if (_directory->isDir()) {
        std::vector<std::string> files;
        _directory->getFilesFromDir("masst", &files);     
        
        std::vector<DEUSHalo*> *haloperfile = new std::vector<DEUSHalo*>[files.size()];
        
        #pragma omp parallel for num_threads(64)
        for (unsigned int i = 0; i < files.size(); i++) {
            try {
                FOFMasst *masst = new FOFMasst(files[i]);
                //_masstFilename.push_back(files[i]);
                haloperfile[i].reserve(masst->nHalos());
                //_halos.reserve(_halos.size() + masst->nHalos());
                int index = 24; // 4 int + 2*4  + 3*4
                for (int j = 0; j < masst->nHalos(); j++) {
                    DEUSHalo *halo = new DEUSHalo(
                                                  masst->halos(j)->x(),
                                                  masst->halos(j)->y(),
                                                  masst->halos(j)->z(),
                                                  masst->halos(j)->mass(),
                                                  i,
                                                  index
                                                  );
                    index += 36 + 32 * masst->halos(j)->mass(); // 3*2*4 + mass * 6*4+8 = 24 + mass * 36
                    haloperfile[i].push_back(halo);
                    //_halos.push_back(halo);
                }
                delete masst;
            }
            catch (const std::ios_base::failure& e) {
                std::cerr << "Can't read " << files[i] << std::endl;
            }
        }
        std::cout << "Merging..." << std::endl;
        // Merge results
        for (unsigned int i = 0; i < files.size(); i++) {
            _masstFilename.push_back(files[i]);
            _halos.insert(_halos.end(),haloperfile[i].begin(),haloperfile[i].end());
        }
        std::cout << "Done" << std::endl;
    }
    else {
        std::cout << "Error, arg1 should be a directory" << std::endl;
        exit(1);
    }
}

/*
 * Load particles for halo i
 */
void DEUSHalos::loadParticles(int i, int mode)
{
    //1- Get the right filename
    std::string filename = this->_masstFilename[this->halos(i)->fileindex()];
    this->_directory->replaceAll(filename, "masst", "strct");

    //2- Load the particle from this file according to halos datas
    FOFParticles *loadedParticles = new FOFParticles(filename, this->halos(i)->mass(), this->halos(i)->haloindex(), mode);
    this->halos(i)->particles(loadedParticles);
}

void DEUSHalos::releaseParticles(int i)
{
    this->halos(i)->particles()->releaseParticles();
    delete this->halos(i)->particles();
    this->halos(i)->particles(0);
}

