/* ********************************** CELL ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        DEUS_SERVER
// TITLE :          DEUSSimulationSingleton
// DESCRIPTION :    Mesh cells integrating particles
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2013)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           DEUSSimulationSingleton.cpp
/// \brief          Mesh cells integrating particles
/// \author         Jean Pasdeloup (jean.pasdeloup@obspm.fr)
/// \date           2013
/// \copyright      CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/

#include "DEUSSimulationSingleton.h"

#define DEBUG_FOF

DEUSSimulationSingleton::DEUSSimulationSingleton(std::string cubedir, std::string halodir = "")
{    
    std::cout << "Reading cube " << cubedir << "... " << std::endl;
    _cubes = new FOFMultiCube(cubedir, FOFParticles::DONT_READ_PARTICLES);
    std::cout << "OK" << std::endl;
    std::cout << "Reading halos " << halodir << "... " << std::endl;
    _halos = new DEUSHalos(halodir);
    std::cout << "OK" << std::endl;    
}

DEUSSimulationSingleton::DEUSSimulationSingleton(const DEUSSimulationSingleton& orig)
{
}

DEUSSimulationSingleton::~DEUSSimulationSingleton()
{
}

DEUSSimulationSingleton *DEUSSimulationSingleton::getInstance(std::string cubedir, std::string halodir)
{
    if (NULL == _instance) {
#ifdef DEBUG_FOF  
        std::cout << "creating singleton." << std::endl;
#endif
        _instance = new DEUSSimulationSingleton(cubedir, halodir);
    }
    else {
#ifdef DEBUG_FOF  
        std::cout << "singleton already created!" << std::endl;
#endif
    }

    return _instance;
}

void DEUSSimulationSingleton::kill()
{
    if (NULL != _instance) {
        delete _instance;
        _instance = NULL;
    }
}

// Initialisation du singleton à NULL
DEUSSimulationSingleton *DEUSSimulationSingleton::_instance = NULL;