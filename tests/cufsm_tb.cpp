/*
 * Copyright (c) 2022 Nazarbayev University, Inc. All rights reserved.
 */

// Verilator generated module include.
#include "Vcufsm.h"

// C++ libraries.
#include "stdlib.h"
#include <iostream>

// Verilator libraries.
#include "verilated.h"
#include "verilated_vcd_c.h"

using dut_type = Vcufsm;

const uint32_t kSimIter = 100;
uint32_t global_time = 0;

struct input_package {
    // input bits
    unsigned int clk;
    unsigned int Resetn = 0;


    // 9-bit input busses
    unsigned int ir : 9;
};

struct output_package {
    //unsigned int unlck;
    unsigned int a = 0;
    unsigned int g = 0;
    unsigned int done = 0;
    unsigned int alu = 0;
    unsigned int mux : 3;
    unsigned int rx : 8;
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
    trace->open("cufsm_wave.vcd");

    input_package inp;
    output_package out;

    inp.ir = 0b001101110; 
    
    int adr1 = (inp.ir & 0b000111000)/8;
    int adr2 = inp.ir & 0b000000111;

    int iter = kSimIter;
    int CurrentState = 0;
    int NextState = 0;
    while(iter > 0)
    {

        inp.clk = global_time % 2;
        top->clk = inp.clk;
        switch (inp.clk)
       {
       case 1:
           if (inp.Resetn || out.done){
               CurrentState = 0;
           } else {
               CurrentState = NextState;
           }
           break;
       case 0:
            top->ir = inp.ir;
            break;
       }


        top->Resetn = inp.Resetn;

        switch (CurrentState)
        {
        case 0:
            out.a = 0;
            out.g = 0;
            out.rx = 0;
            out.mux = 0;
            out.alu = 0;
            out.done = 0;
            if (inp.ir > 0b010000000) {NextState = 4;}
            else {NextState = 1;}
            break;
        case 1:
            out.mux = 0b0000 + adr1+1;
            out.rx = 1*2^(adr1);
            out.a = 1;
            NextState = 2;
            out.done = 0;
            break;
        case 2:
            out.mux = 0b0000 + adr2 + 1;
            out.rx = 1*2^(adr2);
            if (inp.ir > 64)
            {
                out.alu = 1;
            } else { out.alu = 0;}
            out.a = 1;
            out.g = 1;
            NextState = 3;
            out.done = 0;
            break;
        case 3:
            out.a = 0;
            out.alu = 0;
            out.mux = 0b1111;
            out.g = 1;
            out.rx = 1*2^(adr1);
            out.done = 1;
            NextState = 0;
            break;
        case 4:
            out.mux = 0b0000 + adr1 +1;
            out.rx = 1*2^(adr1) + 1*2^(adr2);
            out.done = 1;
            NextState = 0;
            break;    
        default:
            break;
        }
        
        top->eval();
        advance_sim(top, trace);

        // detect error
        if(top->done != out.done) {
            std::cout << "iter" << iter << "; ";
            std::cout << "clk" << inp.clk << "; ";
            std::cout << "instruction" << inp.ir << "; ";
            std::cout << "rx = " << (int)out.rx << "; ";
            std::cout << "a = " << (int)out.a << "; ";
            std::cout << "g = " << (int)out.g << "; ";
            std::cout << "alu = " << (int)out.alu << "; ";
            std::cout << "mux = " << (int)out.mux << "; ";
            std::cout << "done = " << (int)out.done << "; ";
        }

        //sim iteration
        iter--;
    }

    trace->close();
}
