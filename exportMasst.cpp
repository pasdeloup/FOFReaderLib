/* ************************** FOFReaderLib ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        FOFReaderLib
// TITLE :          FOFReaderLib
// DESCRIPTION :    Global include file
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2013)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           FOFReaderLib.h
/// \brief          Global include file
/// \author         Jean Pasdeloup (jean.pasdeloup@obspm.fr)
/// \date           2013
/// \copyright      CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/

#include <cmath>

#include "FOFReaderLib/FOFReaderLib.h"
#include "convert_cosmos.h"

using namespace std;

/*
 * Usage sample
 */
int main(int argc, char** argv) 
{    
    if (argc == 3) { // If correct number of args
        
            cout << "Reading masst " << argv[1] << endl;
            FOFMasst masst(argv[1]);
            
            ofstream myfile;
            cout << "Writing to " << argv[2] << endl;
            myfile.open (argv[2]);
            
            for(int i=0; i<masst.nHalos(); i++) {                
                float dist = sqrt(masst.halos(i)->x()*masst.halos(i)->x() + masst.halos(i)->y()*masst.halos(i)->y() + masst.halos(i)->z()*masst.halos(i)->z());
                float rho = sqrt(pow(masst.halos(i)->x(),2)+pow(masst.halos(i)->y(),2)+pow(masst.halos(i)->z(),2));                
                myfile << "INSERT INTO halos (id,x,y,z,npart,dist,redshift,rho,phi,theta) VALUES ("
                        << masst.halos(i)->id() << "," 
                        << masst.halos(i)->x() << "," 
                        << masst.halos(i)->y() << "," 
                        << masst.halos(i)->z() << "," 
                        << masst.halos(i)->mass() << ","
                        << dist * 21000 / 0.72 << ","
                        << convert_lcdm7[(int) (dist*10000)] << ","
                        << rho << ","
                        << acos(masst.halos(i)->z() / rho) << ","
                        << atan(masst.halos(i)->y() / masst.halos(i)->x())
                        << ");\n";                
            }            
             cout << "TOTAL " << masst.nHalos() << " halos" << endl;             
             myfile.close();
        
    }
    /*
     * USAGE
     */
    else {
        cout << "Usage : exportMasst <directory> <output.txt> \r\n"
                << argc << endl;
        return 0;
    }
    return 0;
}

