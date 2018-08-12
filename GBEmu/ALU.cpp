#include "CPU/ALU.h"
#include <math.h>

//ADC, SBC, BIT


ALU::ALU(GameBoy* gb)
{
    this->gb = gb;
    A = (byte*)&AF + 1;
    F = (byte*)&AF;
    B = (byte*)&BC + 1;
    C = (byte*)&BC;
    D = (byte*)&DE + 1;
    E = (byte*)&DE;
    H = (byte*)&HL + 1;
    L = (byte*)&HL;
    PC = 0;
}


void ALU::ADD(byte value)
{
    Substract = false;
    HalfCarry = (((*A & 0xF) + (value & 0xF)) & 0x10) == 0x10;
    Carry = ((*A + value) & 0x100) == 0x100;
    *A += value;
    Zero = (*A) == 0;
}

void ALU::ADC(byte value)
{
    ADD((byte)(value + *F & 0x10));
}

void ALU::SUB(byte value)
{
    Substract = true;
    HalfCarry = (*A & 0xF) >= (value & 0xF);
    Carry = (~(*A) & value) == 0;
    *A -= value;
    Zero = (*A) == 0;
}

void ALU::SBC(byte value)
{
    SUB(value + *F & 0x10);
}

void ALU::INC(byte* value)
{
    Substract = false;
    HalfCarry = (*value & 0xF) == 0xF;
    (*value)++;
    Zero = *value == 0;
}

void ALU::DEC(byte* value)
{
    Substract = true;
    HalfCarry = (*value & 0xF) == 0;
    (*value)--;
    Zero = *value == 0;
}

void ALU::ADD(ushort value)
{
    Substract = false;
    HalfCarry = (((HL & 0xFFF) + (value & 0xFFF)) & 0x1000) == 0x1000;
    Carry = (((HL & 0xFFFF) + (value & 0xFFFF)) & 0x10000) == 0x10000;
    HL += value;
    gb->SyncCycles(4);
}

void ALU::ADD_SP_n()
{
    SP = ADDsbyteToSP();
}


ushort ALU::ADDsbyteToSP()
{
    Zero = false;
    Substract = false;
    tmp = gb->Read(PC);
    PC++;
    char* sb = (char*)&tmp;
    if (*sb < 0)
    {
        HalfCarry = (SP & 0xFFF) > (abs(*sb) & 0xFFF);
        Carry = (SP & 0xFFFF) > (abs(*sb) & 0xFFFF);
    }
    else
    {
        HalfCarry = (((SP & 0xFFF) + (tmp & 0xFFF)) & 0x1000) == 0x1000;
        Carry = (((SP & 0xFFFF) + (tmp & 0xFFFF)) & 0x10000) == 0x10000;
    }
    gb->SyncCycles(8);
    return SP + *sb;
}



void ALU::AND(byte value)
{
    HalfCarry = true;
    Substract = false;
    Carry = false;
    *A &= value;
    Zero = (*A) == 0;
}

void ALU::OR(byte value)
{
    HalfCarry = false;
    Substract = false;
    Carry = false;
    *A |= value;
    Zero = (*A) == 0;
}

void ALU::XOR(byte value)
{
    HalfCarry = false;
    Substract = false;
    Carry = false;
    *A ^= value;
    Zero = (*A) == 0;
}

void ALU::CP(byte value)
{
    if (*A < value)
        Carry = true;
    else
        Carry = false;
    
    if (*A == value)
        Zero = true;
    else
        Zero = false;
}

void ALU::DAA()
{
    byte bias = Carry ? 0x60 : 0;

    bias += HalfCarry ? 0x6 : 0;

    if (Substract)
        *A -= bias;
    else
    {
        if ((*A & 0xF) > 9)
            bias |= 6;
        if (*A > 0x99)
        {
            bias |= 0x60;
            Carry = true;
        }
        *A += bias;
    }

    HalfCarry = false;

    Zero = (*A) == 0;
}

void ALU::HALT()
{
    if (!gb->IME)
        PC++;
    else
        gb->Halt = true;
}

void ALU::STOP()
{
    if (gb->Read(PC) == 0x00)
    {
        gb->Stop = true;
        PC++;
        gb->SyncCycles(-4);
    }
}

