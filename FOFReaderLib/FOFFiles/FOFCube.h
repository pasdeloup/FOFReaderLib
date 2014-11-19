/* ********************************** CELL ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        FOF_READER_LIB
// TITLE :          FOFCube
// DESCRIPTION :    Mesh cells integrating particles
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2013)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           FOFCube.h
/// \brief          Mesh cells integrating particles
/// \author         Jean Pasdeloup (jean.pasdeloup@obspm.fr)
/// \date           2013
/// \copyright      CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/

#ifndef FOFCUBE_H
#define	FOFCUBE_H

#include <string>

#include "FOFParticles.h"
#include "fortranfile.h"

class FOFCube : public FOFParticles
{
public:
    FOFCube();
    FOFCube(FortranFile<unsigned int> *_fortranFile);
    FOFCube(std::string filename, int readParticles = READ_POS | READ_VEL);
    FOFCube(const FOFCube& orig);
    virtual ~FOFCube();
    
    // Getters
    int procid() {return _procid;}
    float *boundaries() {return _boundaries; }
    float boundaries(int i) {return _boundaries[i]; }
    
    // Enhanced getters    
    float minX(void) {return _boundaries>0 ? _boundaries[0] : 0;}
    float maxX(void) {return _boundaries>0 ? _boundaries[1] : 0;}
    float minY(void) {return _boundaries>0 ? _boundaries[2] : 0;}
    float maxY(void) {return _boundaries>0 ? _boundaries[3] : 0;}
    float minZ(void) {return _boundaries>0 ? _boundaries[4] : 0;}
    float maxZ(void) {return _boundaries>0 ? _boundaries[5] : 0;}
    
    // Reader   
    void readCubeFile(int readParticles = READ_POS | READ_VEL); // Open file and read cube (not multi) skip reading ids by default
    void readCube(bool skipNpart=false, int readParticles = READ_POS | READ_VEL); // Read cube from already opened file.
        
protected:
    int _procid;
    float *_boundaries; 
    
};

#endif	/* FOFCUBE_H */

