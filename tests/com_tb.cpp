/*
 * Copyright (c) 2022 Nazarbayev University, Inc. All rights reserved.
 */

// Verilator generated module include.
#include "Vcom.h"

// C++ libraries.
#include "stdlib.h"
#include <iostream>

// Verilator libraries
#include "verilated.h"
#include "verilated_vcd_c.h"

using dut_type = Vcom;

const uint32_t kSimIter = 100;
uint32_t global_time = 0;

struct input_package {
    // input bits
    unsigned int clk;
    unsigned int Resetn = 0;
    unsigned int Run;

    // 9-bit input busses
};

struct output_package {
    //unsigned int unlck;
    signed int bus : 9;
    signed int sol : 9;
    unsigned int done = 0;
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
    trace->open("com_wave.vcd");

    input_package inp;
    output_package out;

    // Memory register info
    int reg[8] = {50,120,80,200,68,250,8,150};

    int i = 0;
    int k = 0;

    int cmd,adr1,adr2;

    inp.Run = 1;

    int iter = kSimIter;
    int CurrentState = 0;
    int NextState = 0;
    while(iter > 0)
    {
        int mem = top->DIN;
        int adr1 = (mem & 0b000111000)/8;
        int adr2 = mem & 0b000000111;

        inp.clk = global_time % 2;
        top->clk = inp.clk;
        switch (inp.clk)
        {
            case 1:
                top->Resetn = inp.Resetn;
                top->Run = inp.Run;
                cmd = (mem & 0b111000000)/64;

                break;
            case 0:
                if (top->done == 1)
                {
                    out.sol = (signed int)top->bus;
                    if (cmd == 0b010) 
                    {
                        out.bus=reg[adr2];
                        reg[adr1] = reg[adr2];
                    }
                    else if (cmd == 0b000) 
                    {
                        out.bus = reg[adr1]+reg[adr2];
                        reg[adr1] = out.bus;
                    }
                    else if (cmd == 0b001) 
                    {
                        out.bus = reg[adr1]-reg[adr2];
                        reg[adr1] = out.bus;   
                    }
                    else if (cmd == 0b011)
                    {
                        out.bus = mem;
                        reg[adr1] = mem;
                    }
                    else if (cmd==0b100|cmd==0b110|cmd==0b111)
                    {
                        out.bus = mem;
                    }
                    else if (cmd == 0b101)
                    {
                        out.bus = reg[adr2];
                    }


                    if (out.sol == out.bus){
                        inp.Run = 1; 
                    }
                    else{
                        inp.Resetn = 1;
                        inp.Run = 0;
                        i=0;
                        top->eval();
                        std::cout << std::endl;
                        std::cout << "iter " << kSimIter-iter << "; " << std::endl;
                        std::cout << "clk " << inp.clk << "; " << std::endl;
                        for (int i = 0; i<8;i++){
                        std::cout << reg[i] << " ";}
                        std::cout << std::endl;
                        std::cout << "bus " << out.bus << " " << out.sol << "; " << std::endl;
                        std::cout << "instruction " << mem << "; " << std::endl;
                        break;
                    }
                }
    }
    top->eval();
    advance_sim(top, trace);
    if(inp.Resetn==1) break;
    iter--;
    }
    trace->close();
}
