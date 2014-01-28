/* ****************************** FORTRANFILE ******************************* */
/*////////////////////////////////////////////////////////////////////////////*/
// PROJECT :        FURRAY
// TITLE :          FortranFile
// DESCRIPTION :    Reading and managing fortran files in C++
// AUTHOR(S) :      Vincent Reverdy (vince.rev@gmail.com)
// LICENSE :        CeCILL-B
// MODIFICATIONS :  [Vincent Reverdy (2012)]
/*////////////////////////////////////////////////////////////////////////////*/
/// \file           fortranfile.h
/// \brief          Reading and managing fortran files in C++
/// \author         Vincent Reverdy (vince.rev@gmail.com)
/// \date           2012 
/// \remark         CeCILL-B
/*////////////////////////////////////////////////////////////////////////////*/
#ifndef FORTRANFILE_H_INCLUDED
#define FORTRANFILE_H_INCLUDED
/*////////////////////////////////////////////////////////////////////////////*/



// ------------------------------ PREPROCESSOR ------------------------------ //
// Include C++
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
// Include libs
// Include project
// Namespace
// -------------------------------------------------------------------------- //



// ---------------------------------- CLASS --------------------------------- //
// Reading and managing fortran files in C++
/// \brief          Reading and managing fortran files in C++
/// \param[in]      TM Fortran marker type (unsigned int or unsigned long long int)
template<class TM> class FortranFile
{
    // Lifecycle
    public:
        FortranFile();
        ~FortranFile();
    
    // Getters and setters
    public:
        inline std::string name() const;
        inline bool systemEndianness() const;
        inline bool endianness() const;
        inline void setEndianness(const bool big = false);
        inline bool exceptionHandling() const;
        inline void setExceptionHandling(const bool ok = true);
        inline bool swapping() const;
        inline bool setSwapping(const bool ok = true);
        inline unsigned int markerSize() const;
    
    // Stream
    public:
        inline std::ifstream* readStream();
        inline std::ofstream* writeStream();
        inline bool openRead(const std::string &path);
        inline bool openWrite(const std::string &path);
        inline void close();
        
    // Read
    public:
        template<class T> bool read(T &x);
        template<class T> bool readArray(T *&x, unsigned int &length);
        template<class T> bool readVector(std::vector<T> &x, bool extend = false);
        template<class T> bool readIgnore(unsigned int &length);
        inline bool readIgnore();

    // Write
    public:
        template<class T> bool write(T x);
        template<class T> bool writeArray(T *x, const unsigned int length);
        template<class T> bool writeVector(std::vector<T> &x);
    
    // Misc
    public:
        template<class T> void swap(T *x, const unsigned int length = 1);        
    protected:
        inline bool detectSystemEndianness();        
        virtual void throwException();
    
    // Data members
    protected:                
        std::string _name;                                                      ///< Name of the currently opened file
        std::ifstream _readStream;                                              ///< File read stream
        std::ofstream _writeStream;                                             ///< File write stream
        bool _systemEndianness;                                                 ///< System endianness : false if little-endian, true if big-endian
        bool _endianness;                                                       ///< Stream endianness : false if little-endian, true if big-endian
        bool _exceptionHandling;                                                ///< Exception handling
        bool _swap;                                                             ///< Swap bytes if endianness differ
        TM _marker;                                                             ///< Fortran record marker  
};
// -------------------------------------------------------------------------- //



// -------------------------------- LIFECYCLE ------------------------------- //
// Default constructor
/// \brief          Default constructor
template<class TM> FortranFile<TM>::FortranFile() 
{
    _marker = 0;
    _systemEndianness = detectSystemEndianness();
    setEndianness(_systemEndianness);
    _exceptionHandling = true;
}

// Default destructor, close all opened streams
/// \brief          Default destructor, close stream if opened
template<class TM> FortranFile<TM>::~FortranFile() 
{
    close();
}
// -------------------------------------------------------------------------- //



// --------------------------- GETTERS AND SETTERS -------------------------- //
// Get the file name of the opened stream
/// \brief          Get the file name of the opened stream
/// \return         String of the file name
template<class TM> inline std::string FortranFile<TM>::name() const
{
    return _name;
}

// System endianness getter
/// \brief          System endianness getter
/// \return         False if little-endian, true if big-endian
template<class TM> inline bool FortranFile<TM>::systemEndianness() const
{
    return _systemEndianness;
}

