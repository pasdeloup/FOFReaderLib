/* 
 * FOF Export Masst
 * Usage sample
 * Author: jpasdeloup
 * Created on 29 april 2014, 16:22
 */

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
                myfile << 
                        masst.halos(i)->x() << ";" 
                        << masst.halos(i)->y() << ";" 
                        << masst.halos(i)->z() << ";" 
                        << masst.halos(i)->mass() << ";"
                        //<< dist * 21000 / 0.72 << ";"
                        //<< convert_lcdm7[(int) (dist*10000)]
                        << "\n";                
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

