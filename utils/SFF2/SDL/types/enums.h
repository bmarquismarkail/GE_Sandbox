#ifndef ENUMS_H_INCLUDED
#define ENUMS_H_INCLUDED

enum UPD_FLAG
{
    SFF_NOUPDATE = 0,
    SFF_UPDATEPAL,
    SFF_UPDATESPR,
    SFF_UPDATEPALANDSPRITE
};

inline UPD_FLAG operator|(UPD_FLAG a, UPD_FLAG b)
{return static_cast<UPD_FLAG>(static_cast<int>(a) | static_cast<int>(b));}
#endif // ENUMS_H_INCLUDED
