#pragma once
#include "Main/GameBoy.h"
#include <fstream>
#include <string>
#include <iostream>


class GameBoy;

typedef unsigned char byte;
typedef signed char sbyte;
typedef unsigned short ushort;

class Memory
{
private:
        GameBoy* gb;
        byte* ROM;
        byte* cartridgeBank;
        //{ get { return gb.RAM[0x147]; } }
        byte ROMSize;
        //{ get { return gb.RAM[0x148]; } }
        byte RAMSize;
        //{ get { return gb.RAM[0x149]; } }
        bool isBooting, RAMEnabled, ROMRAMMode;
        byte RAMBank, ROMBank;
        byte** cartridgeData;// = new byte[3, 0x2000];
        byte* RAM;



        void LoadCartridge(std::string path);

public:
        Memory(GameBoy* gb, std::string cartridgeName, byte* RAM);


        byte Read(int addr);


        ushort ReadWord(int addr);


        void Write(int addr, byte value);


        void WriteWord(int addr, ushort value);


        void Switch(ushort addr);

};
