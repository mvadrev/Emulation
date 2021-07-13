/******************************************************************************
Simple 6502 implementation with single instruction
*******************************************************************************/

#include <iostream>
#include<stdlib.h>

using namespace std;

// Declare word and Byte
   using Byte = unsigned char;
   using Word = unsigned short; 
   using u32 = unsigned int;

// Declare memory struct
struct Mem {
    static constexpr u32 MAX_MEM = 1024 * 64;
    Byte Data[MAX_MEM];
    
    void initialize() {
        
        for(u32 i=0; i<MAX_MEM; i++) {
            Data[i] = 0;
        }
    }
     Byte operator[] (u32 Address) const {
            return Data[Address];
        }
        
    // Write Byte into Memory
    Byte& operator[](u32 Address) {
    return Data[Address];
}
};

// Define CPU
struct CPU {
   Word PC;
   Word SP; 
   Byte A, X, Y;
   
   // Processor status flags
   Byte C : 1; // Carry flag
   Byte Z : 1; // Zero flag
   Byte I : 1; // Interrupt disable
   Byte D : 1; // Decimal mode
   Byte B : 1; // Break command
   Byte V : 1; // Overflow flag
   Byte N : 1; // Negative flag
   
   // CPU Reset
void Reset(Mem& memory) {
    // Reset routine for 6502
    PC = 0xFFFC; // Reset program counter to #FFFC
    C, Z, I, D, B, V, N = 0; // Reset decimanl mode
    SP = 0x0100;
    A = X = Y = 0;
    memory.initialize();
};
// Fetch
Byte Fetch(u32& Cycles, Mem& Memory) {
    Byte data = Memory[PC];
    PC++;
    Cycles--;
    return data;
};


// Opcodes

static constexpr Byte
INS_LDA_IM = 0xA9;

// Execute
void Execute(u32 Cycles, Mem& memory) {
    while(Cycles > 0) {
        Byte Ins = Fetch(Cycles, memory);
        switch(Ins)
        {
            case INS_LDA_IM:
            {
                cout << "Instructions is INS_LDA_IM" <<  endl;
                Byte Value = Fetch(Cycles, memory);
                A = Value;
                Z = (A == 0);
                N = (A & 0b10000000) > 0;
            } break;
            
            default:
            {
                cout<<"Illegal unknown instruction" << endl;
            }
        }
    }
};
};

// Main Loop
int main()
{
    cout<<"Initializing software emulated CPU.." << endl;
    Mem mem;
    CPU cpu;
    cpu.Reset(mem);
    mem[0xFFFC] = CPU::INS_LDA_IM;
    cpu.Execute(2, mem);
    cout<<"done..";
    return 0;
}
