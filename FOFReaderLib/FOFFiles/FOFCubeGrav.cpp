/* 
 * File:   FOFCubeGrav.cpp
 * Author: jpasdeloup
 * 
 * Created on June 18, 2014, 2:34 PM
 */

#include "FOFCubeGrav.h"

#include <cassert>

FOFCubeGrav::FOFCubeGrav(std::string filename)
{ 
    this->_filename = filename;
    this->readCubeGravFile();
}

FOFCubeGrav::FOFCubeGrav(const FOFCubeGrav& orig) {
}

FOFCubeGrav::~FOFCubeGrav() {
}

// Open file and read cube (not multi)
void FOFCubeGrav::readCubeGravFile()
{   
    if(this->isDir()) {        
         std::cout << "Error, cannot read a full dir" << std::endl;
    }    
    else {
        unsigned int nLevels = 0;
        unsigned int len;
        
        int *cellsByLevel = NULL; //new int[10];                
        nLevels = this->openAndReadFirstArray(cellsByLevel);
        
        this->availableLevels(nLevels);
        this->_fortranFile->read(this->_procid);                    

        this->_boundaries = NULL; //new float[6];
        this->_fortranFile->readArray<float>(this->_boundaries, len); // min/max
        assert(len == 6);
        
        this->_levels.clear();
        for(unsigned int i=0; i< nLevels; i++) {
            FOFCubeGravLevel *myLevel = new FOFCubeGravLevel(this->_fortranFile);
            myLevel->nCells(cellsByLevel[i]);
            this->_levels.push_back(myLevel);
        }
        
        this->close();
    }   
}

void FOFCubeGrav::readLevels(bool onlyCoarse)
{
    unsigned int nLevels = this->availableLevels();
    if(onlyCoarse) {
        nLevels = 1;
    }    
    
    // Reopen and skip header        
    int *cellsByLevel = NULL;
    this->openAndReadFirstArray(cellsByLevel);
    this->_fortranFile->readIgnore();
    this->_fortranFile->readIgnore();
    
    for(unsigned int i=0; i< nLevels; i++) {          
        //std::cout << "read level " << i << std::endl;
        this->_levels[i]->readLevel();
    }
    this->close();
}

void FOFCubeGrav::releaseLevels()
{
    for(unsigned int i=0; i< this->nLevels(); i++) {
        //std::cout << "release level " << i << std::endl;
        this->_levels[i]->releaseLevel();
    }    
}