void ALU::SWAP(byte* value)
{
    Zero = (*value) == 0;
    HalfCarry = false;
    Substract = false;
    Carry = false;
    *value = (*value & 0xF0) >> 4 | (*value) << 4;
}

void ALU::CPL()
{
    *A = ~(*A);
    Substract = true;
    HalfCarry = true;
}

void ALU::CCF()
{
    Substract = false;
    HalfCarry = false;
    Carry = !Carry;
}

void ALU::SCF()
{
    Substract = false;
    HalfCarry = false;
    Carry = true;
}



void ALU::RLC(byte* value)
{
    Carry = ((*value >> 7) & 1) == 1;
    *value = *value >> 7 | (*value) << 1;
    Zero = (*value) == 0;
    HalfCarry = false;
    Substract = false;
}

void ALU::RL(byte* value)
{
    byte temp = (*value);
    *value = *value << 1 | (Carry ? 1 : 0);
    Carry = ((temp >> 7) & 1) == 1;
    Zero = (*value) == 0;
    HalfCarry = false;
    Substract = false;
}


void ALU::RRC(byte* value)
{
    Carry = (*value & 1) == 1;
    *value = (*value >> 1) | ((*value & 1) << 7);
    Zero = (*value) == 0;
    HalfCarry = false;
    Substract = false;
}


void ALU::RR(byte* value)
{
    byte temp = (*value);
    *value = *value >> 1 | (Carry ? 0x80 : 0);
    Carry = (temp & 1) == 1;
    Zero = (*value) == 0;
    HalfCarry = false;
    Substract = false;
}


void ALU::SLA(byte* value)
{
    Carry = (*value & 0x80) == 0x80;
    *value = *value << 1;
    Zero = (*value) == 0;
    HalfCarry = false;
    Substract = false;
}


void ALU::SRA(byte* value)
{
    Carry = (*value & 1) == 1;
    *value = (*value & 0x80) | (*value) >> 1;
    Zero = value == 0;
    HalfCarry = false;
    Substract = false;
}


void ALU::SRL(byte* value)
{
    Carry = (*value & 1) == 1;
    *value = *value >> 1;
    Zero = (*value) == 0;
    HalfCarry = false;
    Substract = false;
}


void ALU::BIT(byte bit, byte value)
{
    *F = (*F & 0x10) | 0x20;
    if ((value >> bit) == 0)
        Zero = true;
}

void ALU::SET(byte* value, byte bit)
{
    *value |= 1 << bit;
}


void ALU::RES(byte* value, byte bit)
{
    *value &= ~(1 << bit);
}



void ALU::PUSH(byte h, byte l)
{
    gb->Write(--SP, h);
    gb->Write(--SP, l);
    gb->SyncCycles(8);
}


void ALU::POP(byte* h, byte* l)
{
    *l = gb->Read(SP);
    SP++;
    *h = gb->Read(SP);
    SP++;
    gb->SyncCycles(4);
}


void ALU::JP(bool flag)
{
    if (flag)
        PC = gb->ReadWord(PC);
    else
    {
        PC += 2;
        gb->SyncCycles(4);
    }
    gb->SyncCycles(4);
}


void ALU::JR(bool flag)
{
    byte value;
    char* sb;
    if (flag)
    {
        value = gb->Read(PC);
        sb = (char*)&value;
        PC = (ushort)(PC + *sb);
    }
    PC++;
    gb->SyncCycles(4);
    
}


void ALU::CALL(bool flag)
{
    if (flag)
    {
        SP -= 2;
        gb->WriteWord(SP, (ushort)(PC + 2));
        PC = gb->ReadWord(PC);
    }
    else
    {
        PC += 2;
        gb->SyncCycles(4);
    }
    gb->SyncCycles(4);
}


void ALU::RST(ushort addr)
{
    SP -= 2;
    gb->WriteWord(SP, PC);
    PC = addr;
    gb->SyncCycles(4);
}


void ALU::RET(bool flag)
{
    if (flag)
    {
        PC = gb->ReadWord(SP);
        SP += 2;
        gb->SyncCycles(4);
    }
    gb->SyncCycles(4);
}


void ALU::RETI()
{
    PC = gb->ReadWord(SP);
    SP += 2;
    gb->IME = true;
}
