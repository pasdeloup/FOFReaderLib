/* ************************** FOFReaderLib ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        FOFReaderLib
// TITLE :          FOFMultiCube
// DESCRIPTION :    FOF MultiCube file management
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2013)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           FOFMultiCube.h
/// \brief          FOF MultiCube file management
/// \author         Jean Pasdeloup (jean.pasdeloup@obspm.fr)
/// \date           2013
/// \copyright      CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/

#ifndef FOFMULTICUBE_H
#define	FOFMULTICUBE_H

#include <vector>

#include "FOFCube.h"
#include "FOFFile.h"

class FOFMultiCube : protected FOFCube
{
public:
    FOFMultiCube();
    FOFMultiCube(std::string, int readParticles = READ_POS | READ_VEL);
    FOFMultiCube(const FOFMultiCube& orig);
    virtual ~FOFMultiCube();
    
    // Getter
    std::vector<FOFCube*> cubes() {return _cubes; }
    
    // Enhanced getters        
    FOFCube *cubes(int i) {return _cubes[i]; }    
    int nCubes() {return _cubes.size(); }
    
    // Overload of Cube to read multicube like a giant cube
    long npart();    
    float boundaries(int i);
    float minX(void) {return boundaries(0);}
    float maxX(void) {return boundaries(1);}
    float minY(void) {return boundaries(2);}
    float maxY(void) {return boundaries(3);}
    float minZ(void) {return boundaries(4);}
    float maxZ(void) {return boundaries(5);}
    
    void readMultiCubeFile(int readParticles = READ_POS | READ_VEL); // Check if dir and add
    void addMultiCubeFile(std::string filename, int readParticles = READ_POS | READ_VEL); // Open file and add cube (not multi)
    
    void divideNpart(int divider = 8); // Divide all cube npart
    void npart(int npart); // Force npart globally (reduce proportionnaly for each cube)
        
protected:    
    std::vector<FOFCube*> _cubes;
    float minBoundaries();
    float maxBoundaries();    
};

#endif	/* FOFMULTICUBE_H */

