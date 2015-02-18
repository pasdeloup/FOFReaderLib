/* ************************** FOFReaderLib ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        FOFReaderLib
// TITLE :          FOFCubeGrav
// DESCRIPTION :    FOF Cubegrav file management
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2013)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           FOFCubeGrav.h
/// \brief          FOF Cubegrav file management
/// \author         Jean Pasdeloup (jean.pasdeloup@obspm.fr)
/// \date           2013
/// \copyright      CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/

#ifndef FOFCUBEGRAV_H
#define	FOFCUBEGRAV_H

#include <string>

#include "FOFFile.h"
#include "FOFCubeGravLevel.h"


class FOFCubeGrav : protected FOFFile {
public:
    FOFCubeGrav(std::string filename);
    FOFCubeGrav(const FOFCubeGrav& orig);
    virtual ~FOFCubeGrav();
    
    // Setters
    void availableLevels(int level) {_availableLevels = level;}
    
    // Getters
    int procid() {return _procid;}
    float *boundaries() {return _boundaries; }
    float boundaries(int i) {return _boundaries[i]; }
    FOFCubeGravLevel *level(int i) {return _levels[i];}
    unsigned int nLevels() {return _levels.size();}
    int availableLevels() {return _availableLevels;}
    std::string filename() {return _filename;}
        
    // Enhanced getters    
    float minX(void) {return _boundaries>0 ? _boundaries[0] - 0.5f : 0;}
    float maxX(void) {return _boundaries>0 ? _boundaries[1] - 0.5f : 0;}
    float minY(void) {return _boundaries>0 ? _boundaries[2] - 0.5f : 0;}
    float maxY(void) {return _boundaries>0 ? _boundaries[3] - 0.5f : 0;}
    float minZ(void) {return _boundaries>0 ? _boundaries[4] - 0.5f : 0;}
    float maxZ(void) {return _boundaries>0 ? _boundaries[5] - 0.5f : 0;} 
    
    // Reader   
    void readCubeGravFile(); 
    void readLevels(bool onlyCoarse = true);
    void releaseLevels();
    
protected:
        int _procid;
        float *_boundaries; 
        int _availableLevels;
        std::vector<FOFCubeGravLevel*> _levels;

};

#endif	/* FOFCUBEGRAV_H */

