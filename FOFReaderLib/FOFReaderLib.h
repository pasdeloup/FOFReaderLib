/* ************************** FOFReaderLib ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        FOFReaderLib
// TITLE :          FOFReaderLib
// DESCRIPTION :    Global include file
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2013)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           FOFReaderLib.h
/// \brief          Global include file
/// \author         Jean Pasdeloup (jean.pasdeloup@obspm.fr)
/// \date           2013
/// \copyright      CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/

#ifndef FOFREADERLIB_H
#define	FOFREADERLIB_H

// Switch to make FOFReaderLib verbose: 
//   display Big Endian mode
//   display unreadable files when reading directories
//#define FOF_VERBOSE   

// Switch to Debug mode, add a lot of notifications when running
//#define FOF_DEBUG

#include "FOFFiles/FOFFile.h"
#include "FOFFiles/FOFCube.h"
#include "FOFFiles/FOFMultiCube.h"
#include "FOFFiles/FOFStrct.h"
#include "FOFFiles/FOFMasst.h"
#include "FOFFiles/FOFHalo.h"
#include "FOFFiles/FOFExtremum.h"
#include "FOFFiles/FOFExtrema.h"
#include "FOFFiles/FOFCubeGrav.h"
#include "DEUSSimulation/DEUSProfile.h"
#include "DEUSSimulation/DEUSHalos.h"
#include "DEUSSimulation/DEUSCubes.h"
#include "DEUSSimulation/DEUSGrav.h"
#include "DEUSSimulation/DEUSArea.h"
#include "DEUSSimulation/DEUSSimulationSingleton.h"

#endif	/* FOFREADERLIB_H */

