
//memory stores 0 and 1. hmm a bit map
#include <iostream>
#include <vector>
#include <unistd.h>

#include "CPU.h"
#include "Parser.h"
#include "Settings.h"
#include "Utilities.h"

using namespace Noon;
using namespace std;

void printHelp(){
    cout <<"Usage: noon -v -h <script>"<<endl;
}

int main(int argc, char *argv[]){
    char c;
    while ((c = getopt(argc, argv, "vh")) != -1){
        switch(c){
            case 'h':
                printHelp();
                return 0;
                break;
            case 'v':
                Settings::instance().verbose(true);
                break;
            default:
                printHelp();
                return 100;
        }
    }

    if (optind >= argc){
        printHelp();
        return 1;
    }

    vector<Instruction>insns;
    debug("Hello");
    if (0!=instructions(argv[optind],insns)){
        cerr <<"Failed to read instructions from: "<<argv[optind]<<endl;
        return 2;
    }
    
    CPU cpu(256, insns);
    //feed some data into memory

    CPURun(cpu);
    CPUBitsOutput(cpu);
        
    return 0;
}
