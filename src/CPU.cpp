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
    
    Instruction::Instruction():read_(0),branch_(0),write_(false){

    }
    
    Instruction::Instruction(U32 read, U32 offset, bool write):read_(read),branch_(offset),write_(write){
        
    }
    string Instruction::info(){
        ostringstream sout;
        sout <<read_<<" "<<branch_<<" "<<write_;
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
        bool write = insn.write();

        debug("Running instruction: "<<insn.info());
        
        U32 readIdx = index(read);
        Bit bit = cpu.bits()[readIdx];
        bool data = bit.value();
        if (data) idx++;
        else{
            if (branch){
                if (idx == 0) idx = 2;
                else idx = 0;
            }
            else idx++;
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
