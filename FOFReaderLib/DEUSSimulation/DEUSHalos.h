/* ************************** FOFReaderLib ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        FOFReaderLib
// TITLE :          DEUSHalos
// DESCRIPTION :    Tools to manage halos using masst + strct
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2014)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           DEUSHalos.h
/// \brief          Tools to manage halos using masst + strct
/// \author         Jean Pasdeloup (jean.pasdeloup@obspm.fr)
/// \date           2014
/// \copyright      CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/

#ifndef DEUSHALOS_H
#define	DEUSHALOS_H

#include "../FOFFiles/FOFStrct.h"
#include "../FOFFiles/FOFMasst.h"
#include "../FOFFiles/FOFFile.h"
#include "DEUSHalo.h"

class DEUSHalos {
public:
    DEUSHalos();
    DEUSHalos(std::string directory);
    DEUSHalos(const DEUSHalos& orig);
    virtual ~DEUSHalos();
    
    DEUSHalo *halos(int i) {return _halos[i];}
    std::string filename(int i) {return _masstFilename[i];}
    long long nHalos() {return _halos.size();}
    int nFiles() {return _masstFilename.size();}
    void loadParticles(int i, int mode = FOFParticles::READ_POS|FOFParticles::READ_VEL);    
    void releaseParticles(int i);    
    
private:
    void loadMasst();    
    
    FOFFile *_directory;
    std::vector<DEUSHalo*> _halos;
    std::vector<std::string> _masstFilename;

};

#endif	/* DEUSHALOS_H */

