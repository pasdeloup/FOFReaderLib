/* ************************** FOFReaderLib ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        FOFReaderLib
// TITLE :          FOFReaderLib
// DESCRIPTION :    Find cube files in a specific area
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2013)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           FOFReaderLib.h
/// \brief          Find cube files in a specific area
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
    if (argc == 6 or argc == 7) { // If correct number of args
        
        float periodicity = 0.0f;
        if(argc == 7) {
            periodicity = atof(argv[6]);
        }
        
        DEUSArea *area;
        area = new DEUSArea(
                        atof(argv[2]),
                        atof(argv[3]),
                        atof(argv[4]),
                        atof(argv[5]),
                        periodicity);
         
        /* 
         * MULTI CUBE USAGE
         */
      
        //cout << "Reading multicube " << argv[1] << endl;

        FOFMultiCube multi(argv[1], FOFParticles::DONT_READ_PARTICLES); // don't use default, don't read particles just header

        for(int i=0; i<multi.nCubes(); i++) {            
            if (area->cubeIntersect(multi.cubes(i)->boundaries())) {
                cout << multi.cubes(i)->getFilename() << endl;
            }
        }        
        
    }
    /*
     * USAGE
     */
    else {
        cout << "Get the file list needed for a subregion\r\n"
                "Usage : getAreaFiles <directory> <center_x> <center_y> <center_z> <size> [periodicity]\r\n"
                "     center_x / center_y / center_z : center to get in float\r\n"
                "        center of snapshots is 0.5 0.5 0.5\r\n"
                "        center of cone (ie Z=0) is 0.0 0.0 0.0\r\n"
                "     size : size to get in float (max 1.0)\r\n"
                "     periodicity : 1.0 for snapshots 0.0 (none, default) for cone\r\n"
                << argc << endl;
        return 0;
    }
    return 0;
}

