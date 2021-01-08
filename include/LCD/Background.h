#pragma once
#include "Main/LCD.h"

class GameBoy;

typedef unsigned char byte;
typedef signed char sbyte;
typedef unsigned short ushort;

class Background
{
private:
    GameBoy* gb;
    byte* RAM;

public:
    Background();
    byte TileFromMap(int i, int j);
    byte GetPalleteColor(int pixel);
};
