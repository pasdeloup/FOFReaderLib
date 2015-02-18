/* ************************** FOFReaderLib ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        FOFReaderLib
// TITLE :          DEUSCubes
// DESCRIPTION :    Tools to manage cubes
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2014)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           DEUSCubes.h
/// \brief          Tools to manage cubes
/// \author         Jean Pasdeloup (jean.pasdeloup@obspm.fr)
/// \date           2014
/// \copyright      CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/

#ifndef DEUSCUBE_H
#define	DEUSCUBE_H

#include "DEUSArea.h"
#include "../FOFFiles/FOFMultiCube.h"

class DEUSCubes {
public:
    DEUSCubes();
    DEUSCubes(const DEUSCubes& orig);
    virtual ~DEUSCubes();
    FOFCube *cubes(int i) {return _cubes.cubes(i);}
private:
    FOFMultiCube _cubes;

};

#endif	/* DEUSCUBE_H */

