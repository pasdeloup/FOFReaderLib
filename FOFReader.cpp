/* ************************** FOFReaderLib ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        FOFReaderLib
// TITLE :          FOFReaderLib
// DESCRIPTION :    Main FOFReaderLib example, try to read all formats
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2013)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           FOFReaderLib.h
/// \brief          Main FOFReaderLib example, try to read all formats
/// \author         Jean Pasdeloup (jean.pasdeloup@obspm.fr)
/// \date           2013
/// \copyright      CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/

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
            int maxDetailCubeToDisplay = 2;
            
            FOFMultiCube multi(argv[1], FOFParticles::DONT_READ_PARTICLES); // don't use default, don't read particles just header
            //multi.divideNpart(8); // Reduce nb part by 8
            //multi.npart(10000); // Force npart to 1000
                        
            for(int i=0; i<multi.nCubes(); i++) {                            
                          
                    cout << "Cube " << i << ": " 
                            << multi.cubes(i)->npart() << " particles, "
                            << "area: (" << multi.cubes(i)->minX() << "," << multi.cubes(i)->minY() << "," << multi.cubes(i)->minZ() << ") "
                            << "to (" << multi.cubes(i)->maxX() << "," << multi.cubes(i)->maxY() << "," << multi.cubes(i)->maxZ() << ")"
                            << endl;       
                    
               if(i < maxDetailCubeToDisplay) {
                    multi.cubes(i)->readParticles(FOFParticles::READ_ALL); // Need to read particles                    
                                        
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
                    multi.cubes(i)->releaseParticles(); // Now we can release to free memory
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
            FOFStrct strct(argv[1], FOFParticles::DONT_READ_PARTICLES);
            int maxHaloToDisplay = 5;
            for(int i=0; i<min(maxHaloToDisplay,strct.nHalos()); i++) {
                cout << "HALO " << i << ": " 
                        << strct.halos(i)->npart() << " particles"                        
                        << endl;
                if(i==0) {
                    strct.halos(i)->readParticles(FOFParticles::READ_ALL);
                    cout << "1st part of 1st halo: ID=" << strct.halos(i)->id(0)
                        << " position: (" << strct.halos(i)->posX(0) << "," << strct.halos(i)->posY(0) << "," << strct.halos(i)->posZ(0) << ") "
                        << endl;
                }
            }            
            cout << "TOTAL " << strct.nHalos() << " halos" << endl;
            break;
        }
        
        /* 
         * MASST USAGE
         */
        case 2: 
        {
            cout << "Reading masst " << argv[1] << endl;
            FOFMasst masst(argv[1]);
            cout << "OK" << endl;
            cout << "Read " << masst.nHalos() << endl;
            int maxHaloToDisplay = 5;
            for(int i=0; i<min(maxHaloToDisplay,masst.nHalos()); i++) {
                cout << "HALO " << i << ": " 
                        << "id:" << masst.halos(i)->id() << " "                        
                        << masst.halos(i)->mass() << " particles"                        
                        << " center: (" << masst.halos(i)->x() << "," << masst.halos(i)->y() << "," << masst.halos(i)->z() << ") "
                        << endl;
            }            
             cout << "TOTAL " << masst.nHalos() << " halos" << endl;
            break;
        }
        
        /* 
         * DEUS HALOS USAGE (masst + strct)
         */
        case 3: 
        {
            cout << "Reading Halo dir " << argv[1] << endl;
            DEUSHalos simulation(argv[1]);
            long long int maxHaloToDisplay = 5;
            int randomHalo = 1; //1651288; //1651288;
            
            for(int i=0; i<min(maxHaloToDisplay,simulation.nHalos()); i++) {
                    cout << "  HALO " << i << ": "                             
                            << simulation.halos(i)->mass() << " particles"                        
                            << " center: (" 
                                << simulation.halos(i)->x() << "," 
                                << simulation.halos(i)->y() << "," 
                                << simulation.halos(i)->z() << ") "
                            << endl;            
            }
            cout << "TOTAL SIMULATION " << simulation.nFiles() << " files, " << simulation.nHalos() << " halos" << endl;
            
            if(simulation.nHalos() >= randomHalo) {
                cout << "SELECTED HALO : " << randomHalo << endl;

                simulation.loadParticles(randomHalo, FOFParticles::READ_ALL);
                FOFParticles *haloParticles = simulation.halos(randomHalo)->particles();

                for(int j=0; j<haloParticles->npart(); j++) {
                    cout << "   Particle " << j << ": "               
                                << "id: (" << haloParticles->id(j) << ") "
                                << "position: (" << haloParticles->posX(j) << "," << haloParticles->posY(j) << "," << haloParticles->posZ(j) << ") "
                                << "velocity (" << haloParticles->velX(j) << "," << haloParticles->velY(j) << "," << haloParticles->velZ(j) << ")"
                                << endl;
                }
                float *haloVelocity = new float[3];
                simulation.halos(randomHalo)->calculateAvgVelocity(haloVelocity);
                cout << "   Halo Velocity "  
                                << " (" << haloVelocity[0] << "," << haloVelocity[1] << "," << haloVelocity[2] << ")"
                        << endl;
            }            
            break;
        }
        /* 
         * CUBE GRAV USAGE
         */
        case 4: 
        {
            cout << "Reading cube grav " << argv[1] << endl;            
            FOFCubeGrav grav(argv[1]);
            int levels = grav.availableLevels();            
            
            cout << "Cube Grav: " 
                            << levels << " levels, "
                            << "area: (" << grav.minX() << "," << grav.minY() << "," << grav.minZ() << ") "
                            << "to (" << grav.maxX() << "," << grav.maxY() << "," << grav.maxZ() << ")"
                            << endl;       
            
            grav.readLevels(false);
            for(int i=0; i<levels; i++) {
                cout << "  level " << i << ": " 
                        << grav.level(i)->nCells() << " cells"
                        << endl;
                int shown=0;
                for(int j=0; j<grav.level(i)->nCells(); j++) {
                    if(1) { //grav.level(i)->son(j) > 0) {
                        cout << "    " << j << "th cell of 1st level: " << endl
                            << "      position: (" << grav.level(i)->posX(j) << "," << grav.level(i)->posY(j) << "," << grav.level(i)->posZ(j) << ") " << endl
                            << "      force: (" << grav.level(i)->fX(j) << "," << grav.level(i)->fY(j) << "," << grav.level(i)->fZ(j) << ")" << endl
                            << "      rho: " << grav.level(i)->rho(j) << ", phi: " << grav.level(i)->phi(j) << ", redshift: " << grav.level(i)->redshift(j)
                                 << ", son: " << grav.level(i)->son(j)
                            << endl;
                        shown++;
                        if(shown>5) {
                            break;
                        }
                    }
                }
            }            
            grav.releaseLevels();
            break;
        }
        
        /* 
         * EXTREMA USAGE
         */
        case 5: 
        {
            cout << "Reading extrema " << argv[1] << endl;
            FOFExtrema extrema(argv[1]);
            cout << "OK" << endl;
            cout << "Read " << extrema.nExtrema() << endl;
            int maxExtremaToDisplay = 5;
            //for(int i=52; i<54; i++) {
            for(int i=0; i<min(maxExtremaToDisplay,extrema.nExtrema()); i++) {
                cout << "EXTREMUM " << i << ": " 
                        << "density:" << extrema.extremum(i)->density() << " "                        
                        << "seuil min:" << extrema.extremum(i)->minSeuil() << " avg: " << extrema.extremum(i)->avgSeuil()
                        << " center: (" << extrema.extremum(i)->x() << "," << extrema.extremum(i)->y() << "," << extrema.extremum(i)->z() << ") "
                        << endl;
            }   
             cout << "TOTAL " << extrema.nExtrema() << " extrema" << endl;
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
        cout << "Usage : FOFReader <file> <format> \r\n"
                "    Formats: \r\n"
                "        0: FOF Cube/Multicube\r\n"
                "        1: FOF Struct\r\n"
                "        2: FOF Masst\r\n"
                "        3: DEUS Halo directory (= masst + strct)\r\n"
                "        4: FOF Grav cube \r\n"
                "        5: FOF Extrema \r\n"
                << argc << endl;
        return 0;
    }
    return 0;
}

