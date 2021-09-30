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

const uint32_t kSimIter = 1000;
uint32_t global_time = 0;

struct input_package {
	//input buses
	bool a,b,c,d,e,f,g,h,i,j = false;
	//control switches
	bool c1, c2, c3, c4 = false;
};

struct output_package {
    uint8_t otp = 0;
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
        //generate input package
        inp.a = (bool)(rand()%2);
        inp.b = (bool)(rand()%2);
        inp.c = (bool)(rand()%2);
        inp.d = (bool)(rand()%2);
        inp.e = (bool)(rand()%2);
        inp.f = (bool)(rand()%2);
        inp.g = (bool)(rand()%2);
        inp.h = (bool)(rand()%2);
        inp.i = (bool)(rand()%2);
        inp.j = (bool)(rand()%2);
		
		//control switches
        inp.c1 = (bool)(rand()%2);
		inp.c2 = (bool)(rand()%2);
		inp.c3 = (bool)(rand()%2);
		inp.c4 = (bool)(rand()%2);

        //generate output package
        if(!inp.c1) {
            if(!inp.c2) {
				if(!inp.c3) {
					if(!inp.c4) {
						out.otp = (int)in.a
					} else {
						out.otp = (int)in.b
					}
				} else {
					if(!inp.c4) {
						out.otp = (int)in.c
					} else {
						out.otp = (int)in.d
					}
				}
			} else {
				if(!inp.c3) {
					if(!inp.c4) {
						out.otp = (int)in.e
					} else {
						out.otp = (int)in.f
					}
				} else {
					if(!inp.c4) {
						out.otp = (int)in.g
					} else {
						out.otp = (int)in.h
					}
				}
			}
        } else {
            if(!inp.c4) {
				out.otp = (int)in.i
			} else {
				out.otp = (int)in.j
			}
        }

        //feed data
        top->a = (int)inp.a;
        top->b = (int)inp.b;
        top->c = (int)inp.c;
        top->d = (int)inp.d;
        top->e = (int)inp.e;
        top->f = (int)inp.f;
        top->g = (int)inp.g;
        top->h = (int)inp.h;
        top->i = (int)inp.i;
        top->j = (int)inp.j;
        top->c1 = (int)inp.c1;
        top->c2 = (int)inp.c2;
        top->c3 = (int)inp.c3;
        top->c4 = (int)inp.c4;
        top->eval();

        if(top->otp != out.otp) {
            std::cout << "Error: op= " << inp.op << "; ";
            std::cout << "inp.a = " << (uint16_t)inp.a << "; ";
            std::cout << "inp.b = " << (uint16_t)inp.b << "; ";
            std::cout << "top->c = " << (uint16_t)top->otp << "; ";
            std::cout << "out.otp = " << (uint16_t)out.otp << std::endl;
        }

        //sim iteration 
        iter--;
    }

    trace->close();
}