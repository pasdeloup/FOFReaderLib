/* ********************************** CELL ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        FOF_READER_LIB
// TITLE :          FOFFile
// DESCRIPTION :    Mesh cells integrating particles
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2013)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           FOFFile.cpp
/// \brief          Mesh cells integrating particles
/// \author         Jean Pasdeloup (jean.pasdeloup@obspm.fr)
/// \date           2013
/// \copyright      CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/

#include "FOFFile.h"

FOFFile::FOFFile()
{
    this->_fortranFile = new FortranFile<unsigned int>;
    this->_fortranFileMaster = true;
}

FOFFile::FOFFile(const FOFFile& orig)
{
}

FOFFile::~FOFFile()
{
    if(this->_fortranFileMaster) { // Only delete if master
     //   delete this->_fortranFile;
    }    
}

int FOFFile::openAndReadFirstInt(std::string filename) 
{
    int value;
    
    try {
        this->_fortranFile->openRead(filename);
        this->_fortranFile->read(value);
    } catch (const std::ios_base::failure& e) {
        this->_fortranFile->close();
        this->_fortranFile->openRead(filename);
        this->_fortranFile->setEndianness(true);
        this->_fortranFile->read(value);
    }
    return value;
}

