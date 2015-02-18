/* ************************** FOFReaderLib ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        FOFReaderLib
// TITLE :          FOFCubeGravLevel
// DESCRIPTION :    FOF Cubegrav level management, used by FOFCubeGrav
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2013)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           FOFCubeGravLevel.h
/// \brief          FOF Cubegrav level management, used by FOFCubeGrav
/// \author         Jean Pasdeloup (jean.pasdeloup@obspm.fr)
/// \date           2013
/// \copyright      CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/

#ifndef FOFCUBEGRAVLEVEL_H
#define	FOFCUBEGRAVLEVEL_H

#include "FOFFile.h"

class FOFCubeGravLevel : protected FOFFile {
public:
	FOFCubeGravLevel();
        FOFCubeGravLevel(FortranFile<unsigned int> *fortranFile);
	FOFCubeGravLevel(const FOFCubeGravLevel& orig);
	virtual ~FOFCubeGravLevel();
        
        // Getters
        int nCells() {return _nCells;}    
        std::vector<float> position() {return _position;}
        std::vector<float> force() {return _force;}
        std::vector<float> redshift() {return _redshift;}
        std::vector<int> son() {return _son;}

        // Setter
        void nCells(int ncells) {this->_nCells = ncells;}    

        // Enhanced getters
        float posX(int i) {return _position[i * 3];}
        float posY(int i) {return _position[i * 3 + 1];}
        float posZ(int i) {return _position[i * 3 + 2];}

        float fX(int i) {return _force[i * 3];}
        float fY(int i) {return _force[i * 3 + 1];}
        float fZ(int i) {return _force[i * 3 + 2];}
        
        float redshift(int i) {return _redshift[i];}
        float phi(int i) {return _phi[i];}
        float rho(int i) {return _rho[i];}
        int son(int i) {return _son[i];}
        
        // Read / Release
        void readLevel();
        void releaseLevel();
        
protected:
    std::streamoff _streampos; // position of the start of particles in the file
    int _nCells;
    std::vector<float> _position;
    std::vector<float> _force;
    std::vector<float> _redshift;  
    std::vector<float> _phi;
    std::vector<float> _rho;
    std::vector<int> _son;
};

#endif	/* FOFCUBEGRAVLEVEL_H */

