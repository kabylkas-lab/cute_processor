/*
 * Copyright (c) 2021 Nazarbayev University, Inc. All rights reserved.
 */

// Verilator generated module include.
#include "Valu.h"

// C++ libraries.
#include "stdlib.h" //rand
#include <iostream>

// Verilator libraries.
#include "verilated.h"
#include "verilated_vcd_c.h"

typedef Valu dut_type;

const uint32_t kSimIter = 1000;
uint32_t global_time = 0;

struct input_package {
    uint8_t a = 0;
    uint8_t b = 0;
    bool op = false;
};

struct output_package {
    uint8_t c = 0;
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
    trace->open("alu_wave.vcd");

    input_package inp;
    output_package out;

    int iter = SIM_ITER;
    while(iter > 0)
    {
        //generate input package
        inp.a = rand() % 100;
        inp.b = rand() % 100;
        inp.op = (bool)(rand()%2);

        //generate output package
        if(!inp.op) {
            out.c = inp.a + inp.b;
        } else {
            out.c = inp.a - inp.b;
        }

        //feed data
        top->a = inp.a;
        top->b = inp.b;
        top->op = (int)inp.op;
        top->eval();

        if(top->c != out.c) {
            std::cout << "Error: op= " << inp.op << "; ";
            std::cout << "inp.a = " << (uint16_t)inp.a << "; ";
            std::cout << "inp.b = " << (uint16_t)inp.b << "; ";
            std::cout << "top->c = " << (uint16_t)top->c << "; ";
            std::cout << "out.c = " << (uint16_t)out.c << std::endl;
        }

        //sim iteration 
        iter--;
    }

    trace->close();
}
