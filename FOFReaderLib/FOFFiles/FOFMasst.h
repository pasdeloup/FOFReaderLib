/* ************************** FOFReaderLib ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        FOFReaderLib
// TITLE :          FOFMasst
// DESCRIPTION :    FOF Masst file management
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2013)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           FOFMasst.h
/// \brief          FOF Masst file management
/// \author         Jean Pasdeloup (jean.pasdeloup@obspm.fr)
/// \date           2013
/// \copyright      CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/

#ifndef FOFMASST_H
#define	FOFMASST_H

#include "FOFFile.h"
#include "FOFHalo.h"

class FOFMasst : protected FOFFile
{
public:
    FOFMasst();
    FOFMasst(const FOFMasst& orig);
    FOFMasst(std::string filename);
    virtual ~FOFMasst();
        
    // Getters
    int nHalos() {return _nHalos;}
    std::vector<FOFHalo*> halos() {return _halos;}
    FOFHalo* halos(int i) {return _halos[i];}
    
    // Reader   
    void readMasstFile(); // Open file and read masst
    void addMasstFile(std::string filename); // add file and read masst
    
private:
    int _nHalos;
    std::vector<FOFHalo*> _halos;

};

#endif	/* FOFMASST_H */

