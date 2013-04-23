#include "Parser.h"

#include <fstream>
#include <iostream>
#include <list>
#include <sstream>

#include "Utilities.h"

namespace Noon{
    void tokenize(string line, list<string>&tokens);
    int binary(string s, bool&bin){
        if (s == "0") bin = false;
        else if (s == "1") bin = true;
        else{
            cerr <<"Invalid string: "<<s<<endl;
            return 4;
        }
        return 0;
    }
    
    //return less than 0 if okay to keep reading next line
    //return greater than 0 if should stop immediately
    int insnFromLine(string line, Instruction &insn){
        list<string> tokens;
        tokenize(line, tokens);

        int size = tokens.size();
        if (size == 0) return -1;
        string first = tokens.front();
        tokens.pop_front();
        if (first[0] == '#') return -2;
        if (size != 3){
            cerr << "3 strings needed, but size: " << size << "for string"<<line<< endl;
            return 4;
        }
        
        string second = tokens.front();
        tokens.pop_front();
        string third = tokens.front();
        tokens.pop_front();
        bool read, offset, write;
        
        if (0 != binary(first, read) || 0 != binary(second, offset) || 0 != binary(third, write)){
            cerr << "line should only have 0 and 1s but doesnt: "<<line<<endl;
            return 5;
        }
        insn.read(read);
        insn.branch(offset);
        insn.write(write);

        return 0;
    }

    void tokenize(string line, list<string>&tokens){
        //parse 3 numbers
        line.erase(0, line.find_first_not_of(" "));
        line.erase(line.find_last_not_of(" \n\r\t")+1);
        if (line.size() == 0) return;
        
        istringstream stream(line);
        while(stream.good()){
            string token;
            stream >> token;
            tokens.push_back(token);
        }
    }

    int instructions(string filename, vector<Instruction>& insns){
        string line;
        //open file, then read line by line, and construct insn and append to insn
        ifstream stream(filename.c_str());
        if (!stream.is_open()){
            cerr <<"Unable to open script: "<<filename<<endl;
            return 2;
        }

        while (stream.good()){
            getline(stream,line);
            Instruction insn;
            int status = insnFromLine(line, insn);
            if (status > 0){
                cerr <<"Invalid instruction: "<<line<<endl;
                return 3;
            }
            else if (status == 0){
                debug("Adding instruction: "<<insn.info());
                insns.push_back(insn);
            }
            //continue
        }
        return 0;
    }
}
