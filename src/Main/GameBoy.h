#pragma once
#include "CPU.h"
#include "Memory.h"
#include "LCD.h"
#include "Timer.h"
#include "Interrupts.h"
#include "SDL2/SDL.h"
#include <string>
#include <vector>

typedef unsigned char byte;
typedef signed char sbyte;
typedef unsigned short ushort;


class GameBoy
{
private:
    static GameBoy* gb;
    CPU* cpu;
    Memory* memory;
    LCD* lcd;
    Timer* timer;
    Interrupts* ints;
    SDL_Renderer* ren;
    SDL_Texture* texture;
    Uint32* pixels;
    int scale;
    byte* RAM;
    std::vector<Uint32>* colors;

    GameBoy();

public:
    void DrawPixel(int x, int y, int color);
    bool DMATransfer;
    bool IME;
    bool Halt;
    bool Stop;

    static GameBoy* createInstance();
    void initParts();

    ~GameBoy();

    byte* getRAM() {
        return RAM;
    }
    bool getFlag(ushort addr, byte value) { return (RAM[addr] & value) == value ? true : false; }
    void setFlag(ushort addr, byte flag, bool value) { value ? RAM[addr] |= flag : RAM[addr] &= (byte)(~flag); }


    static GameBoy* getInstance();

    bool getLCDDisplayEnable() { return getFlag(0xFF40, 128); }

    bool getWindowTileMapDisplaySelect() { return getFlag(0xFF40, 64); }

    bool getWindowDisplayEnable() { return getFlag(0xFF40, 32); }

    bool getBGWindowTileDataSelect() { return getFlag(0xFF40, 16); }

    bool getBGTileMapDisplaySelect() { return getFlag(0xFF40, 8); }

    bool getSpriteSize() { return getFlag(0xFF40, 4); }

    bool getSpriteDisplayEnable() { return getFlag(0xFF40, 2); }

    bool getBGDisplayEnable() { return getFlag(0xFF40, 1); }




    bool getLYCLYCoincidenceInterrupt() { return getFlag(0xFF41, 64); }
    void setLYCLYCoincidenceInterrupt(bool value) { setFlag(0xFF41, 64, value); }

    bool getOAMInterrupt() { return getFlag(0xFF41, 32); }
    void setOAMInterrupt(bool value) { setFlag(0xFF41, 32, value); }

    bool getVBlankInterrupt() { return getFlag(0xFF41, 16); }
    void setVBlankInterrupt(bool value) { setFlag(0xFF41, 16, value); }

    bool getHBlankInterrupt() { return getFlag(0xFF41, 8); }
    void setHBlankInterrupt(bool value) { setFlag(0xFF41, 8, value); }

    bool getCoincidenceFlag() { return getFlag(0xFF41, 4); }
    void setCoincidenceFlag(bool value) { setFlag(0xFF41, 4, value); }

    byte getMode() { return (byte)(RAM[0xFF41] & 3); }
    void setMode(byte value) { RAM[0xFF41] &= 0xFC; RAM[0xFF41] |= value; }




    byte getScrollY() { return RAM[0xFF42]; }

    byte getScrollX() { return RAM[0xFF43]; }

    byte getYCoordinate() { return RAM[0xFF44]; }
    void setYCoordinate(byte value) { RAM[0xFF44] = value; }

    byte getLYCompare() { return RAM[0xFF45]; }

    byte getBGWindowPalette(byte numberOFColor) { return (byte)((RAM[0xFF47] >> (2 * numberOFColor)) & 0x3); }

    byte getWindowY() { return RAM[0xFF4A]; }

    byte getWindowX() { return (byte)(RAM[0xFF4B] - 7); }


    void LoadCartridge(std::string cartridge);
    void Run();
    void SyncCycles(int count);
    void Sync();
    byte PixelColor(byte ID, int xOffset, int yOffset, bool bank);
    void DrawLine();
    void Write(int addr, byte value);
    byte Read(int addr);
    ushort ReadWord(int addr);
    void WriteWord(int addr, ushort value);
    void Switch(ushort addr);
    void Interrupt(ushort addr);
    void FindSprites();
    void Clock();
    bool Drawing();
    void Manager();
    void KeyDown(SDL_Event e);
    void KeyUp();
};
