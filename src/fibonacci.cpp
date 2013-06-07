//help generate code
#include "Types.h"
#include "CPU.h"
#include "Settings.h"
#include <string>
#include <iostream>
using namespace std;
using namespace Noon;

U32 one = 48;

// Return a boolean vector representation of string. vector[0] is least significant, vector[31] is most significant
vector<bool> bitVector(U32 a, U32 size){
    //char bits[32];
    vector<bool>bins;
    for (U32 k = 0; k < size; k++){
        U32 result = (a & (1 << k)) >> k;
        //bits[32 - (k+1)] = result == 0 ? '0' : '1';
        bool val = result == 0 ? false : true;
        bins.push_back(val);
    }
    //string result(bits);
    /*
    cout <<"bits print"<<endl;
    for (U32 k = 0; k < size; k++){
        cout << bins[k] << " "<<endl;
    }
    cout <<"bits print end"<<endl;
    */
    return bins;
}
//construct write something to read. 1 instruction
void write(U32 read, bool writeBoth, vector<Instruction>&insns){
    U32 length = insns.size();
    Instruction i(read, length+1, writeBoth);
    insns.push_back(i);
}

//write and then branch. 2 insns
void write(U32 read, U32 branch, bool writeBoth, vector<Instruction>&insns){
    Instruction i(read, insns.size()+1, writeBoth);
    insns.push_back(i);
    Instruction j(one, branch, true,false);
    insns.push_back(j);
    
}

// the store instruction. append instructions to insns
// store a at storelocation.
void store(U32 a, U32 storeLocation, U32 size, vector<Instruction>& insns){
    vector<bool> bits = bitVector(a, size);
    U32 location = storeLocation;
    U32 insnLocation = insns.size();

    Settings::instance().verbose(true);
    //vector<Instruction> insns;
    for (int i = 0; i < size; i++){
        bool bit = bits[i];
        write(location, bit, insns);
        insnLocation++;
        location++;
        //insns.push_back(i + ' ' + startLocation + );
    }
}

//copy from source location to destination.
//for size bits. append to insns
void copy(U32 source, U32 destination, U32 size, vector<Instruction>&insns){
    U32 insnNumber = insns.size();
    for (int i = 0; i < size; i++){
        Instruction a(source,insnNumber+3,true,false);
        insns.push_back(a);
        write(destination,insnNumber+5,false,insns);
        write(destination,insnNumber+5,true,insns);

        insnNumber +=5;
        source++;
        destination++;
    }
}

//read, and branch if one, else branch 1
//also, write one or zero.
//read and branch if one, else go 1. 
//if one, then write one or zero. else same.
//j

//construct branch if read is one
void branch(U32 read, U32 branch, vector<Instruction>&insns){
    Instruction i(read, branch);
    insns.push_back(i);
}


void addOne(U32 one, U32 two, U32 three, U32 result, U32 carry, vector<Instruction> & insns){
    U32 insnNumber = insns.size();
    branch(one, insnNumber+16, insns);
    //one is 0
    branch(two, insnNumber+9, insns);
    //0 0
    branch(three, insnNumber+6, insns);
    //0 0 0
    write(result, false, insns);
    write(carry, insnNumber+31, false, insns);
    //0 0 1
    write(result, true, insns);
    write(carry, insnNumber+31, false, insns);
    //0 1
    branch(three, insnNumber+13, insns);
    //0 1 0
    write(result, true, insns);
    write(carry, insnNumber+31, false, insns);
    //0 1 1
    write(result, false, insns);
    write(carry, insnNumber+31, true, insns);

    insnNumber += 16;
    //1
    branch(two, insnNumber+8, insns);
    //1 0
    branch(three, insnNumber+5, insns);
    //1 0 0
    write(result, true, insns);
    write(carry, insnNumber+15, false, insns);
    //1 0 1
    write(result, false, insns);
    write(carry, insnNumber+15, true, insns);
    //1 1
    branch(three, insnNumber+12, insns);
    //1 1 0
    write(result, false, insns);
    write(carry, insnNumber+15, true, insns);
    //1 1 1
    write(result, true, insns);
    write(carry, insnNumber+15, true, insns);
}

//add at location one and location two, store in store. need room to store the carry
void add(U32 one, U32 two, U32 store, U32 size, vector<Instruction>&insns, U32 carry){
    U32 insnNumber = insns.size();
    //initially carry stores zero
    write(carry, false, insns);
    for (int i = 0; i < size; i++){
        //first add carry and one
        
        //now add inter and second
        addOne(carry, one, two, store, carry, insns);
        one += 1;
        two +=1;
        store +=1;

    }
}

// branch if source is equal to destination. their sizes are size
void branchIfEqual(U32 source, U32 destination, U32 size, U32 branch, vector<Instruction>&insns){
    U32 insnNumber = insns.size();
    U32 end = insnNumber + (5*size)+1;
    U32 i;
    for (i = 0; i < size; i++){
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

        source++;
        destination++;
    }
    //all equal. branch
    Instruction insn(one, branch, true,false);
    insns.push_back(insn);
    return;
}

/*
    fibonacci sequence:
    1 1 2 3 5 8 13
    store 1 in v1 (last last)
    store 1 in v2 (last)
    store 2 in v3 (current)
    store 3 in v4(current count)
    store 5 in v5 (when to stop)
    copy v2 to v1
    copy v3 to v2
    add v1 and v2, store in v3
    add 1 to v4
    if v4 equal to v5, then halt
    else go to copy v2 to v1
    
    2 improvements:
    1. run in parallel
*/
int main(){
    //cout << bitVector(31) <<endl;
    //cout << bitVector(12431) <<endl;
    vector<Instruction> insns;

    store(1, one,8, insns);
    //store(78, 0, 8, insns);
    store(1, 0, 8, insns);
    store(1, 8, 8, insns);
    store(2, 16, 8, insns);
    store(3, 24, 8, insns);
    store(11, 32, 8, insns);
   
    //temporary
    //store(0, 65, 1, insns);
    U32 startOfCopy = insns.size();
    copy(8, 0, 8, insns);
    
    copy(16, 8, 8, insns);
    
    add(0,8,16, 8, insns,40);
    
    
    add(24,one,56, 8, insns,64);
    
    copy(56,24,8,insns);
    branchIfEqual(24,32,8, 1024, insns);
    
    branch(one, startOfCopy,insns);
    cout <<"num insns: "<<insns.size()<<endl;
    
    //now lets run this
    U32 memorySize = 66;
    CPU cpu(memorySize, insns);
    CPURun(cpu);
   
    for (int a = 0; a < memorySize; a++){
        if (a % 8 == 0) cout << endl;
        else cout << " ";
        cout << cpu.bits()[a];
    }

    return 0;
}
