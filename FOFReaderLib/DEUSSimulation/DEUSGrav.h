/* 
 * File:   DEUSGrav.h
 * Author: jpasdeloup
 *
 * Created on June 25, 2014, 2:20 PM
 */

#ifndef DEUSGRAV_H
#define	DEUSGRAV_H

#include "../FOFFiles/FOFCubeGrav.h"
#include "../FOFFiles/FOFFile.h"

class DEUSGrav {
public:
    DEUSGrav(std::string directory);
    DEUSGrav(const DEUSGrav& orig);
    virtual ~DEUSGrav();
    
    FOFCubeGrav *cubeGrav(int i) {return _files[i];}    
    unsigned int nFiles() {return _files.size();}
    
    void readLevels(int i, bool onlyCoarse=true) {this->_files[i]->readLevels(onlyCoarse);}
    void releaseLevels(int i) {this->_files[i]->releaseLevels();}
    
    
private:
    void loadGrav();      
    
    FOFFile *_directory;
    std::vector<FOFCubeGrav*> _files;

};

#endif	/* DEUSGRAV_H */

