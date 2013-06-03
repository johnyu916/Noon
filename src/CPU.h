#ifndef __NOON_CPU_H
#define __NOON_CPU_H
#include <string>
#include <vector>
#include "Types.h"

using namespace std;

//have data memory and instruction memory
namespace Noon{
    class Bit{
        public:
            Bit();
            Bit(bool val);
            bool value(){ return val_;}
            void value(bool val){ val_=val;}
        private:
            bool val_;
    };
    class Instruction{
        public:
            Instruction();
            Instruction(U32 read, U32 branchIfOne); //just branch based on read value, leave location as is
            Instruction(U32 read, U32 branch, bool writeBoth);
            Instruction(U32 read, U32 branchbranch, bool writeTrue, bool writeFalse);
            string info();
            U32 read(){return read_;}
            void read(U32 read){read_=read;}
            U32 branch(){return branch_;}
            void branch(U32 read){branch_=read;}
            bool writeIfOne(){return writeIfOne_;}
            void writeIfOne(bool w){ writeIfOne_ = w;}
            bool writeElse(){return writeElse_;}
            void writeElse(bool w){ writeElse_ = w;}

        private:
            U32 read_;
            U32 branch_;
            bool writeIfOne_, writeElse_;
    };

    class CPU{
        public:
            CPU(U32 dataSize, vector<Instruction> insns);
            ~CPU();
            vector<Bit> &bits(){ return bits_;}
            vector<Instruction> &instructions(){ return insns_;}
            U32 instructionIndex(){return insnIdx_;}
            void instructionIndex(U32 idx){ insnIdx_ = idx;}
        private:
            vector<Bit> bits_;
            vector<Instruction> insns_;
            U32 insnIdx_;
    };

    void CPURun(CPU &cpu);
    void CPUBitsOutput(CPU &cpu);
}

#endif
