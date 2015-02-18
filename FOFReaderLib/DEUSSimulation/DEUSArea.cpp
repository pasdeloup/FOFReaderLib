/* ************************** FOFReaderLib ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        FOFReaderLib
// TITLE :          DEUSArea
// DESCRIPTION :    Tools to manage areas
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2014)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           DEUSArea.cpp
/// \brief          Tools to manage areas
/// \author         Jean Pasdeloup (jean.pasdeloup@obspm.fr)
/// \date           2014
/// \copyright      CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/

#include <iostream>
#include <math.h> 
#include <algorithm> 

#include "../FOFReaderLib.h"

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

DEUSArea::DEUSArea(float X, float Y, float Z, float LX, float LY, float LZ, float angle, float length, float periodicity)
{
    this->initArea(periodicity); 
    
    // First calculate angle
    float vx = LX-X;
    float vy = LY-Y;
    float vz = LZ-Z;
    
    float pi = 4.*atan(1.);
    float rho = sqrt(vx*vx+vy*vy+vz*vz);    
    float phi = acos(vz/rho);
    float theta;
    
    angle = angle * atan(1.) / 90; // convert to radian and divide per 2 (used as +/- angle)
    
    if(vy == 0) {
        theta = vx>0 ? 0 : pi;        
    }
    else {
        theta = acos(vx/(sqrt(vx*vx+vy*vy)));
        if(vy>0) {
            theta = 2*pi - theta;
        }
    }   
    
    // Then compute projected lookat
    float lx2 = length*sin(phi)*cos(theta)+X;
    float ly2 = length*sin(phi)*sin(theta)+Y;
    float lz2 = length*cos(phi)+Z;
    float R = length*tan(angle);
    
    std::cout << "pi= " << pi
            << ", rho=" << rho
            << ", phi=" << phi
            << ", theta=" << theta
            << ", lx2=" << lx2
            << ", ly2=" << ly2
            << ", lz2=" << lz2
            << ", R=" << R
            << std::endl;
        
    // Now make area
    this->_coords[0][0][0] = std::min(std::min(X,lx2),std::min(lx2-R,lx2+R));
    this->_coords[0][1][0] = std::min(std::min(Y,ly2),std::min(ly2-R,ly2+R));
    this->_coords[0][2][0] = std::min(std::min(Z,lz2),std::min(lz2-R,lz2+R));
    this->_coords[0][0][1] = std::max(std::max(X,lx2),std::max(lx2-R,lx2+R));
    this->_coords[0][1][1] = std::max(std::max(Y,ly2),std::max(ly2-R,ly2+R));
    this->_coords[0][2][1] = std::max(std::max(Z,lz2),std::max(lz2-R,lz2+R));
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
            this->_shift[shift][pos] = 0.0f;
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
            this->_coords[1][pos][1] = this->_coords[0][pos][1] - this->_periodicity;
            this->_coords[0][pos][1] = this->_periodicity;
            this->_shift[1][pos] = this->_periodicity;
        }
    }
}

bool DEUSArea::particuleIsInside(float &X, float &Y, float &Z)
{
    float coords[3] = {X,Y,Z};
    int nbShift = this->_periodicity == 0.0f ? 1 : 2;  
    bool res = true;
    for(int pos=0; pos<3; pos++) {
        bool subres = false;
        for(int shift=0; shift<nbShift; shift++) {            
            bool subsubres = coords[pos] < this->coords(shift,pos, 1) && coords[pos] > this->coords(shift,pos, 0);
            if(subsubres) {
                coords[pos] += this->shift(shift, pos);
            }
            subres |= subsubres;
        }
        res &= subres;
    }
    X = coords[0];
    Y = coords[1];
    Z = coords[2];
    return res;    
}

bool DEUSArea::intersectArea(DEUSArea area)
{
    int nbShift = this->_periodicity == 0.0f ? 1 : 2;    
    
    bool res = true;
    for(int pos=0; pos<3; pos++) {
        bool subres = false;
        for(int shift=0; shift<nbShift; shift++) {
            for(int shift2=0; shift2<nbShift; shift2++) {
                //std::cout << (this->coords(shift, pos, 0) < area.coords(shift2,pos, 1) && this->coords(shift, pos, 1) > area.coords(shift2,pos, 0)) << " ";
                subres |= this->coords(shift, pos, 0) < area.coords(shift2,pos, 1) && this->coords(shift, pos, 1) > area.coords(shift2,pos, 0);
            }
        }
        //std::cout << "=> " << subres << std::endl;
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

