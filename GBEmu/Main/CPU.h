#pragma once
#include "Main/GameBoy.h"
#include "CPU/ALU.h"
#include <exception>

typedef unsigned char byte;
typedef signed char sbyte;
typedef unsigned short ushort;

class ALU;

class CPU : ALU
{
public:
    CPU(GameBoy* gb) : ALU(gb) {}
    
    void Clock();

    //Used by interrupts to save previous Program Counter
    //and jump to it's start address
    void Interrupt(ushort addr);


protected:
    void DI();
    void EI();

};
