/* 
 * FOF Reader Lib
 * Usage sample
 * Created on 1 octobre 2013, 16:22
 */

#include "FOFReaderLib/FOFReaderLib.h"

using namespace std;

/*
 * Usage sample
 */
int main(int argc, char** argv)
{    
    if (argc == 3) { // If correct number of args
        
        switch (atoi(argv[2])) {
        
        /* 
         * MULTI CUBE USAGE
         */
        case 0: 
        {
            cout << "Reading multicube " << argv[1] << endl;
            
            int maxParticleToDisplay = 5;
            int maxDetailCubeToDisplay = 3;
            
            FOFMultiCube multi(argv[1], false, false); // don't use default, don't read particles just header
            for(int i=0; i<multi.nCubes(); i++) {
                cout << "Cube " << i << ": " 
                        << multi.cubes(i)->npart() << " particles, "
                        << "area: (" << multi.cubes(i)->minX() << "," << multi.cubes(i)->minY() << "," << multi.cubes(i)->minZ() << ") "
                        << "to (" << multi.cubes(i)->maxX() << "," << multi.cubes(i)->maxY() << "," << multi.cubes(i)->maxZ() << ")"
                        << endl;
                if(i < maxDetailCubeToDisplay) {
                    multi.cubes(i)->readParticles(true);
                    for(int j=0; j< min(maxParticleToDisplay,multi.cubes(i)->npart()); j++) {                    
                        cout << "   Particle " << j << ": "
                            << "id: " << multi.cubes(i)->id(j) << " "
                            << "position: (" << multi.cubes(i)->posX(j) << "," << multi.cubes(i)->posY(j) << "," << multi.cubes(i)->posZ(j) << ") "
                            << "velocity (" << multi.cubes(i)->velX(j) << "," << multi.cubes(i)->velY(j) << "," << multi.cubes(i)->velZ(j) << ")"
                            << endl;
                    }  
                    if(multi.cubes(i)->npart() > maxParticleToDisplay ) {
                            cout << "   (...) " << endl;
                    }      
                }
                          
            }
            cout << "TOTAL " << multi.npart() << " particles, " 
                        << "area: (" << multi.minX() << "," << multi.minY() << "," << multi.minZ() << ") "
                        << "to (" << multi.maxX() << "," << multi.maxY() << "," << multi.maxZ() << ")"
                        << endl;            
            break;
        }
        
        /* 
         * STRUCT USAGE
         */
        case 1: 
        {
            cout << "Reading strct " << argv[1] << endl;
            FOFStrct strct(argv[1], true);
            for(int i=0; i<strct.nHalos(); i++) {
                cout << "HALO " << i << ": " 
                        << strct.halos(i)->npart() << " particles"                        
                        << endl;
                if(i==0) {
                    cout << "1st part of 1st halo: ID=" << strct.halos(i)->id(0)
                        << endl;
                }
            }            
            break;
        }
        
        /* 
         * MASST USAGE
         */
        case 2: 
        {
            cout << "Reading masst " << argv[1] << endl;
            FOFMasst masst(argv[1]);
            for(int i=0; i<masst.nHalos(); i++) {
                cout << "HALO " << i << ": " 
                        << "id:" << masst.halos(i)->id() << " "                        
                        << masst.halos(i)->mass() << " particles"                        
                        << " center: (" << masst.halos(i)->x() << "," << masst.halos(i)->y() << "," << masst.halos(i)->z() << ") "
                        << endl;
            }            
            break;
        }
        
        /*
         * UNKNOWN FORMAT
         */
        default:
            cout << "Unknown format " << argv[2] << endl;
        }        
        return 0;
    }
    /*
     * USAGE
     */
    else {
        cout << "Usage : fofReader <file> <format> \r\n"
                "    Formats: \r\n"
                "        0: FOF Cube/Multicube\r\n"
                "        1: FOF Struct\r\n"
                "        2: FOF Masst\r\n"
                << argc << endl;
        return 0;
    }
    return 0;
}

