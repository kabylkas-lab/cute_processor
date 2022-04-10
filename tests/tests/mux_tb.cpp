/*
 * Copyright (c) 2021 Nazarbayev University, Inc. All rights reserved.
 */

// Verilator generated module include.
#include "Vmux.h"

// C++ libraries.
#include "stdlib.h"
#include <iostream>

// Verilator libraries.
#include "verilated.h"
#include "verilated_vcd_c.h"

using dut_type = Vmux;

const uint32_t kSimIter = 100;
uint32_t global_time = 0;

struct input_package {
    // 9-bit input busses
    unsigned int a0 : 9;
    unsigned int a1 : 9;
    unsigned int a2 : 9;
    unsigned int a3 : 9;
    unsigned int a4 : 9;
    unsigned int a5 : 9;
    unsigned int a6 : 9;
    unsigned int a7 : 9;
    unsigned int a8 : 9;
    unsigned int a9 : 9;
    
    // 4 control switches
    unsigned int ctrlVar : 4;
};

struct output_package {
    // 9-bit output bus
    unsigned int otp : 9;
};



static void advance_sim(dut_type* top, VerilatedVcdC* trace)
{
    trace->dump(global_time);
    top->eval();
    ++global_time;
}

int main() {
    srand(1234);

    dut_type* top = new dut_type;
    Verilated::traceEverOn(true);
    VerilatedVcdC* trace = new VerilatedVcdC;
    top->trace(trace, 99);
    trace->open("mux_wave.vcd");

    input_package inp;
    output_package out;

    int iter = kSimIter;
    while(iter > 0)
    {
        // generate input package for 9-bit inputs
        inp.a0 = rand() % 512;
        inp.a1 = rand() % 512;
        inp.a2 = rand() % 512;
        inp.a3 = rand() % 512;
        inp.a4 = rand() % 512;
        inp.a5 = rand() % 512;
        inp.a6 = rand() % 512;
        inp.a7 = rand() % 512;
        inp.a8 = rand() % 512;
        inp.a9 = rand() % 512;
        
        //control switches
        inp.ctrlVar = rand() % 10;
        
        // select input by control switches
        switch (inp.ctrlVar){
            case 0:
                out.otp = inp.a0;
                break;
            case 1:
                out.otp = inp.a1;
                break;
            case 2:
                out.otp = inp.a2;
                break;
            case 3:
                out.otp = inp.a3;
                break;
            case 4:
                out.otp = inp.a4;
                break;
            case 5:
                out.otp = inp.a5;
                break;
            case 6:
                out.otp = inp.a6;
                break;
            case 7:
                out.otp = inp.a7;
                break;
            case 8:
                out.otp = inp.a8;
                break;
            case 9:
                out.otp = inp.a9;
                break;
        }

        //feed data
        top->a0 = inp.a0;
        top->a1 = inp.a1;
        top->a2 = inp.a2;
        top->a3 = inp.a3;
        top->a4 = inp.a4;
        top->a5 = inp.a5;
        top->a6 = inp.a6;
        top->a7 = inp.a7;
        top->a8 = inp.a8;
        top->a9 = inp.a9;
        top->ctrlVar = inp.ctrlVar;
        advance_sim(top, trace);
        //top->eval();

        // detect error
        if(top->otp != out.otp) {
            std::cout << "Error: ctrl = " << inp.ctrlVar << "; ";
            std::cout << "inp.a0 = " << (uint16_t)inp.a0 << "; ";
            std::cout << "inp.a1 = " << (uint16_t)inp.a1 << "; ";
            std::cout << "inp.a2 = " << (uint16_t)inp.a2 << "; ";
            std::cout << "inp.a3 = " << (uint16_t)inp.a3 << "; ";
            std::cout << "inp.a4 = " << (uint16_t)inp.a4 << "; ";
            std::cout << "inp.a5 = " << (uint16_t)inp.a5 << "; ";
            std::cout << "inp.a6 = " << (uint16_t)inp.a6 << "; ";
            std::cout << "inp.a7 = " << (uint16_t)inp.a7 << "; ";
            std::cout << "inp.a8 = " << (uint16_t)inp.a8 << "; ";
            std::cout << "inp.a9 = " << (uint16_t)inp.a9 << "; ";
            std::cout << "top->otp = " << (uint16_t)top->otp << "; ";
            std::cout << "out.otp = " << (uint16_t)out.otp << std::endl;
        }

        //sim iteration 
        iter--;
    }

    trace->close();
}

