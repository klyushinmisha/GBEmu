#include "Main/CPU.h"
#include "Main/GameBoy.h"

CPU::CPU() {
    this->gb = GameBoy::getInstance();
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

void CPU::Clock()
{
    //Checks for switching banks
    gb->Switch(PC);
    //Extracts opcode
    opcode = gb->Read(PC);
    PC++;

    //Extracts equal instruction
    switch (opcode)
    {
        //LD nn, n
        case 0x06:
            *B = gb->Read(PC);
            PC++;
            break;
        case 0x0E:
            *C = gb->Read(PC);
            PC++;
            break;
        case 0x16:
            *D = gb->Read(PC);
            PC++;
            break;
        case 0x1E:
            *E = gb->Read(PC);
            PC++;
            break;
        case 0x26:
            *H = gb->Read(PC);
            PC++;
            break;
        case 0x2E:
            *L = gb->Read(PC);
            PC++;
            break;


        //LD r1, r2
        //*A
        case 0x7F:
            break;
        case 0x78:
            *A = *B;
            break;
        case 0x79:
            *A = *C;
            break;
        case 0x7A:
            *A = *D;
            break;
        case 0x7B:
            *A = *E;
            break;
        case 0x7C:
            *A = *H;
            break;
        case 0x7D:
            *A = *L;
            break;
        case 0x7E:
            *A = gb->Read(HL);
            break;


        //*B
        case 0x40:
            break;
        case 0x41:
            *B = *C;
            break;
        case 0x42:
            *B = *D;
            break;
        case 0x43:
            *B = *E;
            break;
        case 0x44:
            *B = *H;
            break;
        case 0x45:
            *B = *L;
            break;
        case 0x46:
            *B = gb->Read(HL);
            break;


        //*C
        case 0x48:
            *C = *B;
            break;
        case 0x49:
            break;
        case 0x4A:
            *C = *D;
            break;
        case 0x4B:
            *C = *E;
            break;
        case 0x4C:
            *C = *H;
            break;
        case 0x4D:
            *C = *L;
            break;
        case 0x4E:
            *C = gb->Read(HL);
            break;


        //*D
        case 0x50:
            *D = *B;
            break;
        case 0x51:
            *D = *C;
            break;
        case 0x52:
            break;
        case 0x53:
            *D = *E;
            break;
        case 0x54:
            *D = *H;
            break;
        case 0x55:
            *D = *L;
            break;
        case 0x56:
            *D = gb->Read(HL);
            break;


        //*E
        case 0x58:
            *E = *B;
            break;
        case 0x59:
            *E = *C;
            break;
        case 0x5A:
            *E = *D;
            break;
        case 0x5B:
            break;
        case 0x5C:
            *E = *H;
            break;
        case 0x5D:
            *E = *L;
            break;
        case 0x5E:
            *E = gb->Read(HL);
            break;


        //*H
        case 0x60:
            *H = *B;
            break;
        case 0x61:
            *H = *C;
            break;
        case 0x62:
            *H = *D;
            break;
        case 0x63:
            *H = *E;
            break;
        case 0x64:
            break;
        case 0x65:
            *H = *L;
            break;
        case 0x66:
            *H = gb->Read(HL);
            break;


        //*L
        case 0x68:
            *L = *B;
            break;
        case 0x69:
            *L = *C;
            break;
        case 0x6A:
            *L = *D;
            break;
        case 0x6B:
            *L = *E;
            break;
        case 0x6C:
            *L = *H;
            break;
        case 0x6D:
            break;
        case 0x6E:
            *L = gb->Read(HL);
            break;


        //(HL)
        case 0x70:
            gb->Write(HL, *B);
            break;
        case 0x71:
            gb->Write(HL, *C);
            break;
        case 0x72:
            gb->Write(HL, *D);
            break;
        case 0x73:
            gb->Write(HL, *E);
            break;
        case 0x74:
            gb->Write(HL, *H);
            break;
        case 0x75:
            gb->Write(HL, *L);
            break;
        case 0x36:
            gb->Write(HL, gb->Read(PC++));
            break;


        //LD *A, n
        case 0x0A:
            *A = gb->Read(BC);
            break;
        case 0x1A:
            *A = gb->Read(DE);
            break;
        case 0xFA:
            *A = gb->Read(gb->ReadWord(PC));
            PC += 2;
            break;
        case 0x3E:
            *A = gb->Read(PC);
            PC++;
            break;


        //LD n, *A
        case 0x47:
            *B = *A;
            break;
        case 0x4F:
            *C = *A;
            break;
        case 0x57:
            *D = *A;
            break;
        case 0x5F:
            *E = *A;
            break;
        case 0x67:
            *H = *A;
            break;
        case 0x6F:
            *L = *A;
            break;
        case 0x02:
            gb->Write(BC, *A);
            break;
        case 0x12:
            gb->Write(DE, *A);
            break;
        case 0x77:
            gb->Write(HL, *A);
            break;
        case 0xEA:
            gb->Write(gb->ReadWord(PC), *A);
            PC += 2;
            break;


        //LD *A, (*C)
        case 0xF2:
            *A = gb->Read(0xFF00 + *C);
            break;
        case 0xE2:
            gb->Write(0xFF00 + *C, *A);
            break;
        case 0x3A:
            *A = gb->Read(HL--);
            break;
        case 0x32:
            gb->Write(HL--, *A);
            break;
        case 0x2A:
            *A = gb->Read(HL++);
            break;
        case 0x22:
            gb->Write(HL++, *A);
            break;
        case 0xE0:
            gb->Write(0xFF00 + gb->Read(PC), *A);
            PC++;
            break;
        case 0xF0:
            *A = gb->Read(0xFF00 + gb->Read(PC));
            PC++;
            break;


        //16bit loads
        //LD n, nn
        case 0x01:
            BC = gb->ReadWord(PC);
            PC += 2;
            break;
        case 0x11:
            DE = gb->ReadWord(PC);
            PC += 2;
            break;
        case 0x21:
            HL = gb->ReadWord(PC);
            PC += 2;
            break;
        case 0x31:
            SP = gb->ReadWord(PC);
            PC += 2;
            break;
        case 0xF9:
            SP = HL;
            gb->SyncCycles(4);
            break;
        case 0xF8:
            HL = ADDsbyteToSP();
            break;


        case 0x08:
            gb->WriteWord(gb->ReadWord(PC), SP);
            PC += 2;
            gb->SyncCycles(4);
            break;


        case 0xF5:
            *F = 0;
            *F |= Zero ? 0x80 : 0;
            *F |= Substract ? 0x40 : 0;
            *F |= HalfCarry ? 0x20 : 0;
            *F |= Carry ? 0x10 : 0;
            PUSH(*A, *F);
            break;
        case 0xC5:
            PUSH(*B, *C);
            break;
        case 0xD5:
            PUSH(*D, *E);
            break;
        case 0xE5:
            PUSH(*H, *L);
            break;


        case 0xF1:
            POP(A, F);
            Carry = (*F & 0x10) == 0x10;
            HalfCarry = (*F & 0x20) == 0x20;
            Substract = (*F & 0x40) == 0x40;
            Zero = (*F & 0x80) == 0x80;
            break;
        case 0xC1:
            POP(B, C);
            break;
        case 0xD1:
            POP(D, E);
            break;
        case 0xE1:
            POP(H, L);
            break;


        case 0x87:
            ADD(*A);
            break;
        case 0x80:
            ADD(*B);
            break;
        case 0x81:
            ADD(*C);
            break;
        case 0x82:
            ADD(*D);
            break;
        case 0x83:
            ADD(*E);
            break;
        case 0x84:
            ADD(*H);
            break;
        case 0x85:
            ADD(*L);
            break;
        case 0x86:
            ADD(gb->Read(HL));
            break;
        case 0xC6:
            ADD(gb->Read(PC));
            PC++;
            break;
            


        case 0x8F:
            ADC(*A);
            break;
        case 0x88:
            ADC(*B);
            break;
        case 0x89:
            ADC(*C);
            break;
        case 0x8A:
            ADC(*D);
            break;
        case 0x8B:
            ADC(*E);
            break;
        case 0x8C:
            ADC(*H);
            break;
        case 0x8D:
            ADC(*L);
            break;
        case 0x8E:
            ADC(gb->Read(HL));
            break;
        case 0xCE:
            ADC(gb->Read(PC++));
            break;




        //SUB n
        case 0x97:
            SUB(*A);
            break;
        case 0x90:
            SUB(*B);
            break;
        case 0x91:
            SUB(*C);
            break;
        case 0x92:
            SUB(*D);
            break;
        case 0x93:
            SUB(*E);
            break;
        case 0x94:
            SUB(*H);
            break;
        case 0x95:
            SUB(*L);
            break;
        case 0x96:
            SUB(gb->Read(HL));
            break;
        case 0xD6:
            SUB(gb->Read(PC++));
            break;


        //SBC
        case 0x9F:
            SBC(*A);
            break;
        case 0x98:
            SBC(*B);
            break;
        case 0x99:
            SBC(*C);
            break;
        case 0x9A:
            SBC(*D);
            break;
        case 0x9B:
            SBC(*E);
            break;
        case 0x9C:
            SBC(*H);
            break;
        case 0x9D:
            SBC(*L);
            break;
        case 0x9E:
            SBC(gb->Read(HL));
            break;
        case 0xDE:
            SBC(gb->Read(PC++));
            break;


        case 0xA7:
            AND(*A);
            break;
        case 0xA0:
            AND(*B);
            break;
        case 0xA1:
            AND(*C);
            break;
        case 0xA2:
            AND(*D);
            break;
        case 0xA3:
            AND(*E);
            break;
        case 0xA4:
            AND(*H);
            break;
        case 0xA5:
            AND(*L);
            break;
        case 0xA6:
            AND(gb->Read(HL));
            break;
        case 0xE6:
            AND(gb->Read(PC++));
            break;


        case 0xB7:
            OR(*A);
            break;
        case 0xB0:
            OR(*B);
            break;
        case 0xB1:
            OR(*C);
            break;
        case 0xB2:
            OR(*D);
            break;
        case 0xB3:
            OR(*E);
            break;
        case 0xB4:
            OR(*H);
            break;
        case 0xB5:
            OR(*L);
            break;
        case 0xB6:
            OR(gb->Read(HL));
            break;
        case 0xF6:
            OR(gb->Read(PC++));
            break;


        case 0xAF:
            XOR(*A);
            break;
        case 0xA8:
            XOR(*B);
            break;
        case 0xA9:
            XOR(*C);
            break;
        case 0xAA:
            XOR(*D);
            break;
        case 0xAB:
            XOR(*E);
            break;
        case 0xAC:
            XOR(*H);
            break;
        case 0xAD:
            XOR(*L);
            break;
        case 0xAE:
            XOR(gb->Read(HL));
            break;
        case 0xEE:
            XOR(gb->Read(PC++));
            break;


        case 0xBF:
            CP(*A);
            break;
        case 0xB8:
            CP(*B);
            break;
        case 0xB9:
            CP(*C);
            break;
        case 0xBA:
            CP(*D);
            break;
        case 0xBB:
            CP(*E);
            break;
        case 0xBC:
            CP(*H);
            break;
        case 0xBD:
            CP(*L);
            break;
        case 0xBE:
            CP(gb->Read(HL));
            break;
        case 0xFE:
            CP(gb->Read(PC++));
            break;


        case 0x3C:
            INC(A);
            break;
        case 0x04:
            INC(B);
            break;
        case 0x0C:
            INC(C);
            break;
        case 0x14:
            INC(D);
            break;
        case 0x1C:
            INC(E);
            break;
        case 0x24:
            INC(H);
            break;
        case 0x2C:
            INC(L);
            break;
        case 0x34:
            tmp = gb->Read(HL);
            INC(&tmp);
            gb->Write(HL, tmp);
            break;


        case 0x3D:
            DEC(A);
            break;
        case 0x05:
            DEC(B);
            break;
        case 0x0D:
            DEC(C);
            break;
        case 0x15:
            DEC(D);
            break;
        case 0x1D:
            DEC(E);
            break;
        case 0x25:
            DEC(H);
            break;
        case 0x2D:
            DEC(L);
            break;
        case 0x35:
            tmp = gb->Read(HL);
            DEC(&tmp);
            gb->Write(HL, tmp);
            break;


        //страница 90 
        //16-bit arithmetics
        case 0x09:
            ADD(BC);
            break;
        case 0x19:
            ADD(DE);
            break;
        case 0x29:
            ADD(HL);
            break;
        case 0x39:
            ADD(SP);
            break;


        case 0xE8:
            ADD_SP_n();
            break;




        case 0x03:
            BC++;
            gb->SyncCycles(4);
            break;
        case 0x13:
            DE++;
            gb->SyncCycles(4);
            break;
        case 0x23:
            HL++;
            gb->SyncCycles(4);
            break;
        case 0x33:
            SP++;
            gb->SyncCycles(4);
            break;


        case 0x0B:
            BC--;
            gb->SyncCycles(4);
            break;
        case 0x1B:
            DE--;
            gb->SyncCycles(4);
            break;
        case 0x2B:
            HL--;
            gb->SyncCycles(4);
            break;
        case 0x3B:
            SP--;
            gb->SyncCycles(4);
            break;


        case 0xCB:
            opcode = gb->Read(PC);
            PC++;
            switch (opcode)
            {
                case 0x37:
                    SWAP(A);
                    break;
                case 0x30:
                    SWAP(B);
                    break;
                case 0x31:
                    SWAP(C);
                    break;
                case 0x32:
                    SWAP(D);
                    break;
                case 0x33:
                    SWAP(E);
                    break;
                case 0x34:
                    SWAP(H);
                    break;
                case 0x35:
                    SWAP(L);
                    break;
                case 0x36:
                    tmp = gb->Read(HL);
                    SWAP(&tmp);
                    gb->Write(HL, tmp);
                    break;


                //Rotations
                case 0x07:
                    RLC(A);
                    break;
                case 0x00:
                    RLC(B);
                    break;
                case 0x01:
                    RLC(C);
                    break;
                case 0x02:
                    RLC(D);
                    break;
                case 0x03:
                    RLC(E);
                    break;
                case 0x04:
                    RLC(H);
                    break;
                case 0x05:
                    RLC(L);
                    break;
                case 0x06:
                    tmp = gb->Read(HL);
                    RLC(&tmp);
                    gb->Write(HL, tmp);
                    break;


                case 0x17:
                    RL(A);
                    break;
                case 0x10:
                    RL(B);
                    break;
                case 0x11:
                    RL(C);
                    break;
                case 0x12:
                    RL(D);
                    break;
                case 0x13:
                    RL(E);
                    break;
                case 0x14:
                    RL(H);
                    break;
                case 0x15:
                    RL(L);
                    break;
                case 0x16:
                    tmp = gb->Read(HL);
                    RL(&tmp);
                    gb->Write(HL, tmp);
                    break;


                case 0x0F:
                    RRC(A);
                    break;
                case 0x08:
                    RRC(B);
                    break;
                case 0x09:
                    RRC(C);
                    break;
                case 0x0A:
                    RRC(D);
                    break;
                case 0x0B:
                    RRC(E);
                    break;
                case 0x0C:
                    RRC(H);
                    break;
                case 0x0D:
                    RRC(L);
                    break;
                case 0x0E:
                    tmp = gb->Read(HL);
                    RRC(&tmp);
                    gb->Write(HL, tmp);
                    break;


                case 0x1F:
                    RR(A);
                    break;
                case 0x18:
                    RR(B);
                    break;
                case 0x19:
                    RR(C);
                    break;
                case 0x1A:
                    RR(D);
                    break;
                case 0x1B:
                    RR(E);
                    break;
                case 0x1C:
                    RR(H);
                    break;
                case 0x1D:
                    RR(L);
                    break;
                case 0x1E:
                    tmp = gb->Read(HL);
                    RR(&tmp);
                    gb->Write(HL, tmp);
                    break;


                case 0x27:
                    SLA(A);
                    break;
                case 0x20:
                    SLA(B);
                    break;
                case 0x21:
                    SLA(C);
                    break;
                case 0x22:
                    SLA(D);
                    break;
                case 0x23:
                    SLA(E);
                    break;
                case 0x24:
                    SLA(H);
                    break;
                case 0x25:
                    SLA(L);
                    break;
                case 0x26:
                    tmp = gb->Read(HL);
                    SLA(&tmp);
                    gb->Write(HL, tmp);
                    break;


                case 0x2F:
                    SRA(A);
                    break;
                case 0x28:
                    SRA(B);
                    break;
                case 0x29:
                    SRA(C);
                    break;
                case 0x2A:
                    SRA(D);
                    break;
                case 0x2B:
                    SRA(E);
                    break;
                case 0x2C:
                    SRA(H);
                    break;
                case 0x2D:
                    SRA(L);
                    break;
                case 0x2E:
                    tmp = gb->Read(HL);
                    SRA(&tmp);
                    gb->Write(HL, tmp);
                    break;


                case 0x3F:
                    SRL(A);
                    break;
                case 0x38:
                    SRL(B);
                    break;
                case 0x39:
                    SRL(C);
                    break;
                case 0x3A:
                    SRL(D);
                    break;
                case 0x3B:
                    SRL(E);
                    break;
                case 0x3C:
                    SRL(H);
                    break;
                case 0x3D:
                    SRL(L);
                    break;
                case 0x3E:
                    tmp = gb->Read(HL);
                    SRL(&tmp);
                    gb->Write(HL, tmp);
                    break;


                case 0x47:
                    BIT(0, *A);
                    break;
                case 0x40:
                    BIT(0, *B);
                    break;
                case 0x41:
                    BIT(0, *C);
                    break;
                case 0x42:
                    BIT(0, *D);
                    break;
                case 0x43:
                    BIT(0, *E);
                    break;
                case 0x44:
                    BIT(0, *H);
                    break;
                case 0x45:
                    BIT(0, *L);
                    break;
                case 0x46:
                    BIT(0, gb->Read(HL));
                    break;


                case 0x4F:
                    BIT(1, *A);
                    break;
                case 0x48:
                    BIT(1, *B);
                    break;
                case 0x49:
                    BIT(1, *C);
                    break;
                case 0x4A:
                    BIT(1, *D);
                    break;
                case 0x4B:
                    BIT(1, *E);
                    break;
                case 0x4C:
                    BIT(1, *H);
                    break;
                case 0x4D:
                    BIT(1, *L);
                    break;
                case 0x4E:
                    BIT(1, gb->Read(HL));
                    break;


                case 0x57:
                    BIT(2, *A);
                    break;
                case 0x50:
                    BIT(2, *B);
                    break;
                case 0x51:
                    BIT(2, *C);
                    break;
                case 0x52:
                    BIT(2, *D);
                    break;
                case 0x53:
                    BIT(2, *E);
                    break;
                case 0x54:
                    BIT(2, *H);
                    break;
                case 0x55:
                    BIT(2, *L);
                    break;
                case 0x56:
                    BIT(2, gb->Read(HL));
                    break;


                case 0x5F:
                    BIT(3, *A);
                    break;
                case 0x58:
                    BIT(3, *B);
                    break;
                case 0x59:
                    BIT(3, *C);
                    break;
                case 0x5A:
                    BIT(3, *D);
                    break;
                case 0x5B:
                    BIT(3, *E);
                    break;
                case 0x5C:
                    BIT(3, *H);
                    break;
                case 0x5D:
                    BIT(3, *L);
                    break;
                case 0x5E:
                    BIT(3, gb->Read(HL));
                    break;


                case 0x67:
                    BIT(4, *A);
                    break;
                case 0x60:
                    BIT(4,  *B);
                    break;
                case 0x61:
                    BIT(4,  *C);
                    break;
                case 0x62:
                    BIT(4,  *D);
                    break;
                case 0x63:
                    BIT(4,  *E);
                    break;
                case 0x64:
                    BIT(4,  *H);
                    break;
                case 0x65:
                    BIT(4,  *L);
                    break;
                case 0x66:
                    BIT(4, gb->Read(HL));
                    break;


                case 0x6F:
                    BIT(5,  *A);
                    break;
                case 0x68:
                    BIT(5,  *B);
                    break;
                case 0x69:
                    BIT(5,  *C);
                    break;
                case 0x6A:
                    BIT(5,  *D);
                    break;
                case 0x6B:
                    BIT(5,  *E);
                    break;
                case 0x6C:
                    BIT(5,  *H);
                    break;
                case 0x6D:
                    BIT(5,  *L);
                    break;
                case 0x6E:
                    BIT(5, gb->Read(HL));
                    break;


                case 0x77:
                    BIT(6, *A);
                    break;
                case 0x70:
                    BIT(6, *B);
                    break;
                case 0x71:
                    BIT(6, *C);
                    break;
                case 0x72:
                    BIT(6, *D);
                    break;
                case 0x73:
                    BIT(6, *E);
                    break;
                case 0x74:
                    BIT(6, *H);
                    break;
                case 0x75:
                    BIT(6, *L);
                    break;
                case 0x76:
                    BIT(6, gb->Read(HL));
                    break;


                case 0x7F:
                    BIT(7,  *A);
                    break;
                case 0x78:
                    BIT(7,  *B);
                    break;
                case 0x79:
                    BIT(7,  *C);
                    break;
                case 0x7A:
                    BIT(7,  *D);
                    break;
                case 0x7B:
                    BIT(7,  *E);
                    break;
                case 0x7C:
                    BIT(7,  *H);
                    break;
                case 0x7D:
                    BIT(7,  *L);
                    break;
                case 0x7E:
                    BIT(7, gb->Read(HL));
                    break;


                case 0xC7:
                    SET(A, 0);
                    break;
                case 0xC0:
                    SET(B, 0);
                    break;
                case 0xC1:
                    SET(C, 0);
                    break;
                case 0xC2:
                    SET(D, 0);
                    break;
                case 0xC3:
                    SET(E, 0);
                    break;
                case 0xC4:
                    SET(H, 0);
                    break;
                case 0xC5:
                    SET(L, 0);
                    break;
                case 0xC6:
                    tmp = gb->Read(HL);
                    SET(&tmp, 0);
                    gb->Write(HL, tmp);
                    break;


                case 0xCF:
                    SET(A, 1);
                    break;
                case 0xC8:
                    SET(B, 1);
                    break;
                case 0xC9:
                    SET(C, 1);
                    break;
                case 0xCA:
                    SET(D, 1);
                    break;
                case 0xCB:
                    SET(E, 1);
                    break;
                case 0xCC:
                    SET(H, 1);
                    break;
                case 0xCD:
                    SET(L, 1);
                    break;
                case 0xCE:
                    tmp = gb->Read(HL);
                    SET(&tmp, 1);
                    gb->Write(HL, tmp);
                    break;
                    
                case 0xD7:
                    SET(A, 2);
                    break;
                case 0xD0:
                    SET(B, 2);
                    break;
                case 0xD1:
                    SET(C, 2);
                    break;
                case 0xD2:
                    SET(D, 2);
                    break;
                case 0xD3:
                    SET(E, 2);
                    break;
                case 0xD4:
                    SET(H, 2);
                    break;
                case 0xD5:
                    SET(L, 2);
                    break;
                case 0xD6:
                    tmp = gb->Read(HL);
                    SET(&tmp, 2);
                    gb->Write(HL, tmp);
                    break;


                case 0xDF:
                    SET(A, 3);
                    break;
                case 0xD8:
                    SET(B, 3);
                    break;
                case 0xD9:
                    SET(C, 3);
                    break;
                case 0xDA:
                    SET(D, 3);
                    break;
                case 0xDB:
                    SET(E, 3);
                    break;
                case 0xDC:
                    SET(H, 3);
                    break;
                case 0xDD:
                    SET(L, 3);
                    break;
                case 0xDE:
                    tmp = gb->Read(HL);
                    SET(&tmp, 3);
                    gb->Write(HL, tmp);
                    break;
                    
                case 0xE7:
                    SET(A, 4);
                    break;
                case 0xE0:
                    SET(B, 4);
                    break;
                case 0xE1:
                    SET(C, 4);
                    break;
                case 0xE2:
                    SET(D, 4);
                    break;
                case 0xE3:
                    SET(E, 4);
                    break;
                case 0xE4:
                    SET(H, 4);
                    break;
                case 0xE5:
                    SET(L, 4);
                    break;
                case 0xE6:
                    tmp = gb->Read(HL);
                    SET(&tmp, 4);
                    gb->Write(HL, tmp);
                    break;


                case 0xEF:
                    SET(A, 5);
                    break;
                case 0xE8:
                    SET(B, 5);
                    break;
                case 0xE9:
                    SET(C, 5);
                    break;
                case 0xEA:
                    SET(D, 5);
                    break;
                case 0xEB:
                    SET(E, 5);
                    break;
                case 0xEC:
                    SET(H, 5);
                    break;
                case 0xED:
                    SET(L, 5);
                    break;
                case 0xEE:
                    tmp = gb->Read(HL);
                    SET(&tmp, 5);
                    gb->Write(HL, tmp);
                    break;
                    
                case 0xF7:
                    SET(A, 6);
                    break;
                case 0xF0:
                    SET(B, 6);
                    break;
                case 0xF1:
                    SET(C, 6);
                    break;
                case 0xF2:
                    SET(D, 6);
                    break;
                case 0xF3:
                    SET(E, 6);
                    break;
                case 0xF4:
                    SET(H, 6);
                    break;
                case 0xF5:
                    SET(L, 6);
                    break;
                case 0xF6:
                    tmp = gb->Read(HL);
                    SET(&tmp, 6);
                    gb->Write(HL, tmp);
                    break;


                case 0xFF:
                    SET(A, 7);
                    break;
                case 0xF8:
                    SET(B, 7);
                    break;
                case 0xF9:
                    SET(C, 7);
                    break;
                case 0xFA:
                    SET(D, 7);
                    break;
                case 0xFB:
                    SET(E, 7);
                    break;
                case 0xFC:
                    SET(H, 7);
                    break;
                case 0xFD:
                    SET(L, 7);
                    break;
                case 0xFE:
                    tmp = gb->Read(HL);
                    SET(&tmp, 7);
                    gb->Write(HL, tmp);
                    break;
                    
                case 0x87:
                    RES(A, 0);
                    break;
                case 0x80:
                    RES(B, 0);
                    break;
                case 0x81:
                    RES(C, 0);
                    break;
                case 0x82:
                    RES(D, 0);
                    break;
                case 0x83:
                    RES(E, 0);
                    break;
                case 0x84:
                    RES(H, 0);
                    break;
                case 0x85:
                    RES(L, 0);
                    break;
                case 0x86:
                    tmp = gb->Read(HL);
                    RES(&tmp, 0);
                    gb->Write(HL, tmp);
                    break;


                case 0x8F:
                    RES(A, 1);
                    break;
                case 0x88:
                    RES(B, 1);
                    break;
                case 0x89:
                    RES(C, 1);
                    break;
                case 0x8A:
                    RES(D, 1);
                    break;
                case 0x8B:
                    RES(E, 1);
                    break;
                case 0x8C:
                    RES(H, 1);
                    break;
                case 0x8D:
                    RES(L, 1);
                    break;
                case 0x8E:
                    tmp = gb->Read(HL);
                    RES(&tmp, 1);
                    gb->Write(HL, tmp);
                    break;
                    
                case 0x97:
                    RES(A, 2);
                    break;
                case 0x90:
                    RES(B, 2);
                    break;
                case 0x91:
                    RES(C, 2);
                    break;
                case 0x92:
                    RES(D, 2);
                    break;
                case 0x93:
                    RES(E, 2);
                    break;
                case 0x94:
                    RES(H, 2);
                    break;
                case 0x95:
                    RES(L, 2);
                    break;
                case 0x96:
                    tmp = gb->Read(HL);
                    RES(&tmp, 2);
                    gb->Write(HL, tmp);
                    break;


                case 0x9F:
                    RES(A, 3);
                    break;
                case 0x98:
                    RES(B, 3);
                    break;
                case 0x99:
                    RES(C, 3);
                    break;
                case 0x9A:
                    RES(D, 3);
                    break;
                case 0x9B:
                    RES(E, 3);
                    break;
                case 0x9C:
                    RES(H, 3);
                    break;
                case 0x9D:
                    RES(L, 3);
                    break;
                case 0x9E:
                    tmp = gb->Read(HL);
                    RES(&tmp, 3);
                    gb->Write(HL, tmp);
                    break;
                    
                case 0xA7:
                    RES(A, 4);
                    break;
                case 0xA0:
                    RES(B, 4);
                    break;
                case 0xA1:
                    RES(C, 4);
                    break;
                case 0xA2:
                    RES(D, 4);
                    break;
                case 0xA3:
                    RES(E, 4);
                    break;
                case 0xA4:
                    RES(H, 4);
                    break;
                case 0xA5:
                    RES(L, 4);
                    break;
                case 0xA6:
                    tmp = gb->Read(HL);
                    RES(&tmp, 4);
                    gb->Write(HL, tmp);
                    break;


                case 0xAF:
                    RES(A, 5);
                    break;
                case 0xA8:
                    RES(B, 5);
                    break;
                case 0xA9:
                    RES(C, 5);
                    break;
                case 0xAA:
                    RES(D, 5);
                    break;
                case 0xAB:
                    RES(E, 5);
                    break;
                case 0xAC:
                    RES(H, 5);
                    break;
                case 0xAD:
                    RES(L, 5);
                    break;
                case 0xAE:
                    tmp = gb->Read(HL);
                    RES(&tmp, 5);
                    gb->Write(HL, tmp);
                    break;
                    
                case 0xB7:
                    RES(A, 6);
                    break;
                case 0xB0:
                    RES(B, 6);
                    break;
                case 0xB1:
                    RES(C, 6);
                    break;
                case 0xB2:
                    RES(D, 6);
                    break;
                case 0xB3:
                    RES(E, 6);
                    break;
                case 0xB4:
                    RES(H, 6);
                    break;
                case 0xB5:
                    RES(L, 6);
                    break;
                case 0xB6:
                    tmp = gb->Read(HL);
                    RES(&tmp, 6);
                    gb->Write(HL, tmp);
                    break;


                case 0xBF:
                    RES(A, 7);
                    break;
                case 0xB8:
                    RES(B, 7);
                    break;
                case 0xB9:
                    RES(C, 7);
                    break;
                case 0xBA:
                    RES(D, 7);
                    break;
                case 0xBB:
                    RES(E, 7);
                    break;
                case 0xBC:
                    RES(H, 7);
                    break;
                case 0xBD:
                    RES(L, 7);
                    break;
                case 0xBE:
                    tmp = gb->Read(HL);
                    RES(&tmp, 7);
                    gb->Write(HL, tmp);
                    break;
            }
            break;
            
        case 0x27:
            DAA();
            break;


        case 0x2F:
            CPL();
            break;


        case 0x3F:
            CCF();
            break;


        case 0x37:
            SCF();
            break;


        case 0x00:
            break;


        case 0x76:
            HALT();
            break;


        case 0x10:
            STOP();
            break;


        case 0xF3:
            DI();
            break;
        case 0xFB:
            EI();
            break;


        case 0x07:
            RLCA();
            break;


        
        case 0x17:
            RLA();
            break;


        case 0x0F:
            RRCA();
            break;


        case 0x1F:
            RRA();
            break;


        case 0xC3:
            JP(true);
            break;


        case 0xC2:
            JP(!Zero);
            break;
        case 0xCA:
            JP(Zero);
            break;
        case 0xD2:
            JP(!Carry);
            break;
        case 0xDA:
            JP(Carry);
            break;


        case 0xE9:
            PC = HL;
            gb->SyncCycles(-4);
            break;


        case 0x18:
            JR(true);
            break;


        case 0x20:
            JR(!Zero);
            break;
        case 0x28:
            JR(Zero);
            break;
        case 0x30:
            JR(!Carry);
            break;
        case 0x38:
            JR(Carry);
            break;


        case 0xCD:
            CALL(true);
            break;


        case 0xC4:
            CALL(!Zero);
            break;
        case 0xCC:
            CALL(Zero);
            break;
        case 0xD4:
            CALL(!Carry);
            break;
        case 0xDC:
            CALL(Carry);
            break;


        case 0xC7:
            RST(0);
            break;


        case 0xCF:
            RST(0x8);
            break;


        case 0xD7:
            RST(0x10);
            break;


        case 0xDF:
            RST(0x18);
            break;


        case 0xE7:
            RST(0x20);
            break;


        case 0xEF:
            RST(0x28);
            break;


        case 0xF7:
            RST(0x30);
            break;


        case 0xFF:
            RST(0x38);
            break;


        case 0xC9:
            RET(true);
            break;


        case 0xC0:
            RET(!Zero);
            break;
        case 0xC8:
            RET(Zero);
            break;
        case 0xD0:
            RET(!Carry);
            break;
        case 0xD8:
            RET(Carry);
            break;


            //RETI
        case 0xD9:
            RETI();
            break;


        default:
            throw new std::exception();
    }
}





void CPU::ADD(byte value)
{
    Substract = false;
    HalfCarry = (((*A & 0xF) + (value & 0xF)) & 0x10) == 0x10;
    Carry = ((*A + value) & 0x100) == 0x100;
    *A += value;
    Zero = (*A) == 0;
}

void CPU::ADC(byte value)
{
    byte carry = Carry ? 1 : 0;
    Substract = false;
    HalfCarry = (((*A & 0xF) + (value & 0xF) + carry) & 0x10) == 0x10;
    Carry = ((*A + value + carry) & 0x100) == 0x100;
    *A += value + carry;
    Zero = (*A) == 0;
}

void CPU::SUB(byte value)
{
    Substract = true;
    HalfCarry = (*A & 0xF) < (value & 0xF);
    Carry = (*A & 0xFF) < (value & 0xFF);
    *A -= value;
    Zero = (*A) == 0;
}

void CPU::SBC(byte value)
{
    byte carry = Carry ? 1 : 0;
    Substract = true;
    HalfCarry = (*A & 0xF) < ((value & 0xF) + carry);
    Carry = (*A & 0xFF) < ((value & 0xFF) + carry);
    *A -= value + carry;
    Zero = (*A) == 0;
}

void CPU::INC(byte* value)
{
    Substract = false;
    HalfCarry = (*value & 0xF) == 0xF;
    (*value)++;
    Zero = *value == 0;
}

void CPU::DEC(byte* value)
{
    Substract = true;
    HalfCarry = (*value & 0xF) == 0;
    (*value)--;
    Zero = *value == 0;
}

void CPU::ADD(ushort value)
{
    Substract = false;
    HalfCarry = (((HL & 0xFFF) + (value & 0xFFF)) & 0x1000) == 0x1000;
    Carry = (((HL & 0xFFFF) + (value & 0xFFFF)) & 0x10000) == 0x10000;
    HL += value;
    gb->SyncCycles(4);
}

void CPU::ADD_SP_n()
{
    SP = ADDsbyteToSP();
}

//сделать попроще
ushort CPU::ADDsbyteToSP()
{
    Zero = false;
    Substract = false;
    tmp = gb->Read(PC);
    PC++;
    ushort newSP = SP;
    char* sb = (char*)&tmp;
    newSP += *sb;
    
    if (*sb < 0)
    {
        HalfCarry = (newSP & 0xF) <= (SP & 0xF);
        Carry = (newSP & 0xFF) <= (SP & 0xFF);
    }
    else
    {
        HalfCarry = (((SP & 0xF) + (tmp & 0xF)) & 0x10) == 0x10;
        Carry = (((SP & 0xFF) + (tmp & 0xFF)) & 0x100) == 0x100;
    }
    gb->SyncCycles(8);
    return newSP;
}



void CPU::AND(byte value)
{
    HalfCarry = true;
    Substract = false;
    Carry = false;
    *A &= value;
    Zero = (*A) == 0;
}

void CPU::OR(byte value)
{
    HalfCarry = false;
    Substract = false;
    Carry = false;
    *A |= value;
    Zero = (*A) == 0;
}

void CPU::XOR(byte value)
{
    HalfCarry = false;
    Substract = false;
    Carry = false;
    *A ^= value;
    Zero = (*A) == 0;
}

void CPU::CP(byte value)
{
    Substract = true;
    HalfCarry = (*A & 0xF) < (value & 0xF);

    if (value > *A)
        Carry = true;
    else
        Carry = false;

    if (*A == value)
        Zero = true;
    else
        Zero = false;
}

void CPU::DAA()
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

void CPU::HALT()
{
    bool halt = gb->EnterHALTMode();
    if (!halt) {
        gb->Clock();
        PC--;
    }
}

void CPU::STOP()
{
    if (gb->Read(PC) == 0x00)
    {
        gb->Stop = true;
        PC++;
        gb->SyncCycles(-4);
    }
}

void CPU::SWAP(byte* value)
{
    Zero = (*value) == 0;
    HalfCarry = false;
    Substract = false;
    Carry = false;
    *value = (*value & 0xF0) >> 4 | (*value) << 4;
}

void CPU::CPL()
{
    *A = ~(*A);
    Substract = true;
    HalfCarry = true;
}

void CPU::CCF()
{
    Substract = false;
    HalfCarry = false;
    Carry = !Carry;
}

void CPU::SCF()
{
    Substract = false;
    HalfCarry = false;
    Carry = true;
}



void CPU::RLC(byte* value)
{
    Carry = ((*value >> 7) & 1) == 1;
    *value = *value >> 7 | (*value) << 1;
    Zero = (*value) == 0;
    HalfCarry = false;
    Substract = false;
}

void CPU::RL(byte* value)
{
    byte temp = (*value);
    *value = *value << 1 | (Carry ? 1 : 0);
    Carry = ((temp >> 7) & 1) == 1;
    Zero = (*value) == 0;
    HalfCarry = false;
    Substract = false;
}


void CPU::RRC(byte* value)
{
    Carry = (*value & 1) == 1;
    *value = (*value >> 1) | ((*value & 1) << 7);
    Zero = (*value) == 0;
    HalfCarry = false;
    Substract = false;
}


void CPU::RR(byte* value)
{
    byte temp = (*value);
    *value = *value >> 1 | (Carry ? 0x80 : 0);
    Carry = (temp & 1) == 1;
    Zero = (*value) == 0;
    HalfCarry = false;
    Substract = false;
}



void CPU::RLCA()
{
    Carry = ((*A >> 7) & 1) == 1;
    *A = *A >> 7 | (*A) << 1;
    Zero = false;
    HalfCarry = false;
    Substract = false;
}

void CPU::RLA()
{
    byte temp = (*A);
    *A = *A << 1 | (Carry ? 1 : 0);
    Carry = ((temp >> 7) & 1) == 1;
    Zero = false;
    HalfCarry = false;
    Substract = false;
}

void CPU::RRCA()
{
    Carry = (*A & 1) == 1;
    *A = (*A >> 1) | ((*A & 1) << 7);
    Zero = false;
    HalfCarry = false;
    Substract = false;
}


void CPU::RRA()
{
    byte temp = (*A);
    *A = *A >> 1 | (Carry ? 0x80 : 0);
    Carry = (temp & 1) == 1;
    Zero = false;
    HalfCarry = false;
    Substract = false;
}



void CPU::SLA(byte* value)
{
    Carry = (*value & 0x80) == 0x80;
    *value = *value << 1;
    Zero = (*value) == 0;
    HalfCarry = false;
    Substract = false;
}


void CPU::SRA(byte* value)
{
    Carry = (*value & 1) == 1;
    *value = (*value & 0x80) | (*value) >> 1;
    Zero = *value == 0;
    HalfCarry = false;
    Substract = false;
}


void CPU::SRL(byte* value)
{
    Carry = (*value & 1) == 1;
    *value = *value >> 1;
    Zero = (*value) == 0;
    HalfCarry = false;
    Substract = false;
}


void CPU::BIT(byte bit, byte value)
{
    Substract = false;
    HalfCarry = true;
    Zero = true;
    if ((value >> bit) & 1) {
        Zero = false;
    }
}

void CPU::SET(byte* value, byte bit)
{
    *value |= 1 << bit;
}


void CPU::RES(byte* value, byte bit)
{
    *value &= ~(1 << bit);
}



void CPU::PUSH(byte h, byte l)
{
    gb->Write(--SP, h);
    gb->Write(--SP, l);
    gb->SyncCycles(8);
}


void CPU::POP(byte* h, byte* l)
{
    *l = gb->Read(SP);
    SP++;
    *h = gb->Read(SP);
    SP++;
    gb->SyncCycles(4);
}


void CPU::JP(bool flag)
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


void CPU::JR(bool flag)
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


void CPU::CALL(bool flag)
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


void CPU::RST(ushort addr)
{
    SP -= 2;
    gb->WriteWord(SP, PC);
    PC = addr;
    gb->SyncCycles(4);
}


void CPU::RET(bool flag)
{
    if (flag)
    {
        PC = gb->ReadWord(SP);
        SP += 2;
        gb->SyncCycles(4);
    }
    gb->SyncCycles(4);
}


void CPU::RETI()
{
    PC = gb->ReadWord(SP);
    SP += 2;
    gb->IME = true;
}

//Used by interrupts to save previous Program Counter
//and jump to it's start address
void CPU::Interrupt(ushort addr)
{
    SP -= 2;
    gb->WriteWord(SP, PC);
    PC = addr;
}


void CPU::DI()
{
    Clock();
    gb->IME = false;
}


void CPU::EI()
{
    Clock();
    gb->IME = true;
}

