/* ************************** FOFReaderLib ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        FOFReaderLib
// TITLE :          DEUSSimulationSingleton
// DESCRIPTION :    Full simulation management ie cubes + halos with singleton
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2014)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           DEUSSimulationSingleton.h
/// \brief          Full simulation management ie cubes + halos with singleton
/// \author         Jean Pasdeloup (jean.pasdeloup@obspm.fr)
/// \date           2014
/// \copyright      CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/

#ifndef DEUSSIMULATIONSINGLETON_H
#define	DEUSSIMULATIONSINGLETON_H

#include "DEUSHalos.h"
#include "../FOFFiles/FOFMultiCube.h"

class DEUSSimulationSingleton {
public:
    static DEUSSimulationSingleton *getInstance(std::string cubedir, std::string halodir);
    static void kill();
    DEUSHalos *halos() {return _halos;}
    FOFMultiCube *cubes() {return _cubes;}

private:
    DEUSSimulationSingleton(std::string cubedir, std::string halodir);
    DEUSSimulationSingleton(const DEUSSimulationSingleton& orig);
    virtual ~DEUSSimulationSingleton();

    DEUSHalos *_halos;
    FOFMultiCube *_cubes;

    static DEUSSimulationSingleton *_instance;
};

#endif	/* DEUSSIMULATIONSINGLETON_H */

