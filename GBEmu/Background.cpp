#include "LCD/Background.h"
#include <exception>

byte Background::TileFromMap(int i, int j)
{
    ushort startAddr;
    if (gb->getBGTileMapDisplaySelect())
        startAddr = 0x9C00;
    else
        startAddr = 0x9800;
    return RAM[startAddr + j * 32 + i];
}

Background::Background(GameBoy* gb, byte* RAM)
{
    this->gb = gb;
    this->RAM = RAM;
}

byte Background::GetPalleteColor(int pixel)
{
    byte x = (byte)((gb->getScrollX() + pixel) % 256),
    y = (byte)((gb->getScrollY() + gb->getYCoordinate()) % 256);
    if (gb->getBGDisplayEnable())
        return gb->PixelColor(TileFromMap(x / 8, y / 8), x % 8, y % 8, gb->getBGWindowTileDataSelect());
    return 0;
}

byte Background::GetPixelColor(int pixel)
{
    return gb->getBGWindowPalette(GetPalleteColor(pixel));
}
