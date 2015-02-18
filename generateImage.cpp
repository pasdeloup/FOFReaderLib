/* ************************** FOFReaderLib ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        FOFReaderLib
// TITLE :          FOFReaderLib
// DESCRIPTION :    Image generation from gravity files
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2013)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           FOFReaderLib.h
/// \brief          Image generation from gravity files
/// \author         Jean Pasdeloup (jean.pasdeloup@obspm.fr)
/// \date           2013
/// \copyright      CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/

#include <cstdlib>
#include <fstream>
#include <sstream>

#define DEBUG_FOF

#include "FOFReaderLib/FOFReaderLib.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) 
{
    if (argc == 3) { // If correct number of args
        cout << "Reading grav " << argv[1] << endl;
       
        cout << "Writing to " << argv[2] << endl;
        
        ofstream myFile (argv[2], ios::out | ios::binary);
        
        int width = 8192;
        float *image = new float[width*width];
        
        for(int i=0; i<width*width; i++) {
            image[i] = -10.0f;
        }
        
        DEUSGrav GravFiles(argv[1]);
          
        cout << "NFiles = " << GravFiles.nFiles() << endl;
                
        float resolution = 8192.0f;
        float deltaCenter = 1.0f / resolution / 2.0f;
                
        float minRho = 1000.0f;
        float maxRho = -1000.0f;
        
        float minZ = 0;
        float maxZ = deltaCenter * 2.0f;
        
        unsigned int ncell = 0;
        unsigned int nfiles = 0;
        
        for(unsigned int f=0; f<GravFiles.nFiles(); f++) {
            
            FOFCubeGrav *grav = GravFiles.cubeGrav(f);
            
            if(grav->minZ() <= maxZ && grav->maxZ() >= minZ
               //     && grav->minX() <= maxZ && grav->maxX() >= minZ
               //     && grav->minY() <= maxZ && grav->maxY() >= minZ                    
                    ) {
                
                //cout << grav->filename() <<  " ";     
                
                cout << "Cube " << f << " : " << grav->minZ() << " < Z < " << grav->maxZ() 
                    << " - " << grav->minY() << " < Y < " << grav->maxY() 
                    << " - " << grav->minX() << " < X < " << grav->maxX() << endl;
                
                cout << "=> Reading Cube " << f << " " << grav->filename() <<  "... ";                
                cout << "nb levels = " << grav->availableLevels() << endl;
                cout << "Level 0 = " << grav->level(0)->nCells() << endl;                
                grav->readLevels(true);
                cout << "OK" << endl;
                
                
                int deltaCellX = 0; //(int) (grav->minX() * resolution);
                int deltaCellY = 0; //(int) (grav->minY() * resolution);
        
                // Get values
                for(int j=0; j<grav->level(0)->nCells(); j++) {
                    if(grav->level(0)->posZ(j) > minZ && grav->level(0)->posZ(j) < maxZ) {
                        
                        ncell++;
                        
                        int x = ((grav->level(0)->posX(j) - deltaCenter + 0.5f) * (float) resolution) - deltaCellX;
                        int y = ((grav->level(0)->posY(j) - deltaCenter + 0.5f) * (float) resolution) - deltaCellY;

                        if(x > width || x < 0) { cout << "ERROR X value: " << x << " for " << grav->level(0)->posX(j) << endl; }
                        if(y > width || y < 0) { cout << "ERROR Y value: " << y << " for " << grav->level(0)->posY(j) << endl; }

                        image[x+width*y] = grav->level(0)->rho(j);

                        if(image[x+width*y] > maxRho) { maxRho = image[x+width*y];}
                        if(image[x+width*y] < minRho) { minRho = image[x+width*y];}
                    }            
                }
                grav->releaseLevels();
                nfiles++;
            }
        }
                
        // Now normalize
        cout << nfiles << " files - " << ncell << " cells - min rho= " << minRho << ", max rho= " << maxRho << endl;        

        myFile.write ((char*)image, width*width*4);        
        myFile.close();
        
        
    }
    else {
        cout << "Usage : generateImage <directory> <output.gray> \r\n"
                << argc << endl;
        return 0;
    }
    
    return 0;
}

