#ifndef __NOON_PARSER_H
#define __NOON_PARSER_H

#include "CPU.h"
#include <string>
//read text file and spit out machine instructions
//using namespace std;
namespace Noon{
    int instructions(string filename, vector<Instruction>& insns);
}

#endif
