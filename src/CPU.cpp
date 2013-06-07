#include "CPU.h"

#include <fstream>
#include <sstream>

#include "Utilities.h"
namespace Noon{
    U32 index(bool val){
        if (val) return 1;
        else return 0;
    }
    /*
    Bit::Bit():val_(false){}
    Bit::Bit(bool val):val_(val){}
    */
    
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
        sout <<read_<<" "<<branch_<<" "<<writeIfOne_ <<" "<<writeElse_;
        return sout.str();
    }
    //size in bits but needs to be multiple of 8
    CPU::CPU(U32 dataSize,vector<Instruction> insns){
        insns_ = insns;
        for (int a = 0; a < dataSize; a++){
            bits_.push_back(Bit());
        }
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
            cerr <<"Invalid instruction index: "<<idx<<endl;
            return 2;
        };
        Instruction insn = insns[idx];
        U32 readIdx = insn.read();
        U32 branch = insn.branch();
        bool writeIfOne = insn.writeIfOne();
        bool writeElse = insn.writeElse();
        bool write;
        debug("Running number: "<<idx<<" insn: "<<insn.info());
        
        Bit data = cpu.bits()[readIdx];
        if (data){
            idx = branch;
            write = writeIfOne;
        }
        else{
            idx++;
            write = writeElse;
        }
        cpu.instructionIndex(idx);
        cpu.bits()[readIdx] = write;
        return 0;
    }
    void CPURun(CPU &cpu){
        U32 steps = 10000;
        while (true){
            debug("Cycles left: " <<steps<<" ");
            if (0 != CPURunCycle(cpu)) break;
            //at every run print the state
            if (steps % 8 == 0) CPUBitsOutput(cpu);

            steps--;
            if (steps == 0) break;
        }
    }
    void CPUBitsOutput(CPU &cpu){
        vector<Bit>bits = cpu.bits();
        for (int a = 0; a < bits.size(); a++){
            if (a % 8 == 0) cout << endl;
            else cout << " ";
            cout << bits[a];
        }
    }
}