// Stream endianness getter
/// \brief          Stream endianness getter
/// \return         False if little-endian, true if big-endian
template<class TM> inline bool FortranFile<TM>::endianness() const
{
    return _endianness;
}

// Stream endianness setter
/// \brief          Stream endianness setter
/// \param[in]      big False if little-endian, true if big-endian
template<class TM> inline void FortranFile<TM>::setEndianness(const bool big)
{
    _endianness = big;
    _swap = (_endianness != _systemEndianness);
}

// Exception handling getter
/// \brief          Exception handling getter
/// \return         True if exception handling is activated
template<class TM> inline bool FortranFile<TM>::exceptionHandling() const
{
    return _exceptionHandling;
}

// Exception handling setter
/// \brief          Exception handling setter
/// \param[in]      ok True to activate exception handling
template<class TM> inline void FortranFile<TM>::setExceptionHandling(const bool ok)
{
    _exceptionHandling = ok;
}

// Swap getter
/// \brief          Swap getter
/// \return         True if system and stream endiannesses are not the same
template<class TM> inline bool FortranFile<TM>::swapping() const
{
    return _swap;
}

// Swap setter
/// \brief          Swap setter
/// \param[in]      ok True to activate byte swapping for endianness
/// \return         Swap variable
template<class TM> inline bool FortranFile<TM>::setSwapping(const bool ok)
{
    _swap = ok;
    _endianness = (_systemEndianness != _swap);
    return _swap;
}

// Marker size getter
/// \brief          Marker size getter
/// \return         Size of marker in bytes
template<class TM> inline unsigned int FortranFile<TM>::markerSize() const
{
    return sizeof(TM);
}
// -------------------------------------------------------------------------- //



// --------------------------------- STREAM --------------------------------- //
// Get the read stream
/// \brief          Get the read stream
/// \return         Pointer to the read stream
template<class TM> inline std::ifstream* FortranFile<TM>::readStream()
{
    return ((_writeStream.is_open()) ? (NULL) : (&_readStream));
}

// Get the write stream
/// \brief          Get the write stream
/// \return         Pointer to the write stream
template<class TM> inline std::ofstream* FortranFile<TM>::writeStream()
{   
    return ((_readStream.is_open()) ? (NULL) : (&_writeStream));
}

// Open a binary fortran file for reading
/// \brief          Open a binary fortran file for reading
/// \param[in]      path Path to the file
/// \return         True if file sucessfully open
template<class TM> inline bool FortranFile<TM>::openRead(const std::string &path) 
{
    bool ok = true;
    close(); 
    _name = path;
    _readStream.open(_name.c_str(), std::ios::binary); 
    if (!(ok =_readStream.good())) close();
    return ok;
}

// Open a binary fortran file for writing
/// \brief          Open a binary fortran file for writing
/// \param[in]      path Path to the file
/// \return         True if file sucessfully open
template<class TM> inline bool FortranFile<TM>::openWrite(const std::string &path)
{
    bool ok = true;
    close();
    _name = path;
    _writeStream.open(_name.c_str(), std::ios::binary);
    if (!(ok =_readStream.good())) close();
    return ok;
}

// Close opened streams
/// \brief          Close opened streams
template<class TM> inline void FortranFile<TM>::close() 
{
    _name.clear();
    if (_readStream.is_open()) {
        _readStream.close();
        _readStream.clear();
    }
    if (_writeStream.is_open()) {
        _writeStream.close();
        _writeStream.clear();
    }
}
// -------------------------------------------------------------------------- //



// ---------------------------------- READ ---------------------------------- //  
// Read a value from a binary fortran file
/// \brief          Read a value from a binary fortran file
/// \param[out]     x Value to be read
/// \return         Value sucessfully read
template<class TM> template<class T> bool FortranFile<TM>::read(T &x)
{
    // Initialize
    bool ok = false;
    
    // Read
    if (_readStream.good()) {
        _readStream.read(reinterpret_cast<char*>(&_marker), sizeof(TM));
        if (_swap) swap(&_marker);
        if (_marker == sizeof(T)) {
            _readStream.read(reinterpret_cast<char*>(&x), sizeof(T));
            if (_swap) swap(&x);
            _readStream.read((reinterpret_cast<char*>(&_marker)), sizeof(TM));
            if (_swap) swap(&_marker);
            ok = ((_marker == sizeof(T)) && (_readStream.good()));
        }
    }
    
    // Finalize
    if (!ok) x = 0;
    if ((_exceptionHandling) && (!ok)) throwException();
    return ok;
}

