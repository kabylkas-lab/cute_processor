/*
 * Copyright (c) 2022 Nazarbayev University, Inc. All rights reserved.
 */

// Verilator generated module include.
#include "Vcute.h"

// C++ libraries.
#include "stdlib.h"
#include <iostream>

// Verilator libraries.
#include "verilated.h"
#include "verilated_vcd_c.h"

using dut_type = Vcute;

const uint32_t kSimIter = 10;
uint32_t global_time = 0;

struct input_package {
    // input bits
    unsigned int clk;
    unsigned int Resetn = 0;
    unsigned int Run;

    // 9-bit input busses
    unsigned int DIN : 9;
};

struct output_package {
    //unsigned int unlck;
    unsigned int bus : 9;
    unsigned int done = 0;

    unsigned int a1 : 9;
    unsigned int a2 : 9;
    unsigned int a3 : 9;
    unsigned int a4 : 9;
    unsigned int a5 : 9;
    unsigned int a6 : 9;
    unsigned int a7 : 9;
    unsigned int a8 : 9;
};

static void advance_sim(dut_type* top, VerilatedVcdC* trace)
{
    trace->dump(global_time);
    top->eval();
    ++global_time;
}

/* 
010-MV
000-ADD
001-SUB
*/

int main() {
    srand(1234);

    dut_type* top = new dut_type;
    Verilated::traceEverOn(true);
    VerilatedVcdC* trace = new VerilatedVcdC;
    top->trace(trace, 99);
    trace->open("cute_wave.vcd");

    input_package inp;
    output_package out;

    inp.DIN = 0b010110011;
    inp.Run = 1;

    int iter = kSimIter;
    int CurrentState = 0;
    int NextState = 0;
    while(iter > 0)
    {

        inp.clk = (global_time+1)   % 2;

        top->Run = inp.Run;
        top->Resetn = inp.Resetn;
        top->clk = inp.clk;
        top->DIN = inp.DIN;
        
        top->eval();
        advance_sim(top, trace);

        // detect error
        if(top->bus != out.bus) {
            std::cout << "iter " << iter << "; " << std::endl;
            std::cout << "clk " << inp.clk << "; " << std::endl;
            std::cout << "instruction " << inp.DIN << "; " << std::endl;
            std::cout << "bus " << out.bus << "; " << std::endl;
        }

        //sim iteration
        iter--;
    }

    trace->close();
}
