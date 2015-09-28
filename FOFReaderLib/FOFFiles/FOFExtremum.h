/* ************************** FOFReaderLib ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        FOFReaderLib
// TITLE :          FOFExtremim
// DESCRIPTION :    Extremum simple value object
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2015)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           FOFExtremum.h
/// \brief          Extremum simple value object
/// \author         Jean Pasdeloup (jean.pasdeloup@obspm.fr)
/// \date           2015
/// \copyright      CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/

#ifndef FOFEXTREMUM_H
#define	FOFEXTREMUM_H

class FOFExtremum {
public:
    FOFExtremum();
    FOFExtremum(float x, float y, float z, float density, float minSeuil, float avgSeuil): _x(x), _y(y), _z(z), _density(density), _minSeuil(minSeuil), _avgSeuil(avgSeuil) {}
    FOFExtremum(const FOFExtremum& orig) {}
    virtual ~FOFExtremum() {}    
    float x() {return _x;}
    float y() {return _y;}
    float z() {return _z;}
    float density() {return _density;}
    float minSeuil() {return _minSeuil;}
    float avgSeuil() {return _avgSeuil;}
private:    
    float _x;
    float _y;
    float _z;
    float _density;
    float _minSeuil;
    float _avgSeuil;
};

#endif	/* FOFEXTREMUM_H */