// Read an array from a binary fortran file
/// \brief          Read an array from a binary fortran file
/// \param[out]     x Array to be filled
/// \param[out]     length Size of x after reading
/// \return         Array sucessfully read
template<class TM> template<class T> bool FortranFile<TM>::readArray(T *&x, unsigned int &length)
{
    // Initialize
    bool ok = false;
    if (x) delete[] x;
    x = NULL;
    length = 0;
    
    // Read
    if (_readStream.good()) {
        _readStream.read(reinterpret_cast<char*>(&_marker), sizeof(TM));
        if (_swap) swap(&_marker);
        if (_marker%sizeof(T) == 0) {
            length = _marker/sizeof(T);
            if (length > 0) {
                x = new T[length];
                _readStream.read(reinterpret_cast<char*>(x), length*sizeof(T));
                if (_swap) swap(x, length);
            }
            _readStream.read((reinterpret_cast<char*>(&_marker)), sizeof(TM));
            if (_swap) swap(&_marker);
            if (!(ok = ((_marker/sizeof(T) == length) && _readStream.good()))) {
                if (x) delete[] x;
                x = NULL;
                length = 0;
            }
        }
    }

    // Finalize
    if ((_exceptionHandling) && (!ok)) throwException();
    return ok;
}

// Read a vector from a binary fortran file
/// \brief          Read a vector from a binary fortran file
/// \param[out]     x Vector to be filled
/// \param[in]      extend True if content is added at the end of the vector
/// \return         Vector sucessfully read
template<class TM> template<class T> bool FortranFile<TM>::readVector(std::vector<T> &x, bool extend)
{
    // Initialize
    bool ok = false;
    unsigned int length = 0;
    const unsigned int xsize = ((extend) ? (x.size()) : (0));
    extend = ((extend) && (xsize > 0));
    if (!extend) x.clear();
    
    // Read
    if (_readStream.good()) {
        _readStream.read(reinterpret_cast<char*>(&_marker), sizeof(TM));
        if (_swap) swap(&_marker);
        if (_marker%sizeof(T) == 0) {
            length = _marker/sizeof(T);
            if (length > 0) {
                if (extend) x.insert(x.end(), length, 0);
                else x.resize(length);
                _readStream.read(reinterpret_cast<char*>(&x[xsize]), length*sizeof(T));
                if (_swap) swap(&x[xsize], length);
            }
            _readStream.read((reinterpret_cast<char*>(&_marker)), sizeof(TM));
            if (_swap) swap(&_marker);
            ok = ((_marker/sizeof(T) == length) && _readStream.good());
            if ((!ok) && (length > 0)) {
                if (extend) x.erase(x.begin()+xsize, x.end());
                else x.clear();
            }
        }
    }
    
    // Finalize
    if ((_exceptionHandling) && (!ok)) throwException();
    return ok;
}

// Read the file and ignore the content
/// \brief          Read the file and ignore the content
/// \param[out]     length Size of read content
/// \return         Content successfully ignored
template<class TM> template<class T> bool FortranFile<TM>::readIgnore(unsigned int &length)
{
    // Initialize
    bool ok = false;
    length = 0;
    
    // Read
    if (_readStream.good()) {
        _readStream.read(reinterpret_cast<char*>(&_marker), sizeof(TM));
        if (_swap) swap(&_marker);
        if (_marker%sizeof(T) == 0) {
            length = _marker/sizeof(T); 
            if (length > 0) _readStream.seekg(_marker, std::ios::cur);
            _readStream.read((reinterpret_cast<char*>(&_marker)), sizeof(TM));
            if (_swap) swap(&_marker);
            if (!(ok = ((_marker/sizeof(T) == length) && _readStream.good()))) length = 0;
        }
    }
    
    // Finalize
    if ((_exceptionHandling) && (!ok)) throwException();
    return ok;
}

// Read the file and ignore the content
/// \brief          Read the file and ignore the content
/// \return         Content successfully ignored
template<class TM> inline bool FortranFile<TM>::readIgnore()
{
    unsigned int length = 0;
    return (readIgnore<char>(length));
}
// -------------------------------------------------------------------------- //



