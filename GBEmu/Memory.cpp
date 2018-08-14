#include "Main/Memory.h"

void Memory::LoadCartridge(std::string path)
{
	std::fstream is;
    is.open("/Users/mikhail/Desktop/C++/GBEmu/GBEmu/ROMs/11-op a,(hl).gb", std::fstream::in);

    long int length = is.tellg();
    is.seekg(0, is.end);
    length = (long int)is.tellg() - length;
    is.seekg(0, is.beg);

    try
    {
        if (length % 0x8000 != 0)
            throw new std::exception();
        is.read((char*)RAM, 0x8000);
        
        if (length == 0x8000)
        {
            is.close();
            return;
        }

        cartridgeData = new byte*[length % 0x8000 - 1];

        // проверить??? 0x8000?
        for (int i = 0; i < length % 0x8000 - 1; i++)
        {
            cartridgeData[i] = new byte[0x8000];
            is.read((char*)cartridgeData[i], 0x8000);
        }
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
    
    LoadCartridge(cartridgeName);
    
    //Clear this item
    //because 0 means all keys down
    RAM[0xFF00] = 0xFF;

    //Switch to ROM bank on start
    //Copys data from BIOS.gb to ROM
    isBooting = true;
    std::fstream fs;
    try
    {
        fs.open("/Users/mikhail/Desktop/C++/GBEmu/GBEmu/Resources/BIOS.bin", std::fstream::in);
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
    int x = RAM[addr];
    
    if (addr >= 0xC192 && addr < 0xC200)
        x = x;
    
    return x;
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
    Write(addr, value & 0xFF);
    Write(addr + 1, value >> 8);
}


void Memory::Switch(ushort addr)
{
    if (isBooting & (addr == 256))
        isBooting = false;
}
