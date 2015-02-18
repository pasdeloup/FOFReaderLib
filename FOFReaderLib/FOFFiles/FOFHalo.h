/* ************************** FOFReaderLib ********************************** */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        FOFReaderLib
// TITLE :          FOFHalo
// DESCRIPTION :    Halo simple value object
// AUTHOR(S) :      Jean Pasdeloup (jean.pasdeloup@obspm.fr)
// CONTRIBUTIONS :  [Jean Pasdeloup (2013)]
// LICENSE :        CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           FOFHalo.h
/// \brief          Halo simple value object
/// \author         Jean Pasdeloup (jean.pasdeloup@obspm.fr)
/// \date           2013
/// \copyright      CECILL-B License
/*////////////////////////////////////////////////////////////////////////////*/

#ifndef FOFHALO_H
#define	FOFHALO_H

class FOFHalo {
public:
    FOFHalo();
    FOFHalo(long long id, float x, float y, float z, int mass): _id(id), _x(x), _y(y), _z(z), _mass(mass) {}
    FOFHalo(const FOFHalo& orig);
    virtual ~FOFHalo();
    long long id() {return _id;}    
    float x() {return _x;}
    float y() {return _y;}
    float z() {return _z;}
    int mass() {return _mass;}
    
private:
    long long _id;
    float _x;
    float _y;
    float _z;
    int  _mass;
};

#endif	/* FOFHALO_H */

