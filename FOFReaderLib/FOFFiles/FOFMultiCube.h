/* ********************************** CELL ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        DEUS_SERVER
// TITLE :          FOFMultiCube
// DESCRIPTION :    Mesh cells integrating particles
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2013)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           FOFMultiCube.h
/// \brief          Mesh cells integrating particles
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
    FOFMultiCube(std::string, bool readIds=false, bool readParticles=true);
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
    
    void readMultiCubeFile(bool readIds=false, bool readParticles=true); // Check if dir and add
    void addMultiCubeFile(std::string filename, bool readIds=false, bool readParticles=true); // Open file and add cube (not multi)

protected:    
    std::vector<FOFCube*> _cubes;
    float minBoundaries();
    float maxBoundaries();
};

#endif	/* FOFMULTICUBE_H */
