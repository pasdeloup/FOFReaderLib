/* ************************** FOFReaderLib ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        FOFReaderLib
// TITLE :          FOFFile
// DESCRIPTION :    Low level FOFFile management, extended by other classes
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2013)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           FOFFile.h
/// \brief          Low level FOFFile management, extended by other classes
/// \author         Jean Pasdeloup (jean.pasdeloup@obspm.fr)
/// \date           2013
/// \copyright      CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/

#ifndef FOFFILE_H
#define	FOFFILE_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "fortranfile.h"

class FOFFile
{
public:
        
    FOFFile();
    FOFFile(std::string filename);   
    FOFFile(const FOFFile& orig);
    virtual ~FOFFile();
    
    // Open the file for reading and get the first int to check endianess    
    int openAndReadFirstInt(std::string filename, FortranFile<unsigned int> * fortranFile);
    int openAndReadFirstInt();
    
    int openAndReadFirstArray(int *&value, std::string filename, FortranFile<unsigned int> * fortranFile);
    int openAndReadFirstArray(int *&value);    
    
    void close() {this->_fortranFile->close();}
    
    // Check if current file is a dir or a real file
    bool isDir();
    
    // Get File name
    std::string getFilename() {return this->_filename;};
    
    // Get the files containing a string in a vector
    bool getFilesFromDir(std::string type, std::vector<std::string> *files);
    
    // Check if string contains a value
    bool contains(const std::string &haystack, const std::string &needle);
    
    // Replace a value by another (masst by strct for instance)
    void replaceAll(std::string& str, const std::string& from, const std::string& to);
    
    template<class T> T convert(std::vector<char> temp, int pos, bool endianness) {
        T value;        
        value = *reinterpret_cast<T*> (&temp[pos]); 
        if(endianness) {
            this->_fortranFile->swap(&value, 1);
        }
        return value;
    }    
        
protected:
    FortranFile<unsigned int> *_fortranFile;
    bool _fortranFileMaster;
    std::string _filename;
    
};

#endif	/* FOFFILE_H */

