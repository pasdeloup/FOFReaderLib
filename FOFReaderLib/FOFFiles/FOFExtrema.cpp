/* ************************** FOFReaderLib ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        FOFReaderLib
// TITLE :          FOFExtrema
// DESCRIPTION :    FOF Extrema file management
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2015)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           FOFExtrema.cpp
/// \brief          FOF Extrema file management
/// \author         Jean Pasdeloup (jean.pasdeloup@obspm.fr)
/// \date           2015
/// \copyright      CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/

#include "../FOFReaderLib.h"

FOFExtrema::FOFExtrema()
{
}

FOFExtrema::FOFExtrema(const FOFExtrema& orig)
{
}

FOFExtrema::FOFExtrema(std::string filename)
{
    this->_filename = filename;
    this->readExtremaFile();
}

FOFExtrema::~FOFExtrema()
{
    while (!this->_extrema.empty()) delete this->_extrema.back(), this->_extrema.pop_back();
}

void FOFExtrema::readExtremaFile() // Open file and read masst
{
    if (this->isDir()) {
        std::vector<std::string> files;
        this->getFilesFromDir("extrema", &files);
        for (unsigned int i = 0; i < files.size(); i++) {
            addExtremaFile(files[i]); // Never read particles from a directory !
        }
    }
    else {
        std::vector<float> temp;
        
        this->_nExtrema = this->openAndReadFirstInt();
    
        temp.reserve(this->_nExtrema * 6);
        this->_extrema.reserve(this->_nExtrema);
        
        this->_fortranFile->readVector(temp);
        
        for(int i=0; i<this->_nExtrema; i++) {
            FOFExtremum *extremum = new FOFExtremum(
                    temp[i + 0],
                    temp[i + this->_nExtrema],
                    temp[i + this->_nExtrema*2],
                    temp[i + this->_nExtrema*3],
                    temp[i + this->_nExtrema*4],
                    temp[i + this->_nExtrema*5]
                    );
            this->_extrema.push_back(extremum);
        }
        //temp.clear();
        this->_fortranFile->close();
    }
}

void FOFExtrema::addExtremaFile(std::string filename) // Open file and read masst
{
#ifdef FOF_DEBUG    
    std::cout << "Adding " << filename << std::endl;
#endif
    FOFExtrema *multi;

    try {

        multi = new FOFExtrema(filename);

        this->_extrema.reserve(this->nExtrema() + multi->nExtrema());
        for (int i = 0; i < multi->nExtrema(); i++) {
            this->_extrema.push_back(multi->extremum(i));
        }
        this->_nExtrema = this->_extrema.size();
    }
    catch (const std::ios_base::failure& e) {
#ifdef FOF_VERBOSE
        std::cerr << "Can't read " << filename << std::endl;
#endif
    }
}


