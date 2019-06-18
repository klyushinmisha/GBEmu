#pragma once
#include <exception>

typedef unsigned char byte;
typedef signed char sbyte;
typedef unsigned short ushort;

class GameBoy;

class CPU
{
public:
    CPU();
    void Clock();

    //Used by interrupts to save previous Program Counter
    //and jump to it's start address
    void Interrupt(ushort addr);


protected:
    void DI();
    void EI();
protected:
        //Combinations of 2 usual 1 byte registers
        ushort AF;
        ushort BC;
        ushort DE;
        ushort HL;


        bool Zero;
        bool Substract;
        bool HalfCarry;
        bool Carry;
        //CPU flags used for different mathematical operations
        /*bool Zero
        { get { return F >> 7 == 1; } set { if (value == true) F |= 0x80; else F &= 0b1111111; } }
        bool Substract
        { get { return ((F >> 6) & 1) == 1; } set { if (value == true) F |= 0x40; else F &= 0b10111111; } }
        bool HalfCarry
        { get { return ((F >> 5) & 1) == 1; } set { if (value == true) F |= 0x20; else F &= 0b11011111; } }
        bool Carry
        { get { return ((F >> 4) & 1) == 1; } set { if (value == true) F |= 0x10; else F &= 0b11101111; } }*/

        //CPU registers
        byte* A;
        byte* F;
        byte* B;
        byte* C;
        byte* D;
        byte* E;
        byte* H;
        byte* L;
        ushort PC, SP;


        //Useful temp variables
        byte opcode, tmp;

        GameBoy* gb;


        void ADD(byte value);
        void ADC(byte value);
        void SUB(byte value);
        void SBC(byte value);
        void INC(byte* value);
        void DEC(byte* value);
        void ADD(ushort value);
        void ADD_SP_n();
        ushort ADDsbyteToSP();


        void AND(byte value);
        void OR(byte value);
        void XOR(byte value);
        void CP(byte value);

        
        void HALT();
        void STOP();


        void DAA();
        void SWAP(byte* value);
        void CPL();
        void CCF();
        void SCF();
        void RLC(byte* value);
        void RL(byte* value);
        void RRC(byte* value);
        void RR(byte* value);
        void SLA(byte* value);
        void SRA(byte* value);
        void SRL(byte* value);
        void BIT(byte bit, byte value);
        void SET(byte* value, byte bit);
        void RES(byte* value, byte bit);


        void PUSH(byte h, byte l);
        void POP(byte* h, byte* l);
        void JP(bool flag);
        void JR(bool flag);
        void CALL(bool flag);
        void RST(ushort addr);
        void RET(bool flag);
        void RETI();
};
