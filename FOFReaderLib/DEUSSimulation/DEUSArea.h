/* ************************** FOFReaderLib ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        FOFReaderLib
// TITLE :          DEUSArea
// DESCRIPTION :    Tools to manage areas
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2014)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           DEUSArea.h
/// \brief          Tools to manage areas
/// \author         Jean Pasdeloup (jean.pasdeloup@obspm.fr)
/// \date           2014
/// \copyright      CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/

#ifndef DEUSAREA_H
#define	DEUSAREA_H

class DEUSArea {
public:
    // Constructors
    DEUSArea();    
    DEUSArea(float minX, float maxX, float minY, float maxY, float minZ, float maxZ, float periodicity = 1.0f);    
    DEUSArea(float X, float Y, float Z, float size, float periodicity = 1.0f);
    DEUSArea(float X, float Y, float Z, float LX, float LY, float LZ, float angle, float length, float periodicity = 1.0f);
    DEUSArea(float *boundaries, float periodicity = 1.0f);
    DEUSArea(const DEUSArea& orig);
    virtual ~DEUSArea();
    
    // Check if particle is inside + modify coords to match periodicity
    bool particuleIsInside(float &X, float &Y, float &Z);
    
    // Check if cube intersect area
    bool intersectArea(DEUSArea area);
    bool cubeIntersect(float *cubeBoundaries);
    
    float coords(int shift, int pos, int minmax) {return _coords[shift][pos][minmax];}
    float shift(int shift, int pos) {return _shift[shift][pos];}
    
    void display();
    
private:   
    void calculateShift();
    void initArea(float periodicity);
    float _coords[2][3][2];
    float _shift[2][3];
    float _periodicity;
};

#endif	/* DEUSAREA_H */

