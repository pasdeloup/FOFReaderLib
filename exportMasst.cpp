/* ************************** FOFReaderLib ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        FOFReaderLib
// TITLE :          exportMasst
// DESCRIPTION :    Export Masst into CSV file
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2013)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           exportMasst.cpp
/// \brief          Export Masst into CSV file
/// \author         Jean Pasdeloup (jean.pasdeloup@obspm.fr)
/// \date           2013
/// \copyright      CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/

#include <cmath>
#include <iomanip>

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
            
            // CSV MODE
            string header = "id;x;y;z;mass\n"; // use "" for SQL
            string row_separator = ";"; // use "," for SQL
            string line_separator = "\n"; // use ");\n" for SQL
            string line_start = ""; // use for SQL "INSERT INTO halos (id,x,y,z,npart,dist,redshift,rho,phi,theta) VALUES ("
            string footer = "";
            
            // SQL MODE
//            string header = "CREATE TABLE IF NOT EXISTS halos (id int not null primary key, x float, y float, z float, npart int);\n"; 
//            string row_separator = ","; 
//            string line_separator = ");\n"; 
//            string line_start = "INSERT INTO halos (id,x,y,z,npart) VALUES (";
//            string footer = "";
                        
            ofstream myfile;
            cout << "Writing to " << argv[2] << endl;
            myfile.open (argv[2]);
            
            myfile << header;
            
            for(int i=0; i<masst.nHalos(); i++) {                
                
                // Additional calculated rows for cones (spherical coordinates)
                //float dist = sqrt(masst.halos(i)->x()*masst.halos(i)->x() + masst.halos(i)->y()*masst.halos(i)->y() + masst.halos(i)->z()*masst.halos(i)->z());
                //float rho = sqrt(pow(masst.halos(i)->x(),2)+pow(masst.halos(i)->y(),2)+pow(masst.halos(i)->z(),2));                
                //float dist_norm =  dist * 21000 / 0.72;
                //float redshift = convert_lcdm7[(int) (dist*10000)];  // use included table
                //float phi = acos(masst.halos(i)->z() / rho);
                //float theta = atan(masst.halos(i)->y() / masst.halos(i)->x());
                
                myfile 
                        << line_start
                        //<< setprecision(6) // Default to 6 as it is the safe value for single precision float
                        << masst.halos(i)->id() << row_separator
                        << masst.halos(i)->x() << row_separator
                        << masst.halos(i)->y() << row_separator
                        << masst.halos(i)->z() << row_separator
                        << masst.halos(i)->mass()                         
                        << line_separator
                        ;                        
            }            
            myfile << footer;
            
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

