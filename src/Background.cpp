#include "LCD/Background.h"
#include <exception>
#include "Main/GameBoy.h"

byte Background::TileFromMap(int x, int y)
{
    ushort startAddr;
    if (gb->getBGTileMapDisplaySelect())
        startAddr = 0x9C00;
    else
        startAddr = 0x9800;
    return RAM[startAddr + y * 32 + x];
}

Background::Background()
{
    this->gb = GameBoy::getInstance();
    this->RAM = gb->getRAM();
}

byte Background::GetPalleteColor(int pixel)
{
    byte x = (gb->getScrollX() + pixel) % 256;
    byte y = (gb->getScrollY() + gb->getYCoordinate()) % 256;
    if (gb->getBGDisplayEnable())
        return gb->PixelColor(TileFromMap(x / 8, y / 8), x % 8, y % 8, gb->getBGWindowTileDataSelect());
    return 0;
}
