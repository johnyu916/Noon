#include "CPU.h"

#include <fstream>
#include <sstream>

#include "Utilities.h"
namespace Noon{
    U32 index(bool val){
        if (val) return 1;
        else return 0;
    }

    Bit::Bit():val_(false){}
    Bit::Bit(bool val):val_(val){}
    
    Instruction::Instruction():read_(0),branch_(0),writeIfOne_(false), writeElse_(false){

    }
    Instruction::Instruction(U32 read, U32 offset):read_(read),branch_(offset),writeIfOne_(true), writeElse_(false){
    }

    
    Instruction::Instruction(U32 read, U32 offset, bool writeBoth):read_(read),branch_(offset),writeIfOne_(writeBoth), writeElse_(writeBoth){
        
    }
    Instruction::Instruction(U32 read, U32 offset, bool writeTrue, bool writeFalse):read_(read),branch_(offset),writeIfOne_(writeTrue), writeElse_(writeFalse){
    }
    string Instruction::info(){
        ostringstream sout;
        sout <<read_<<" "<<branch_<<" "<<writeIfOne_, writeElse_;
        return sout.str();
    }
    //size in bits but needs to be multiple of 8
    CPU::CPU(U32 dataSize,vector<Instruction> insns){
        insns_ = insns;
        bits_.push_back(Bit());
        bits_.push_back(Bit());
        insnIdx_ = 0;
        //insns_ = new Instruction[20];
        
    }

    CPU::~CPU(){
        //delete data_;
        //delete insns_;
    }
    int CPURunCycle(CPU &cpu){
        vector<Instruction> insns = cpu.instructions();
        U32 idx = cpu.instructionIndex();
        if (idx >= insns.size()){
            if (idx == insns.size()) return 1;
            else{
                cerr <<"Invalid instruction index: "<<idx<<endl;
                return 2;
            }
        };
        Instruction insn = insns[idx];
        U32 read = insn.read();
        U32 branch = insn.branch();
        bool writeIfOne = insn.writeIfOne();
        bool writeElse = insn.writeElse();
        bool write;
        debug("Running instruction: "<<insn.info());
        
        U32 readIdx = index(read);
        Bit bit = cpu.bits()[readIdx];
        bool data = bit.value();
        if (data){
            idx = branch;
            write = writeIfOne;
        }
        else{
            write = writeElse;
        }
        cpu.instructionIndex(idx);
        cpu.bits()[readIdx] = write;
        return 0;
    }
    void CPURun(CPU &cpu){
        while (true){
            if (0 != CPURunCycle(cpu)) break;
        }
    }
    void CPUBitsOutput(CPU &cpu){
        ofstream stream("data");
        vector<Bit>bits = cpu.bits();
        for (int a = 0; a < bits.size(); a++){
            stream << bits[a].value()<<endl;
        }
        stream.close();
    }
}
