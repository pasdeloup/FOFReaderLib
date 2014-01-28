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
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

FOFFile::FOFFile()
{
    this->_fortranFile = new FortranFile<unsigned int>;
    this->_fortranFileMaster = true;    
}

FOFFile::FOFFile(std::string filename)
{
    this->_fortranFile = new FortranFile<unsigned int>;
    this->_fortranFileMaster = true;   
    this->_filename = filename;
}

FOFFile::FOFFile(const FOFFile& orig)
{
}

FOFFile::~FOFFile()
{
    if(this->_fortranFileMaster) { // Only delete if master
        this->_fortranFile->close();
    }    
}

int FOFFile::openAndReadFirstInt() 
{        
    return this->openAndReadFirstInt(this->_filename, this->_fortranFile);
}

int FOFFile::openAndReadFirstInt(std::string filename, FortranFile<unsigned int> * fortranFile) 
{
    int value;
    
    try {
        fortranFile->openRead(filename);
        fortranFile->read(value);
    } catch (const std::ios_base::failure& e) {
        fortranFile->close();
        fortranFile->openRead(filename);
        fortranFile->setEndianness(true);
        fortranFile->read(value);
    }
    return value;
}

bool FOFFile::isDir()
{
    DIR *Dir;
    Dir = opendir(this->_filename.c_str());
    return (Dir != NULL);        
}
            
bool FOFFile::getFilesFromDir(std::string type, std::vector<std::string> *files)
{
    DIR *Dir;
    struct dirent *DirEntry;
    Dir = opendir(this->_filename.c_str());
    if (Dir == NULL) {
        return false;
    }    
    while (DirEntry = readdir(Dir)) {
            if (contains(DirEntry->d_name,type)) {
                files->push_back(this->_filename + "/" + DirEntry->d_name);
            }
    }    
    return true;
}

bool FOFFile::contains(const std::string &haystack, const std::string &needle)
{
    int sleng = haystack.length();
    int nleng = needle.length();

    if (sleng==0 || nleng==0)
        return false;

    for(int i=0, j=0; i<sleng; j=0, i++ )
    {
        while (i+j<sleng && j<nleng && haystack[i+j]==needle[j])
            j++;
        if (j==nleng)
            return true;
    }
    return false;
}

void FOFFile::replaceAll(std::string& str, const std::string& from, const std::string& to) {
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}