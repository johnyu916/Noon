//help generate code
#include "Types.h"
#include <string>
#include <iostream>
using namespace std;
//string from most to least
string bitString(U32 a){
    char bits[32];
    for (int k = 0; k < 32; k++){
        U32 result = (a & (1 << k)) >> k;
        bits[32 - (k+1)] = result == 0 ? '0' : '1';
    }
    string result(bits);
    return result;
}
//emulate the store instruction.
list<string> store(U32 a, U32 startLocation){
    string aString = bitString(a);
    list<string> insns;
    for (int i = 0; i < 32; i++){
        string i = aString[i];
        insns.push_back(i + ' ' + startLocation
    }
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
