#pragma once
#include "Main/GameBoy.h"
#include "LCD/Background.h"

class GameBoy;
class Background;

typedef unsigned char byte;
typedef signed char sbyte;
typedef unsigned short ushort;

class LCD
{
private:
    GameBoy* gb;
    Background* background;
    byte* RAM;
    //Window* window;
    //Sprite* s;
    //byte* sID;

    
      

    byte GetPixel(int pixel);
    bool IsInArea();
    byte GetColor(ushort startAddr, int xOffset, int yOffset);


public:
    LCD(GameBoy* gb, byte* RAM);
    void DrawLine();
    //void FindSprites();
    byte PixelColor(byte ID, int xOffset, int yOffset, bool bank);
    //bool IsPrevailing(Sprite s, int pixel);
};
