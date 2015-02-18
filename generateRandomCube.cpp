/* ************************** FOFReaderLib ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        FOFReaderLib
// TITLE :          FOFReaderLib
// DESCRIPTION :    Cube generator with random data
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2013)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           FOFReaderLib.h
/// \brief          Cube generator with random data
/// \author         Jean Pasdeloup (jean.pasdeloup@obspm.fr)
/// \date           2013
/// \copyright      CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/

#include <cstdlib>
#include <fstream>
#include <sstream>
#include <random>
#include <vector>

#include "FOFReaderLib/FOFReaderLib.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) 
{    
    
    if (argc == 4) { // If correct number of args
        
        FOFCube myCube(
            pow(atoi(argv[2]),3), 
            atoi(argv[3])
        );
        
        cout << "Cube before "  << ": " 
                    << myCube.npart() << " particles, " 
                    << "area: (" << myCube.minX() << "," << myCube.minY() << "," << myCube.minZ() << ") "
                    << "to (" << myCube.maxX() << "," << myCube.maxY() << "," << myCube.maxZ() << ")"
                    << endl;           
        
        // remove particle in the center with radius 0.1        
        float radius = 0.1f;
        float center[3] = {0.5f,0.5f,0.5f};        
        
        for(int j=0; j< myCube.npart(); j++) {
            float x = myCube.posX(j) - center[0];
            float y = myCube.posY(j) - center[1];
            float z = myCube.posZ(j) - center[2];
            float r = sqrt(x*x + y*y + z*z);
            if(r < radius) {                
                myCube.removeParticle(j, true);                
            }            
        }
        myCube.removeParticleInInfinity();
        
        int maxParticleToDisplay = 8;
                          
        cout << "Cube after "  << ": " 
                    << myCube.npart() << " particles, " 
                    << "area: (" << myCube.minX() << "," << myCube.minY() << "," << myCube.minZ() << ") "
                    << "to (" << myCube.maxX() << "," << myCube.maxY() << "," << myCube.maxZ() << ")"
                    << endl;       

        for(int j=0; j< min(maxParticleToDisplay,myCube.npart()); j++) {                    
            cout << "   Particle " << j << ": "
                << "id: " << myCube.id(j) << " "
                << "position: (" << myCube.posX(j) << "," << myCube.posY(j) << "," << myCube.posZ(j) << ") "
                << "velocity (" << myCube.velX(j) << "," << myCube.velY(j) << "," << myCube.velZ(j) << ")"
                << endl;
        }  
        if(myCube.npart() > maxParticleToDisplay ) {
                cout << "   (...) " << endl;
        }
                  
        myCube.writeCubeFile(argv[1]);
        
    }
    else {
        cout << "Usage : generateRandomCube <filename> <lpart> <generator>\r\n"
                << "   will generate a cube with lpart*lpart*lpart particles using generator: \r\n"                
                << "     0: constant, all particles in (0.5,0.5,0.5) with velocity(0,0,0) \r\n"
                << "     1: random, all particles with random position and velocity between 0.0 and 1.0 \r\n"
                << "     2: homogeneous, all particles in a constant grid with velocity(0,0,0) \r\n"
                << argc << endl;
        return 0;
    }
    
    return 0;
}


