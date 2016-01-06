/* ************************** FOFReaderLib ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        FOFReaderLib
// TITLE :          FOFCube
// DESCRIPTION :    FOF Cube file management
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2013)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           FOFCube.cpp
/// \brief          FOF Cube file management
/// \author         Jean Pasdeloup (jean.pasdeloup@obspm.fr)
/// \date           2013
/// \copyright      CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/

#include <cassert>
#include <random>

#include "../FOFReaderLib.h"

FOFCube::FOFCube() : _boundaries(0)
{
}

FOFCube::FOFCube(std::string filename, int readParticles)
{
    this->_streampos = 0;
    this->_filename = filename;
    this->readCubeFile(readParticles);
}

FOFCube::FOFCube(FortranFile<unsigned int> *fortranFile)
{
    this->_fortranFile = fortranFile; 
    this->_filename = fortranFile->name();
    this->_streampos = fortranFile->readStream()->tellg();
}

FOFCube::FOFCube(const FOFCube& orig)
{
}

FOFCube::FOFCube(int npart, int generator)
{
    this->_npart = this->_originalNpart = npart;
    
    this->_position.resize(npart * 3);
    this->_velocity.resize(npart * 3);
    this->_id.resize(npart);
    
    this->_boundaries = new float[6];
    this->_boundaries[0] = this->_boundaries[2] = this->_boundaries[4] = 0.0f;
    this->_boundaries[1] = this->_boundaries[3] = this->_boundaries[5] = 1.0f;
    
    switch(generator) {
        case RANDOM_GENERATOR:
            this->generateRandomParticles();
            break;
        case HOMOGENOUS_GENERATOR:
            this->generateHomogeneousParticles();
            break;
        default:
            this->generateConstantParticles();
    }
}

FOFCube::~FOFCube()
{
    delete this->_boundaries;
}

void FOFCube::generateConstantParticles() 
{        
    for(int i=0; i<(this->_npart); i++) {
        this->_id[i] = i;
        this->_position[i*3 + 0] = 0.5f;
        this->_position[i*3 + 1] = 0.5f;
        this->_position[i*3 + 2] = 0.5f;
        this->_velocity[i*3 + 0] = 0.0f;
        this->_velocity[i*3 + 1] = 0.0f;
        this->_velocity[i*3 + 2] = 0.0f;        
    }
}

void FOFCube::generateRandomParticles() 
{
    // C++11 Random generator
    std::random_device rd;
    std::mt19937 gen(rd());
        
    for(int i=0; i<(this->_npart); i++) {
        this->_id[i] = i;        
        this->_position[i*3 + 0] = std::generate_canonical<double, 32>(gen);
        this->_position[i*3 + 1] = std::generate_canonical<double, 32>(gen);
        this->_position[i*3 + 2] = std::generate_canonical<double, 32>(gen);
        this->_velocity[i*3 + 0] = std::generate_canonical<double, 32>(gen);
        this->_velocity[i*3 + 1] = std::generate_canonical<double, 32>(gen);
        this->_velocity[i*3 + 2] = std::generate_canonical<double, 32>(gen);        
    }
}

void FOFCube::generateHomogeneousParticles() {
    
    int len = round(pow(this->_npart, 1.0/3));
    if(pow(len,3) != this->_npart) {
        std::cout << "Error: for homogeneous generation, number of part should be a power of 3 : 256³, 512³, ..."  << this->_npart << " != " << len << "^3" << std::endl;
        exit(1);
    }
    float step = 1.0f/len;
    
    for(int i=0; i<len; i++) {
        for(int j=0; j<len; j++) {
            for(int k=0; k<len; k++) {
                int pos = i + j*len + k*len*len;
                this->_id[pos] = pos;
                this->_position[pos*3 + 0] = i * step;
                this->_position[pos*3 + 1] = j * step;
                this->_position[pos*3 + 2] = k * step;
                this->_velocity[pos*3 + 0] = 0.0f;
                this->_velocity[pos*3 + 1] = 0.0f;
                this->_velocity[pos*3 + 2] = 0.0f;        
            }
        }        
    }
}

// Read cube from already opened file (can use external FortranFile for multicube reading)
void FOFCube::readCube(bool skipNpart, int readParticles)
{
    unsigned int len = 0;
    
    if(not skipNpart) {        
        this->_fortranFile->read(this->_npart);
        this->_originalNpart = this->_npart;
    }
    
    this->_fortranFile->read(this->_procid);                    
        
    this->_boundaries = new float[6];
    this->_fortranFile->readArray<float>(this->_boundaries, len); // min/max
    assert(len == 6);
    this->setStreampos();
    if(readParticles > 0) {
        this->readParticles(readParticles);
    }
    else { // Else ignore to go to next cube
        this->skipParticles();
    }
}

// Open file and read cube (not multi)
void FOFCube::readCubeFile(int readParticles)
{       
    this->_npart = this->_originalNpart = this->openAndReadFirstInt();
    if(npart() < 0) {
        throw std::ios_base::failure("ERROR : FOFCube multicube format");
    }
    this->readCube(true, readParticles);
    this->close();
}

// Open file and write cube
void FOFCube::writeCubeFile(std::string filename)
{
    std::cout << "Writing " << filename << std::endl;
    
    FortranFile<unsigned int> *writeFile;
    writeFile= new FortranFile<unsigned int>;
    writeFile->openWrite(filename);
    
    writeFile->write(this->_npart);
    writeFile->write(0); // nproc
    writeFile->writeArray<float>(this->_boundaries, 6); // min/max
    
    writeFile->writeVector(this->_position);
    writeFile->writeVector(this->_velocity);
    writeFile->writeVector(this->_id);
    
    writeFile->close();
}