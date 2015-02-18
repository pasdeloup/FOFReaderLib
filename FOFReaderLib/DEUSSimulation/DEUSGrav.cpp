/* ************************** FOFReaderLib ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        FOFReaderLib
// TITLE :          DEUSGrav
// DESCRIPTION :    Tools to manage grav full directory
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2014)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           DEUSGrav.cpp
/// \brief          Tools to manage grav full directory
/// \author         Jean Pasdeloup (jean.pasdeloup@obspm.fr)
/// \date           2014
/// \copyright      CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/

#include "../FOFReaderLib.h"

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