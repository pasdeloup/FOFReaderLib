/* ********************************** CELL ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        DEUS_SERVER
// TITLE :          DEUSArea
// DESCRIPTION :    Mesh cells integrating particles
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2013)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           DEUSArea.cpp
/// \brief          Mesh cells integrating particles
/// \author         Jean Pasdeloup (jean.pasdeloup@obspm.fr)
/// \date           2013
/// \copyright      CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/

#include "DEUSArea.h"
#include <iostream>

DEUSArea::DEUSArea()
{    
    this->initArea(1.0f);
    
}

DEUSArea::DEUSArea(float minX, float maxX, float minY, float maxY, float minZ, float maxZ, float periodicity)
{    
    this->initArea(periodicity);
    this->_coords[0][0][0] = minX;
    this->_coords[0][1][0] = minY;
    this->_coords[0][2][0] = minZ;
    this->_coords[0][0][1] = maxX;
    this->_coords[0][1][1] = maxY;
    this->_coords[0][2][1] = maxZ;
    this->calculateShift();
}

DEUSArea::DEUSArea(float X, float Y, float Z, float size, float periodicity)
{    
    this->initArea(periodicity);
    float halfsize = size/2.0f;
    this->_coords[0][0][0] = X - halfsize;
    this->_coords[0][1][0] = Y - halfsize;
    this->_coords[0][2][0] = Z - halfsize;
    this->_coords[0][0][1] = X + halfsize;
    this->_coords[0][1][1] = Y + halfsize;
    this->_coords[0][2][1] = Z + halfsize;
    this->calculateShift();
}

DEUSArea::DEUSArea(float *boundaries, float periodicity)
{   
    this->initArea(periodicity);    
    this->_coords[0][0][0] = boundaries[0];
    this->_coords[0][1][0] = boundaries[2];
    this->_coords[0][2][0] = boundaries[4];
    this->_coords[0][0][1] = boundaries[1];
    this->_coords[0][1][1] = boundaries[3];
    this->_coords[0][2][1] = boundaries[5];    
    this->calculateShift();
}

DEUSArea::DEUSArea(const DEUSArea& orig)
{
}

DEUSArea::~DEUSArea()
{
}

void DEUSArea::initArea(float periodicity)
{
    this->_periodicity = periodicity;
    float max = this->_periodicity != 0.0f ? this->_periodicity : 1.0f;
    for(int shift=0;shift<2;shift++) {
        for(int pos=0; pos<3; pos++) {
            for(int minmax=0; minmax<2; minmax++) {                
                if(shift == 1 && minmax == 1 && shift == 0) {
                    this->_coords[shift][pos][minmax] = max;
                }
                else {                    
                    this->_coords[shift][pos][minmax] = 0.0f;                    
                }
            }
        }
    }
}

void DEUSArea::calculateShift()
{
    if(this->_periodicity == 0.0f) {
        return;
    }
    for(int pos=0; pos<3; pos++) {
        if(this->_coords[0][pos][0] < 0.0f) {
            this->_coords[1][pos][0] = this->_periodicity + this->_coords[0][pos][0];
            this->_coords[1][pos][1] = this->_periodicity;
            this->_coords[0][pos][0] = 0.0f;
            this->_shift[1][pos] = -this->_periodicity;
        }
        if(this->_coords[0][pos][1] > this->_periodicity) {
            this->_coords[1][pos][0] = 0.0f;
            this->_coords[1][pos][1] = this->_coords[0][pos][0] - this->_periodicity;
            this->_coords[0][pos][1] = this->_periodicity;
            this->_shift[0][pos] = -this->_periodicity;
        }
    }
}

bool DEUSArea::particuleIsInside(float &X, float &Y, float &Z)
{
    return false;
}

bool DEUSArea::intersectArea(DEUSArea area)
{
    bool res = true;
    for(int pos=0; pos<3; pos++) {
        bool subres = false;
        for(int shift=0; shift<2; shift++) {
            for(int shift2=0; shift2<2; shift2++) {
                subres |= this->coords(shift, pos, 0) < area.coords(shift2,pos, 1) && this->coords(shift, pos, 1) > area.coords(shift2,pos, 0);
            }
        }
        res &= subres;
    }    
    return res;    
}

bool DEUSArea::cubeIntersect(float *cubeBoundaries)
{    
    return this->intersectArea(DEUSArea(cubeBoundaries));
}

void DEUSArea::display()
{
    std::cout << "Area: " << std::endl
            << "(" << this->coords(0,0,0) << "," << this->coords(0,1,0) << "," << this->coords(0,2,0) << ")"
            << " to (" << this->coords(0,0,1) << "," << this->coords(0,1,1) << "," << this->coords(0,2,1) << ")"
            << std::endl << "AND" << std::endl
            << "(" << this->coords(1,0,0) << "," << this->coords(1,1,0) << "," << this->coords(1,2,0) << ")"
            << " to (" << this->coords(1,0,1) << "," << this->coords(1,1,1) << "," << this->coords(1,2,1) << ")"
            << std::endl;
}

