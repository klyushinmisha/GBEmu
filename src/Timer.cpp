#include "Main/Timer.h"
#include "Main/GameBoy.h"

Timer::Timer()
{
    systemCounter = 0;
    internalCounter = 0;
    this->RAM = GameBoy::getInstance()->getRAM();
}

//Overloaded increment operator
//Used for 
void Timer::Inc()
{
    //Syncronization of DIV register
    systemCounter += 4;
    if (systemCounter == 0)
        //DIV
        RAM[0xFF04]++;
   
    //Checks timer (enabled or not)
    enabled = (RAM[0xFF07] & 4) == 4;

    //Sets timer frequency
    switch (RAM[0xFF07] & 3)
    {
        case 0:
            frequency = 1024;
            break;
        case 1:
            frequency = 16;
            break;
        case 2:
            frequency = 64;
            break;
        case 4:
            frequency = 256;
            break;
    }

    if (enabled) {
        //Syncronization of TIMA register
        internalCounter += 4;
        if (internalCounter == frequency) {
            //TIMA
            RAM[0xFF05]++;
            //Checks TIMA overflow
            if (RAM[0xFF05] == 0)
            {
                //copy TMA to TIMA
                RAM[0xFF05] = RAM[0xFF06];
                RAM[0xFF0F] |= 4;
            }
        }
        internalCounter = internalCounter % frequency;
    }

}
