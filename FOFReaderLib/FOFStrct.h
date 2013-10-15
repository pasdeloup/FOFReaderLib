/* ********************************** CELL ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        DEUS_SERVER
// TITLE :          FOFStrct
// DESCRIPTION :    Mesh cells integrating particles
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2013)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           FOFStrct.h
/// \brief          Mesh cells integrating particles
/// \author         Jean Pasdeloup (jean.pasdeloup@obspm.fr)
/// \date           2013
/// \copyright      CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/

#ifndef FOFSTRCT_H
#define	FOFSTRCT_H

#include <string>

#include "FOFParticles.h"
#include "fortranfile.h"

class FOFStrct : protected FOFFile
{
public:
    FOFStrct();
    FOFStrct(const FOFStrct& orig);
    FOFStrct(std::string filename, bool readIds=false);
    virtual ~FOFStrct();
    
    // Getters
    int nHalos() {return _nHalos;}
    std::vector<FOFParticles*> halos() {return _halos;}
    FOFParticles* halos(int i) {return _halos[i];}
    
    // Reader   
    void readStrctFile(std::string filename, bool readIds=false); // Open file and read strct
    
protected:
    int _nHalos;
    std::vector<FOFParticles*> _halos;
    

};

#endif	/* FOFSTRCT_H */

