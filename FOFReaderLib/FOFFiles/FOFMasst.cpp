/* ************************** FOFReaderLib ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        FOFReaderLib
// TITLE :          FOFMasst
// DESCRIPTION :    FOF Masst file management
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2013)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           FOFMasst.cpp
/// \brief          FOF Masst file management
/// \author         Jean Pasdeloup (jean.pasdeloup@obspm.fr)
/// \date           2013
/// \copyright      CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/

#include "../FOFReaderLib.h"

FOFMasst::FOFMasst()
{
}

FOFMasst::FOFMasst(const FOFMasst& orig)
{
}

FOFMasst::FOFMasst(std::string filename)
{
    this->_filename = filename;
    this->readMasstFile();
}

FOFMasst::~FOFMasst()
{
    while (!this->_halos.empty()) delete this->_halos.back(), this->_halos.pop_back();
}

void FOFMasst::readMasstFile() // Open file and read masst
{
    if (this->isDir()) {
        std::vector<std::string> files;
        this->getFilesFromDir("masst", &files);
        for (unsigned int i = 0; i < files.size(); i++) {
            addMasstFile(files[i]); // Never read particles from a directory !
        }
    }
    else {
        bool endianness;
        this->_nHalos = this->openAndReadFirstInt();

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

            this->_halos.push_back(myHalo);
        }

        this->_fortranFile->close();
    }
}

void FOFMasst::addMasstFile(std::string filename) // Open file and read masst
{
#ifdef FOF_DEBUG    
    std::cout << "Adding " << filename << std::endl;
#endif
    FOFMasst *multi;

    try {

        multi = new FOFMasst(filename);

        this->_halos.reserve(this->nHalos() + multi->nHalos());
        for (int i = 0; i < multi->nHalos(); i++) {
            this->_halos.push_back(multi->halos(i));
        }
        this->_nHalos = this->_halos.size();
    }
    catch (const std::ios_base::failure& e) {
#ifdef FOF_VERBOSE
        std::cerr << "Can't read " << filename << std::endl;
#endif
    }
}


