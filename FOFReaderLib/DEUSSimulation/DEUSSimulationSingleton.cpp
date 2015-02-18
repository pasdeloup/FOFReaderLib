/* ************************** FOFReaderLib ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        FOFReaderLib
// TITLE :          DEUSSimulationSingleton
// DESCRIPTION :    Full simulation management ie cubes + halos with singleton
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2014)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           DEUSSimulationSingleton.cpp
/// \brief          Full simulation management ie cubes + halos with singleton
/// \author         Jean Pasdeloup (jean.pasdeloup@obspm.fr)
/// \date           2014
/// \copyright      CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/

#include "../FOFReaderLib.h"

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
#ifdef FOF_DEBUG  
        std::cout << "creating singleton." << std::endl;
#endif
        _instance = new DEUSSimulationSingleton(cubedir, halodir);
    }
    else {
#ifdef FOF_DEBUG  
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