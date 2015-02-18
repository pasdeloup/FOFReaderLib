/* ************************** FOFReaderLib ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        FOFReaderLib
// TITLE :          FOFReaderLib
// DESCRIPTION :    Find biggests halos of a simulation
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2013)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           FOFReaderLib.h
/// \brief          Find biggests halos of a simulation
/// \author         Jean Pasdeloup (jean.pasdeloup@obspm.fr)
/// \date           2013
/// \copyright      CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/

#include <sys/types.h>
#include <sys/stat.h>
#include <string>
#include <errno.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <algorithm>    // std::sort

#include "FOFReaderLib/FOFReaderLib.h"

using namespace std;

bool contains(const string &haystack, const string &needle);
bool massCompare (FOFHalo *i,FOFHalo *j) { return (i->mass()>j->mass()); }

/*
 * 
 */
int main(int argc, char** argv) {    
    DIR *Dir;
    struct dirent *DirEntry;
    vector<FOFHalo*> halos;
    int nbTops = 10;
    
    if(argc == 3) {
        nbTops = atoi(argv[2]);
        argc--;
    }
    
    if (argc == 2) {
        
        Dir = opendir(argv[1]);
        if (Dir == NULL) {
            cout << argv[1] << " is not a directory" << endl;
            return 2;
        }

        while ((DirEntry = readdir(Dir))) {
            if (contains(DirEntry->d_name,"masst")) {
                cout << "Reading " << DirEntry->d_name;                
                
                FOFMasst masst(string(argv[1]) + "/" + DirEntry->d_name);
                //std::cout << "halo " << DirEntry->d_name << " mass=" << masst.halos(0)->mass() << std::endl;
                for(int i=0; i<masst.nHalos(); i++) {
                   FOFHalo *newHalo = new FOFHalo(
                           masst.halos(i)->id(),
                           masst.halos(i)->x(),
                           masst.halos(i)->y(),
                           masst.halos(i)->z(),
                           masst.halos(i)->mass());
                   halos.push_back(newHalo);
                }                        
                cout << "(" << masst.nHalos() << " halos)" <<  endl;                  
            }
           
        }
        std::sort(halos.begin(),halos.end(),massCompare);
        
        std::cout << "TOTAL = " << halos.size() << " halos" << std::endl;
        
        std::cout << "TOP " << nbTops << " HALOS:" << std::endl;
        
        for(int i=0; i<nbTops; i++) {
            std::cout << "halo " << i+1 
                    << ": id=" << halos[i]->mass() 
                    << " mass=" << halos[i]->mass() 
                    << " pos=(" << halos[i]->x() << "," << halos[i]->y() << "," << halos[i]->z() << ")"
                    << std::endl;
        }
 
    } else {
        cout << "Get top N halos from masst files" << endl;
        cout << "  Usage: getBiggestHalo full_path [nbTops]" << endl;
        cout << "  Example: getBiggestHalo /mySimulation/post/fof/output00025/ 5" << endl;
        return 1;
    }


    return 0;
}


bool contains(const string &haystack, const string &needle)
{
    int sleng = haystack.length();
    int nleng = needle.length();

    if (sleng==0 || nleng==0)
        return false;

    for(int i=0, j=0; i<sleng; j=0, i++ )
    {
        while (i+j<sleng && j<nleng && haystack[i+j]==needle[j])
            j++;
        if (j==nleng)
            return true;
    }
    return false;
}

