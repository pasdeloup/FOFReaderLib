/* ************************** FOFReaderLib ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        FOFReaderLib
// TITLE :          FOFExtremum
// DESCRIPTION :    FOF Extremum file management
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2015)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           FOFExtremum.h
/// \brief          FOF Extremum file management
/// \author         Jean Pasdeloup (jean.pasdeloup@obspm.fr)
/// \date           2015
/// \copyright      CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/

#ifndef FOFEXTREMA_H
#define	FOFEXTREMA_H

#include "FOFFile.h"
#include "FOFExtremum.h"

class FOFExtrema : protected FOFFile
{
public:
    FOFExtrema();
    FOFExtrema(const FOFExtrema& orig);
    FOFExtrema(std::string filename);
    virtual ~FOFExtrema();
        
    // Getters
    int nExtrema() {return _nExtrema;}
    std::vector<FOFExtremum*> extrema() {return _extrema;}
    FOFExtremum* extremum(int i) {return _extrema[i];}
    
    // Reader   
    void readExtremaFile(); // Open file and read masst
    void addExtremaFile(std::string filename); // add file and read masst
    
private:
    int _nExtrema;
    std::vector<FOFExtremum*> _extrema;

};

#endif	/* FOFEXTREMA_H */

