#include "Main/GameBoy.h"
#include "SDL2/SDL.h"
#include <exception>

sbyte GameBoy::ToSByte(byte value)
{
    sbyte sb;
    if (value == 128)
        return -128;
    if ((value & 0x80) == 0x80)
    {
        value--;
        value = (byte)(~value);
        sb = (sbyte)(-value);
    }
    else
        sb = (sbyte)value;
    return sb;
}

void GameBoy::Link(std::string cartridgeName)
{
    DMATransfer = false;
    IME = true;
    Halt = false;
    Stop = false;
	LCDBuffer = new byte*[144];
    for (int i = 0; i < 144; i++)
        LCDBuffer[i] = new byte[160];
    RAM = new byte[0x10000];
    this->memory = new Memory(this, cartridgeName, RAM);
    this->cpu = new CPU(this);
    this->lcd = new LCD(this, RAM);
    this->timer = new Timer(RAM);
    this->ints = new Interrupts(this, RAM);
    setMode(2);
    setOAMInterrupt(true);
}

/*void GameBoy_Closing(object sender, System.ComponentModel.CancelEventArgs e)
{
    Application.Exit();
}*/

/*
    Это хэндлер для пользовательского ввода (событие отпускания клавиши)
*/

/*void GameBoy_KeyUp(object sender, KeyboardKeyEventArgs e)
{
    RAM[0xFF00] &= 0xF0;
    RAM[0xFF00] |= 0xF;
}*/

/*
    Основная часть эмулятора
    Запускает цикл:
        -отрисовка изображения контроллером
        -обработка комманд процессором
*/

void GameBoy::Run()
{

    static const byte colors[4][3] = { { 196, 207, 161 }, { 139, 149, 109 }, { 107, 115, 83 }, { 65, 65, 65 } };
    SDL_Init(SDL_INIT_EVERYTHING);

    int scale = 3;
    SDL_Window* w = SDL_CreateWindow("Window", 100, 100, 160*scale, 144*scale, 0);

    SDL_Event* e = nullptr;
    SDL_Renderer* ren = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED);
    SDL_Rect* r = new SDL_Rect();

    
    r->w = scale;
    r->h = scale;
    SDL_ShowWindow(w);
    SDL_RenderClear(ren);
    int c;
    while (true)
    {
        if (Drawing())
            Manager();
        else
        {
            for (int i = 0; i < 144; i++)
                for (int j = 0; j < 160; j++)
                {
                    c = LCDBuffer[i][j];
                    SDL_SetRenderDrawColor(ren, colors[c][0], colors[c][1], colors[c][2], 255);
                    r->x = j*scale;
                    r->y = i*scale;
                    SDL_RenderFillRect(ren, r);
                    
                }
            SDL_PollEvent(e);
            if (SDL_HasEvent(SDL_QUIT))
                break;
            SDL_RenderPresent(ren);
        }
    }

    delete r;

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(w);
    SDL_Quit();
}

/*
    Связка всех классов между собой
    Лучше будет реализовать через отдельный класс
*/

/*
    Это хэндлер для пользовательского ввода (событие нажатия клавиши)
*/

/*void GameBoy_KeyDown(object sender, KeyboardKeyEventArgs e)
{
    byte key = 0;

    if (((RAM[0xFF00] >> 4) & 3) == 3 | ((RAM[0xFF00] >> 4) & 3) == 0)
        return;

    if (RAM[0xFF00] >> 4 == 0b1101)
        switch (e.Key)
        {
            case Key.Number1:
                key = 0b111;
                break;
            case Key.Number2:
                key = 0b1011;
                break;
            case Key.K:
                key = 0b1101;
                break;
            case Key.L:
                key = 0b1110;
                break;
            default:
                return;
        }
    else if (RAM[0xFF00] >> 4 == 0b1110)
        switch (e.Key)
        {
            case Key.W:
                key = 0b1011;
                break;
            case Key.A:
                key = 0b1101;
                break;
            case Key.S:
                key = 0b111;
                break;
            case Key.D:
                key = 0b1110;
                break;
            default:
                return;
        }

    RAM[0xFF0F] |= 0b10000;
    RAM[0xFF00] &= 0xF0;
    RAM[0xFF00] |= key;
    Stop = false;
}*/

GameBoy::~GameBoy()
{

    delete[] RAM;


    for (int i = 0; i < 144; i++)
        delete[] LCDBuffer[i];
    delete[] LCDBuffer;


    std::cout << "buf!" << std::endl;
}

void GameBoy::SyncCycles(int count)
{
    ints->Sync(count);
}

void GameBoy::Sync()
{
    SyncCycles(4);
    timer++;
}

byte GameBoy::PixelColor(byte ID, int xOffset, int yOffset, bool bank)
{
    return lcd->PixelColor(ID, xOffset, yOffset, bank);
}

void GameBoy::DrawLine()
{
    lcd->DrawLine();
}

void GameBoy::Write(int addr, byte value)
{
    memory->Write(addr, value);
}

byte GameBoy::Read(int addr)
{
    return memory->Read(addr);
}

ushort GameBoy::ReadWord(int addr)
{
    return memory->ReadWord(addr);
}

void GameBoy::WriteWord(int addr, ushort value)
{
    memory->WriteWord(addr, value);
}

void GameBoy::Switch(ushort addr)
{
    memory->Switch(addr);
}

void GameBoy::Interrupt(ushort addr)
{
    cpu->Interrupt(addr);
}

/*void GameBoy::FindSprites()
{
    lcd->FindSprites();
}*/

void GameBoy::Clock()
{
    cpu->Clock();
}

bool GameBoy::Drawing()
{
    return ints->Drawing();
}

void GameBoy::Manager()
{
    ints->Manager();
}


int main()
{
	GameBoy* gb = new GameBoy();
	gb->Link("Tetris.gb");
    gb->Run();
	return 0;
}
