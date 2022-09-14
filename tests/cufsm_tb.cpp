/*
 * Copyright (c) 2022 Nazarbayev University, Inc. All rights reserved.
 */

// Verilator generated module include.
#include "Vcufsm.h"

// C++ libraries.
#include "stdlib.h"
#include <iostream>
#include <math>

// Verilator libraries.
#include "verilated.h"
#include "verilated_vcd_c.h"

using dut_type = Vcufsm;

const uint32_t kSimIter = 19;
uint32_t global_time = 0;

struct input_package {
    // input bits
    unsigned int clk;
    unsigned int Resetn = 0;
    unsigned int Run = 0;

    // 9-bit input busses
    unsigned int ir : 9;
};

struct output_package {
    //unsigned int unlck;
    unsigned int a = 0;
    unsigned int g = 0;
    unsigned int IRen = 0;
    unsigned int done = 0;
    unsigned int alu = 0;
    unsigned int mux : 4;
    unsigned int rx : 8;
};

static void advance_sim(dut_type* top, VerilatedVcdC* trace)
{
    trace->dump(global_time);
    top->eval();
    ++global_time;
};
/* 
010-MV
011-MVI
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

    //inp.ir = 0b00101110; 

    int ix[5] = {0b001110011,0b010010001,0b011010100, 0b000111011};
    inp.ir = ix[0];
    int cmd;
    int adr1;
    int adr2;

    int i = 0;

    int iter = kSimIter;
    int CurrentState = 0;
    int NextState = 0;
    while(iter > 0)
    {
        
        inp.clk = (global_time) % 2;
        top->clk = inp.clk;
        switch (inp.clk)
       {
       case 1:
            
            top->ir = inp.ir;
            top->Run = inp.Run;
            if (inp.Resetn == 1 || out.done == 1){
                CurrentState = 0;
                inp.Run = 0;
            } else {
                CurrentState = NextState;
                inp.Run = 1;
            }
            
            if (top->done == 1 && inp.Run == 1 && out.rx == 0)
            {
                i++;
                inp.ir = ix[i];
            }
            break;
       case 0:
            
            break;
       }

    cmd = (inp.ir & 0b111000000)/64;
    adr1 = (inp.ir & 0b000111000)/8;
    adr2 = inp.ir & 0b000000111;

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
            if (inp.Run == 1)
            {
                if (cmd == 0b010) 
                {NextState = 4;}
                else if (cmd == 0b000 || cmd == 0b001) 
                {NextState = 1;}
                else if (cmd == 0b011)
                {NextState = 5;}
            }
            break;
        case 1:
            out.mux = 0b0000 + adr1+1;
            out.rx = 0b00000000 + 1*pow(2,adr1);
            out.a = 1;
            NextState = 2;
            out.done = 0;
            break;
        case 2:
            out.mux = 0b0000 + adr2 + 1;
            out.rx = 1*pow(2,adr2);
            if (cmd == 2)
            {
                out.alu = 1;
            } else { out.alu = 0;}
            out.a = 1;
            out.g = 1;
            NextState = 3;
            break;
        case 3:
            out.a = 0;
            out.alu = 0;
            out.mux = 0b1001;
            out.g = 1;
            out.rx = 1*pow(2,adr1);
            out.done = 1;
            break;
        case 4:
            out.mux = 0b0000 + adr1 +1;
            out.rx = 1*pow(2,adr1) + 1*pow(2,adr2);
            out.done = 1;
            break;    
        case 5:
            out.mux = 0b0000;
            out.rx = 1*pow(2,adr1);
            out.done = 1;
            break;
        default:
            break;
        }
        
        top->eval();
        advance_sim(top, trace);

        // detect error
        //if(top->done != out.done) {
            std::cout << " " << std::endl;
            std::cout << "iter " << kSimIter - iter << "; " << std::endl;
            std::cout << "clk "  << inp.clk << "; " << std::endl;
            std::cout << "instruction " << inp.ir << "; " << std::endl;
            std::cout << "rx = " << (int)out.rx << "; " << std::endl;
            std::cout << "a = " << (int)out.a << "; " << std::endl;
            std::cout << "g = " << (int)out.g << "; " << std::endl;
            std::cout << "alu = " << (int)out.alu << "; " << std::endl;
            std::cout << "mux = " << (int)out.mux << "; " << std::endl;
            std::cout << "done = " << (int)out.done << "; " << std::endl;
            std::cout << "state = " << CurrentState<< "; " << std::endl;
            std::cout << "n_state = " << NextState<< "; " << std::endl;
            std::cout << "Run = " << inp.Run << "; " << std::endl;
        //}

        //sim iteration
        iter--;
    }

    trace->close();
}
