#include "Main/LCD.h"
#include <exception>
#include "Main/GameBoy.h"

byte LCD::GetPixel(int pixel)
{
    //if (!gb->getLCDDisplayEnable())
        //return 0;
/* 
    if (gb->SpriteDisplayEnable)
    {
        foreach (byte id in sID)
        {
            s.Index = id;
            if (s.X <= pixel & s.X + 8 > pixel & s.IsNotTransparent(pixel) & IsPrevailing(s, pixel))
                return s.GetPixelColor(pixel);
        }
    } 
*/

    //if (gb->WindowDisplayEnable & pixel >= gb->WindowX & gb->YCoordinate >= gb->WindowY)
     //   return window.GetPixelColor(pixel);
    //else
        return gb->getBGWindowPalette(background->GetPalleteColor(pixel));
}

/*bool LCD::IsInArea()
{
    int side = gb->getSpriteSize() ? 16 : 8;
    return s.X >= 0 & s.X + 8 < 160 & s.Y <= gb->getYCoordinate() & s.Y + side > gb->getYCoordinate();
}*/

byte LCD::GetColor(ushort startAddr, int xOffset, int yOffset)
{
    byte half1 = (RAM[startAddr] >> (7 - xOffset)) & 1;
    byte half2 = (RAM[startAddr + 1] >> (7 - xOffset)) & 1;
    byte value = (half2 << 1) + half1;
    return value;
}


LCD::LCD()
{
    this->gb = GameBoy::getInstance();
    this->RAM = gb->getRAM();
    background = new Background();
    //s = new Sprite(gb);
    //window = new Window(gb);
    //sID = new byte[10];
}

void LCD::DrawLine()
{
    for (int pixel = 0; pixel < 160; pixel++)
        gb->DrawPixel(pixel, gb->getYCoordinate(), GetPixel(pixel));
    gb->setYCoordinate(gb->getYCoordinate() + 1);
}

/*void LCD::FindSprites()
{
    for (byte i = 0, j = 0; i < 40 & j < 10; i++)
    {
        s.Index = i;
        if (IsInArea())
            sID[j++] = i;
    }
}*/

byte LCD::PixelColor(byte ID, int xOffset, int yOffset, bool bank)
{
    ushort startAddr;
    if (bank)
        startAddr = (ushort)(0x8000 + ID * 16);
    else
    {
        char* sb = (char*)&ID;
        startAddr = (ushort)(0x9000 + *sb * 16);
    }
    
    startAddr += (ushort)(yOffset * 2);

    return GetColor(startAddr, xOffset, yOffset);
}

/*bool LCD::IsPrevailing(Sprite s, int pixel)
{
    if (!gb->BGDisplayEnable)// & !gb->WindowDisplayEnable)
        return true;
    if (!s.Priority)
        return true;
    else if (s.Priority & background.GetPalleteColor(pixel) == 0)// & window.GetPalleteColor(pixel) == 0)
        return true;
    return false;
}*/
