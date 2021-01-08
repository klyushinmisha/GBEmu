#pragma once

class GameBoy;

typedef unsigned char byte;
typedef signed char sbyte;
typedef unsigned short ushort;

class Timer
{
private:
    //Increase by 4, because simplieest step
    //takes 4 machine cycles
    //Used to increase DIV register
    byte systemCounter;

    //Increase by 4, because simplieest step
    //takes 4 machine cycles
    //Used to increase TIMA register
    int internalCounter;
    
    byte* RAM;

    //checks is timer enabled or not
    bool enabled;

    //contains count of cycles
    //that GB needs to increase TIMA register
    int frequency;

public:
    Timer();

    //Overloaded increment operator
    //Used for 
    void Inc();
};
