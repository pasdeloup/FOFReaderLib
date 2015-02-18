/* ************************** FOFReaderLib ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        FOFReaderLib
// TITLE :          DEUSGrav
// DESCRIPTION :    Tools to manage grav full directory
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2014)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           DEUSGrav.h
/// \brief          Tools to manage grav full directory
/// \author         Jean Pasdeloup (jean.pasdeloup@obspm.fr)
/// \date           2014
/// \copyright      CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/

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

