/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

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
        };
        
    };
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

// Execute
void Execute(u32 Cycles, Mem& memory) {
    cout<<"Executing instructions...";
    while(Cycles < 0) {
        Byte Ins = Fetch(Cycles, memory);
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
    cpu.Execute(2, mem);
    return 0;
}