// --------------------------------- WRITE ---------------------------------- //
// Write a value to a binary fortran file
/// \brief          Write a value to a binary fortran file
/// \param[in]      x Value
/// \return         Value sucessfully written
template<class TM> template<class T> bool FortranFile<TM>::write(T x)
{
    // Initialize
    bool ok = false;
    
    // Write
    if (_writeStream.good()) {
        _marker = sizeof(T);
        if (_swap) swap(&_marker);
        _writeStream.write(reinterpret_cast<char*>(&_marker), sizeof(TM));
        if (_swap) swap(&x);
        _writeStream.write(reinterpret_cast<char*>(&x), sizeof(T));
        if (_swap) swap(&x);
        _writeStream.write(reinterpret_cast<char*>(&_marker), sizeof(TM));
        if (_swap) swap(&_marker);
        ok = _writeStream.good();
    }
    
    // Finalize
    if ((_exceptionHandling) && (!ok)) throwException();
    return ok;
}

// Write an array to a binary fortran file
/// \brief          Write an array to a binary fortran file
/// \param[in]      x Array
/// \param[in]      length Size of x
/// \return         Array sucessfully written
template<class TM> template<class T> bool FortranFile<TM>::writeArray(T *x, const unsigned int length)
{
    // Initialize
    bool ok = false;
    
    // Write
    if (_writeStream.good()) {
        _marker = sizeof(T)*length;
        if (_swap) swap(&_marker);
        _writeStream.write(reinterpret_cast<char*>(&_marker), sizeof(TM));
        if (length > 0) {
            if (_swap) swap(x, length);
            _writeStream.write(reinterpret_cast<char*>(x), length*sizeof(T));
            if (_swap) swap(x, length);
        }
        _writeStream.write(reinterpret_cast<char*>(&_marker), sizeof(TM));
        if (_swap) swap(&_marker);
        ok = _writeStream.good();
    }
    
    // Finalize
    if ((_exceptionHandling) && (!ok)) throwException();
    return ok;
}

// Write a vector to a binary fortran file
/// \brief          Write a vector to a binary fortran file
/// \param[in]      x Vector
/// \return         Vector sucessfully written
template<class TM> template<class T> bool FortranFile<TM>::writeVector(std::vector<T> &x)
{
    // Initialize
    bool ok = false;
    const unsigned int xsize = x.size();
    
    // Write
    if (_writeStream.good()) {
        _marker = sizeof(T)*xsize;
        if (_swap) swap(&_marker);
        _writeStream.write(reinterpret_cast<char*>(&_marker), sizeof(TM));
        if (xsize > 0) {
            if (_swap) swap(&x[0], xsize);
            _writeStream.write(reinterpret_cast<char*>(&x[0]), xsize*sizeof(T));
            if (_swap) swap(&x[0], xsize);
        }
        _writeStream.write(reinterpret_cast<char*>(&_marker), sizeof(TM));
        if (_swap) swap(&_marker);
        ok = _writeStream.good();
    }
    
    // Finalize
    if ((_exceptionHandling) && (!ok)) throwException();
    return ok;
}
// -------------------------------------------------------------------------- //



// ---------------------------------- MISC ---------------------------------- //
// Detect system endianness
/// \brief          Detect system endianness
/// \return         False if little-endian, true if big-endian
template<class TM> inline bool FortranFile<TM>::detectSystemEndianness()
{
    int i = 1;
    char *c = reinterpret_cast<char*>(&i);
    return (c[0] != i);
}

// Swap bytes for endianness purposes
/// \brief          Swap bytes for endianness purposes
/// \param[in]      x Array of data
/// \param[in]      length Size of x
template<class TM> template<class T> void FortranFile<TM>::swap(T *x, const unsigned int length)
{
    // Variables
    const unsigned int typesize = sizeof(T);
    const unsigned int half = sizeof(T)/2;
    char *c = reinterpret_cast<char*>(x);
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int begin = 0;
    unsigned int end = 0;
    char tmp = 0;
    
    // Swap
    if ((x) && (length > 0)) {
        for (i = 0; i < length; ++i) {
            begin = i*typesize;
            end = begin+(typesize-1);
            for (j = 0; j < half; ++j) {
                tmp = c[begin+j];
                c[begin+j] = c[end-j];
                c[end-j] = tmp;
            }
        }
    }
}

// Throw exception if error during input or output
/// \brief          Throw exception if error during input or output
template<class TM> void FortranFile<TM>::throwException()
{
    throw std::ios_base::failure("ERROR : FortranFile<TM>::throwException()");
}
// -------------------------------------------------------------------------- //



/*////////////////////////////////////////////////////////////////////////////*/
#endif // FORTRANFILE_H_INCLUDED
/*////////////////////////////////////////////////////////////////////////////*/