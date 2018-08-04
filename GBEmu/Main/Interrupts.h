#pragma once
#include "/Users/mihail/Desktop/C++/GBEmu/GBEmu/Main/GameBoy.h"

class GameBoy;

typedef unsigned char byte;
typedef signed char sbyte;
typedef unsigned short ushort;

class Interrupts
{
private:
    GameBoy* gb;
    byte* RAM;

    int interruptCounter;
    byte* IE;
    byte* IF;


public:
    Interrupts(GameBoy* gb, byte* RAM);
    void Sync(int value);
    void Manager();
    bool Drawing();
};
