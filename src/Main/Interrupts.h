#pragma once

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
    Interrupts();
    void Sync(int value);
    void Manager();
    bool Drawing();
    bool EnterHALTMode();
    bool EnterSTOPMode();
};
