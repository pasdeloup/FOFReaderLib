/* 
 * File:   FOFCubeGravLevel.cpp
 * Author: jpasdeloup
 * 
 * Created on June 18, 2014, 2:48 PM
 */

#include "FOFCubeGravLevel.h"

FOFCubeGravLevel::FOFCubeGravLevel() 
{
}

FOFCubeGravLevel::FOFCubeGravLevel(FortranFile<unsigned int> *fortranFile)
{
    this->_fortranFile = fortranFile; 
    this->_filename = fortranFile->name();
    this->_streampos = fortranFile->readStream()->tellg();
}

FOFCubeGravLevel::FOFCubeGravLevel(const FOFCubeGravLevel& orig) 
{
}

FOFCubeGravLevel::~FOFCubeGravLevel() 
{
}

void FOFCubeGravLevel::readLevel()  // Read level from already opened file.
{ 
    unsigned int len = this->_nCells;
#ifdef DEBUG_FOF    
    std::cout << "Len = " << len << std::endl;
#endif
    
    this->_position.reserve(len * 3);    
    this->_fortranFile->readVector(this->_position, false);    
    if (this->_position.size() != len * 3) {        
        throw std::ios_base::failure("ERROR : FOFCubeGravLevel read position len");
    }
    
    this->_force.reserve(len * 3);
    this->_fortranFile->readVector(this->_force, false);
    if (this->_force.size() != len * 3) {
        throw std::ios_base::failure("ERROR : FOFCubeGravLevel read velocity force");
    }
    
    this->_redshift.reserve(len);
    this->_fortranFile->readVector(this->_redshift, false);
    if (this->_redshift.size() != len) {
       throw std::ios_base::failure("ERROR : FOFCubeGravLevel read id redshift");            
    }
    
    this->_phi.reserve(len);
    this->_fortranFile->readVector(this->_phi, false);
    if (this->_phi.size() != len) {
        throw std::ios_base::failure("ERROR : FOFCubeGravLevel read phi redshift");            
    }
    
    this->_rho.reserve(len);
    this->_fortranFile->readVector(this->_rho, false);
    if (this->_redshift.size() != len) {
        throw std::ios_base::failure("ERROR : FOFCubeGravLevel read rho redshift");            
    }
    
    this->_son.reserve(len);
    this->_fortranFile->readVector(this->_son, false);
    if (this->_son.size() != len) {
        throw std::ios_base::failure("ERROR : FOFCubeGravLevel read son redshift");            
    }  
}

void FOFCubeGravLevel::releaseLevel()
{
    this->_position.clear();
    std::vector<float>().swap(this->_position);
    this->_force.clear();
    std::vector<float>().swap(this->_force);
    this->_redshift.clear();
    std::vector<float>().swap(this->_redshift);
    this->_phi.clear();
    std::vector<float>().swap(this->_phi);
    this->_rho.clear();
    std::vector<float>().swap(this->_rho);
    this->_son.clear();
    std::vector<int>().swap(this->_son);
}

