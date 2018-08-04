#include "Main/Memory.h"

void Memory::LoadCartridge(std::string path)
{
	std::fstream is;
    is.open("/Users/mihail/Desktop/C++/GBEmu/GBEmu/ROMs/Tetris.gb", std::fstream::in);

    /*int length = is.tellg();
    is.seekg(0, is.end);
    length = (int)is.tellg() - length;
    is.seekg(0, is.beg);*/

    try
    {
        /*std::cout << length << std::endl;
        if (length % 0x8000 != 0)
            throw new std::exception();*/
        is.read((char*)RAM, 0x8000);
        
        /*if (length == 0x8000)
         {*/
        is.close();
        return;
        //}

        //cartridgeData = new byte*[length % 0x8000 - 1];

        /*for (int i = 0; i < length % 0x8000 - 1; i++)
        {
            cartridgeData[i] = new byte[0x8000];
            for (int j = 0; j < 0x8000; j++)
                is >> cartridgeData[i][j];
        }*/
    }
    catch (std::exception e)
    {
        std::cout << "Incorrect format" << std::endl;
    }

    
    is.close();
}

Memory::Memory(GameBoy* gb, std::string cartridgeName, byte* RAM)
{
    //Init all components
    this->gb = gb;
    this->RAM = RAM;
    RAMBank = 0;

    std::cout << "beg" << std::endl;
    LoadCartridge(cartridgeName);

    std::cout << "end" << std::endl;
    
    //Clear this item
    //because 0 means all keys down
    RAM[0xFF00] = 0xFF;

    //Switch to ROM bank on start
    //Copys data from BIOS.gb to ROM
    isBooting = true;
    std::fstream fs;
    try
    {
        std::cout << "not opened" << std::endl;
        fs.open("/Users/mihail/Desktop/C++/GBEmu/GBEmu/Resources/BIOS.bin", std::fstream::in);
        std::cout << "opened" << std::endl;
        char* tmpR = new char[256];
        fs.read(tmpR, 256);
        ROM = (byte*)tmpR;
    }
    catch (std::exception e)
    {
        std::cout << "Can't find BIOS.gb" << std::endl;
    }
    
}


byte Memory::Read(int addr)
{
    gb->Sync();

    //Reads from ROM
    if (isBooting & (addr < 256))
    {
        return ROM[addr];
    }

    //Reads from external RAM
    if ((addr > 0x9FFF) & (addr < 0xBFFF) & (RAMBank != 0))
        return cartridgeData[RAMBank - 1][addr - 0x8000];

    //Reads from RAM
    return RAM[addr];
}


ushort Memory::ReadWord(int addr)
{
    ushort temp;
    temp = Read(addr + 1);
    temp <<= 8;
    temp |= Read(addr);
    return temp;
}



void Memory::Write(int addr, byte value)
{
    gb->Sync();

    if (addr < 0x8000)
        return;
    //    CheckMBC(addr, value);

    //Checks writing to special registers
    //which have unusual behaviour
    switch (addr)
    {
        case 0xFF00:
            //INPUT
            RAM[0xFF00] &= 0b11001111;
            RAM[0xFF00] |= (byte)(value & 0b110000);
            return;

        case 0xFF04:
            //DIV
            RAM[0xFF04] = 0;
            return;

        case 0xFF41:
            //STAT
            value &= 0b11111000;
            RAM[0xFF41] &= 7;
            RAM[0xFF41] |= value;
            return;

        case 0xFF44:
            //LYCounter
            RAM[0xFF44] = 0;
            return;

        case 0xFF46:
            gb->DMATransfer = true;
            break;
    }

    //This space copys value to C000-DE00
    if ((addr >= 0xE000) & (addr < 0xFE00))
    {
        RAM[addr] = value;
        addr -= 0x2000;
    }

    //Writing to external RAM
    if ((addr > 0x9FFF) & (addr < 0xBFFF) & (RAMBank != 0))
        cartridgeData[RAMBank - 1][addr - 0x8000] = value;
    else if (addr > 0x7FFF)
        RAM[addr] = value;

}


void Memory::WriteWord(int addr, ushort value)
{
    Write(addr, (byte)(value & 0xFF));
    Write(addr + 1, (byte)(value >> 8));
}


void Memory::Switch(ushort addr)
{
    if (isBooting & (addr == 256))
        isBooting = false;
}
