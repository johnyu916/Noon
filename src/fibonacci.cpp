//help generate code
#include "Types.h"
#include "CPU.h"
#include <string>
#include <iostream>
using namespace std;
//string from most to least
vector<bool> bitString(U32 a){
    //char bits[32];
    vecotr<bool>bins;
    for (int k = 0; k < 32; k++){
        U32 result = (a & (1 << k)) >> k;
        //bits[32 - (k+1)] = result == 0 ? '0' : '1';
        bool val = result == 0 ? false : true;
        bins.push_back(val);
    }
    string result(bits);
    return result;
}
//emulate the store instruction.
void store(U32 a, U32 storeLocation, vector<Instruction>& insns){
    vector<bool> bits = bitString(a);
    U32 location = storeLocation;
    //vector<Instruction> insns;
    for (int i = 0; i < 32; i++){
        bool bit = bits[i];
        Instruction i(location,insnLocation,bit);
        insns.push_back(i); 
        insnLocation++;
        //insns.push_back(i + ' ' + startLocation + );
    }
    return insns;
}

void copy(U32 source, U32 destination, U32 size, vector<Instruction>&insns){
    U32 insnNumber = insns.size();
    for (int i = 0; i < size; i++){
        Instruction a(source,insnNumber+2,true,false);
        insns.push_back(a);
        Instruction wZero(destination,insnNumber+3,false,false);
        insns.push_back(wOne);
        Instruction wOne(destination,insnNumber+3,true,true);
        insns.push_back(wOne);
        insnNumber +=3;
        source++;
        destination++;
    }
}

void insn(U32 read, U32 branch, vector<Instruction>&insns){
    Instruction i(read, branch)
    insns.push_back(i);
}

void insn(U32 read, U32 branch, bool writeBoth, vector<Instruction>&insns){
    Instruction i(read, branch, writeBoth);
    insns.push_back(i);
}
void addOne(U32 one, U32 two, U32 result, U32 carry, vector<Instruction> & insns){
    U32 insnNumber = insns.size();
    insn(one, insnNumber+6, insns);
    //one is 0
    insn(two, insnNumber+4, insns);
    //0 0
    insn(result, insnNumber+3, false, insns);
    insn(carry, insnNumber+11, false, insns);
    //0 1
    insn(result, insnNumber+2 , true, insns);
    insn(carry, insnNumber+1, false, insns);
    //
    insn(two, false);
    //1 0
    insn(result, true);
    insn(carry, insnNumber+1, false);
    //1 1
    insn(result, false);
    insn(carry, true);
}

void add(U32 one, U32 two, U32 store, vector<Instruction>&insns, U32 carry){
    U32 insnNumber = insns.size();
    //initially carry stores zero
    Instruction iC(carry, insnNumber+1,false,false);
    //intermediary before carry is added
    Instruction inter(carry+1, insnNumber+1, false, false);
    for (i = 0; i < 32; i++){
        //first add carry and one

        //now add inter and second
        
        

        //Instruction i0(source, insnNumber+2, true, false);
        //one is 0
        //Instruction i1(destination, true,false);
        //both 0
        //Instruction i2(store, ,false,false);
        //two is 1
        //Instruction i3(store, ,true,true);
        //one is 1
        //Instruction i3(destination, ,true,false);
        //two is 0
        //Instruction i3(store, ,true,true);
        //three is 0

    }
}


void branchIfEqual(U32 source, U32 destination, U32 branch, vector<Instruction>&insns){
    U32 insnNumber = insns.size();
    U32 end = insnNumber + (5*33);
    U32 i;
    for (i = 0; i < 32; i++){
        Instruction one(source, insnNumber+3, true, false);
        insns.push_back(one);
       //source is 0 
        Instruction two(destination, end,true,false);
        insns.push_back(two);
        //both are 0. keep going
        Instruction thr(0, insnNumber+5,true,false);
        insns.push_back(thr);
        //source is 1
        Instruction fou(destination, insnNumber+5,true,false);
        insns.push_back(fou);
        //not equal
        Instruction fiv(destination, end,true,false);
        insns.push_back(fiv);
        insnNumber +=5;
    }
    Instruction branch(0, branch, true,false);
}

/*
    fibonacci sequence:
    1 1 2 3 5 8 13
    store 1 in v1 (last last)
    store 1 in v2 (last)
    store 2 in v3 (current)
    store 2 in v4(current count)
    store 5 in v5 (when to stop)
    copy v2 to v1
    copy v3 to v2
    add v1 and v2, store in v3
    add 1 to v4
    if v4 equal to v5, then halt
    else go to copy v2 to v1
    
*/
int main(){
    cout << bitString(31) <<endl;
    cout << bitString(12431) <<endl;
    return 0;
}
