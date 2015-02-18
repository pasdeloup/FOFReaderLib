/* ************************** FOFReaderLib ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        FOFReaderLib
// TITLE :          FOFStrct
// DESCRIPTION :    FOF Strct file management
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2013)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           FOFStrct.h
/// \brief          FOF Strct file management
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
    FOFStrct(std::string filename, int readParticles = FOFParticles::READ_POS | FOFParticles::READ_VEL);
    virtual ~FOFStrct();
    
    // Getters
    int nHalos() {return _nHalos;}
    std::vector<FOFParticles*> halos() {return _halos;}
    FOFParticles* halos(int i) {return _halos[i];}
    
    // Reader   
    void readStrctFile(int readParticles = FOFParticles::READ_POS | FOFParticles::READ_VEL); // Open file and read strct
    void addStrctFile(std::string filename, int readParticles = FOFParticles::READ_POS | FOFParticles::READ_VEL);
    
protected:
    int _nHalos;
    std::vector<FOFParticles*> _halos;
    

};

#endif	/* FOFSTRCT_H */

