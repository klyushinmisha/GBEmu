#include "Main/Interrupts.h"

Interrupts::Interrupts(GameBoy* gb, byte* RAM)
{
    interruptCounter = 0;
    this->gb = gb;
    this->RAM = RAM;
    gb->Halt = false; gb->Stop = false;
    gb->IME = true;
    gb->DMATransfer = false;
    IE = RAM + 0xFFFF;
    IF = RAM + 0xFF0F;
}

void Interrupts::Sync(int value)
{
    interruptCounter += value;
}

void Interrupts::Manager()
{
    if (gb->Stop)
        return;
    if ((*IE & *IF) != 0)
    {
        gb->Halt = false;
        if (gb->IME)
        {
            gb->IME = false;
            byte interrupts = (byte)(*IE & *IF), interrupt = 0;
            *IF &= (byte)(~interrupts);
            while (((interrupts >> interrupt) & 1) != 1)
                interrupt++;
            switch (interrupt)
            {
                case 0:
                    gb->Interrupt(0x40);
                    break;
                case 1:
                    gb->Interrupt(0x48);
                    break;
                case 2:
                    gb->Interrupt(0x50);
                    break;
                case 4:
                    gb->Interrupt(0x60);
                    break;
            }
        }
    }

    if (gb->Halt)
        gb->Sync();
    else
        gb->Clock();
}

bool Interrupts::Drawing()
{
    if (gb->DMATransfer)
    {
        ushort addr = (ushort)((ushort)RAM[0xFF46] * 0x100);
        gb->DMATransfer = false;
        for (int i = 0; i < 160; i++)
            RAM[0xFE00 + i] = RAM[addr + i];
    }

    switch (gb->getMode())
    {
        case 0:
            if (interruptCounter >= 204)
            {
                interruptCounter %= 204;
                gb->DrawLine();
                if (gb->getYCoordinate() == 144)
                {
                    gb->setMode(1);
                    RAM[0xFF0F] |= 3;
                }
                else
                {
                    //gb->FindSprites();
                    gb->setMode(2);
                    RAM[0xFF0F] |= 2;
                }
                
            }
            break;
        case 2:
            if (interruptCounter >= 80)
            {
                interruptCounter %= 80;
                gb->setMode(3);
                RAM[0xFF0F] |= 2;
            }
            break;
        case 3:
            if (interruptCounter >= 172)
            {
                interruptCounter %= 172;
                gb->setMode(0);
                RAM[0xFF0F] |= 2;
            }
            break;
        case 1:
            if (interruptCounter >= 456)
            {
                gb->setYCoordinate(gb->getYCoordinate() + 1);
                interruptCounter %= 456;
            }
            if (gb->getYCoordinate() == 154)
            {
                gb->setYCoordinate(0);
                interruptCounter = 0;
                gb->setMode(2);
                RAM[0xFF0F] |= 2;
                return false;
            }
            break;
    }
    if (gb->getLYCompare() == gb->getYCoordinate())
        gb->setCoincidenceFlag(true);
    else
        gb->setCoincidenceFlag(false);
    if (gb->getCoincidenceFlag() & gb->getLYCLYCoincidenceInterrupt())
        RAM[0xFF0F] |= 2;
    return true;
}