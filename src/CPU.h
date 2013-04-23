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
            Instruction(bool read, bool offset, bool write);
            string info();
            bool read(){return read_;}
            void read(bool read){read_=read;}
            bool branch(){return branch_;}
            void branch(bool read){branch_=read;}
            bool write(){return write_;}
            void write(bool read){write_=read;}

        private:
            bool read_;
            bool branch_;
            bool write_;
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
