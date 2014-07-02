/* 
 * File:   DEUSGrav.cpp
 * Author: jpasdeloup
 * 
 * Created on June 25, 2014, 2:20 PM
 */

#include "DEUSGrav.h"

DEUSGrav::DEUSGrav(std::string directory) {
    this->_directory = new FOFFile(directory);
    if(directory != "") {        
        this->loadGrav();
    }
}

DEUSGrav::DEUSGrav(const DEUSGrav& orig) {
}

DEUSGrav::~DEUSGrav() {
}

void DEUSGrav::loadGrav()
{
    if (_directory->isDir()) {
        std::vector<std::string> files;
        _directory->getFilesFromDir("grav", &files);     
        
        for (unsigned int i = 0; i < files.size(); i++) {
            try {
                FOFCubeGrav *grav = new FOFCubeGrav(files[i]);
                
                if(grav->level(0)->nCells() > 0) {
                    this->_files.push_back(grav); 
                }
                else {
                    delete grav;
                }                
            }
            catch (const std::ios_base::failure& e) {
                std::cerr << "Can't read " << files[i] << std::endl;
            }            
        }        
        std::cout << "Done" << std::endl;
    }
    else {
        std::cout << "Error, arg1 should be a directory" << std::endl;
        exit(1);
    }
}