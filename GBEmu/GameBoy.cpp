#include "Main/GameBoy.h"
#include <exception>

void GameBoy::Link(std::string cartridgeName)
{
    DMATransfer = false;
    IME = true;
    Halt = false;
    Stop = false;
    RAM = new byte[0x10000];
    this->memory = new Memory(this, cartridgeName, RAM);
    this->cpu = new CPU(this);
    this->lcd = new LCD(this, RAM);
    this->timer = new Timer(RAM);
    this->ints = new Interrupts(this, RAM);
    setMode(2);
    setOAMInterrupt(true);
}

static const byte colors[4][3] = { { 196, 207, 161 }, { 139, 149, 109 }, { 107, 115, 83 }, { 65, 65, 65 } };

void GameBoy::DrawPixel(int x, int y, int color)
{
    SDL_SetRenderDrawColor(ren, colors[color][0], colors[color][1], colors[color][2], 255);
    r->x = x*scale;
    r->y = y*scale;
    SDL_RenderFillRect(ren, r);
}

void GameBoy::Run()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    
    scale = 3;
    SDL_Window* w = SDL_CreateWindow("GBEmu", 100, 100, 160*scale, 144*scale, 0);

    SDL_Event e;
    ren = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED);
    r = new SDL_Rect();

    bool isRunning = true;
    r->w = scale;
    r->h = scale;
    SDL_ShowWindow(w);
    SDL_RenderClear(ren);
    while (isRunning)
    {
        if (Drawing())
            Manager();
        else
        {
            SDL_RenderPresent(ren);
            SDL_PollEvent(&e);
            switch (e.type)
            {
                case SDL_QUIT:
                    isRunning = false;
                    break;
                case SDL_KEYDOWN:
                    KeyDown(e);
                    break;
                case SDL_KEYUP:
                    KeyUp();
                    break;
            }
        }
    }

    delete r;

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(w);
    SDL_Quit();
}

void GameBoy::KeyDown(SDL_Event e)
{
    byte key = 0;
    
    if (((RAM[0xFF00] >> 4) & 3) == 3 | ((RAM[0xFF00] >> 4) & 3) == 0)
        return;
    
    if (RAM[0xFF00] >> 4 == 0b1101)
        switch (e.key.keysym.sym)
        {
            case SDL_SCANCODE_1:
                key = 0b111;
                break;
            case SDL_SCANCODE_2:
                key = 0b1011;
                break;
            case SDL_SCANCODE_K:
                key = 0b1101;
                break;
            case SDL_SCANCODE_L:
                key = 0b1110;
                break;
            default:
                return;
        }
    else if (RAM[0xFF00] >> 4 == 0b1110)
        switch (e.key.keysym.sym)
        {
            case SDL_SCANCODE_W:
                key = 0b1011;
                break;
            case SDL_SCANCODE_A:
                key = 0b1101;
                break;
            case SDL_SCANCODE_S:
                key = 0b111;
                break;
            case SDL_SCANCODE_D:
                key = 0b1110;
                break;
            default:
                return;
        }
    
    RAM[0xFF0F] |= 0b10000;
    RAM[0xFF00] &= 0xF0;
    RAM[0xFF00] |= key;
    Stop = false;
}

void GameBoy::KeyUp()
{
    RAM[0xFF00] &= 0xF0;
    RAM[0xFF00] |= 0xF;
}

GameBoy::~GameBoy()
{
    delete[] RAM;
}

void GameBoy::SyncCycles(int count)
{
    ints->Sync(count);
}

void GameBoy::Sync()
{
    SyncCycles(4);
    timer->Inc();
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
