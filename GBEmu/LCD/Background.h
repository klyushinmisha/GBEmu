#pragma once
#include "Main/LCD.h"
#include "Main/GameBoy.h"

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
    Background(GameBoy* gb, byte* RAM);
    byte TileFromMap(int i, int j);
    byte GetPalleteColor(int pixel);
};
