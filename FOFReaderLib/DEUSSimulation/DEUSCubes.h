/* ********************************** CELL ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        DEUS_SERVER
// TITLE :          DEUSCube
// DESCRIPTION :    Mesh cells integrating particles
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2013)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           DEUSCube.h
/// \brief          Mesh cells integrating particles
/// \author         Jean Pasdeloup (jean.pasdeloup@obspm.fr)
/// \date           2013
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

