Noon
======

A simulator for a simple computer processor


Build:
    make

Usage:
    ./noon -v -h instruction_file

    -v -- verbose output
    -h -- print help

    instruction_file contains instructions for the processor to run. It is equivalent to an executable file (see sample.ins) 

Introduction:

This program simulates a simple processor.

Language definition:

read_location branch write_value

read_location - memory address to read
branch - where to branch next if location is 1
write_value - write some value to read_location


