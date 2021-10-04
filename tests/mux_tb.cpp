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
	//input buses
	bool a,b,c,d,e,f,g,h,i,j = false;
	//control switches
	bool c1, c2, c3, c4 = false;
	unsigned int ctrlVar : 4;
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
		
		ctrlVar = rand() % 10;
		
		switch (ctrlVar){
			case 0:
				out.otp = (int)inp.a;
				break;
			case 1:
				out.otp = (int)inp.b;
				break;
			case 2:
				out.otp = (int)inp.c;
				break;
			case 3:
				out.otp = (int)inp.d;
				break;
			case 4:
				out.otp = (int)inp.e;
				break;
			case 5:
				out.otp = (int)inp.f;
				break;
			case 6:
				out.otp = (int)inp.g;
				break;
			case 7:
				out.otp = (int)inp.h;
				break;
			case 8:
				out.otp = (int)inp.i;
				break;
			case 9:
				out.otp = (int)inp.j;
				break;
		}

     /*   //generate output package
        if(!inp.c1) {
            if(!inp.c2) {
				if(!inp.c3) {
					if(!inp.c4) {
						out.otp = (int)inp.a;
					} else {
						out.otp = (int)inp.b;
					}
				} else {
					if(!inp.c4) {
						out.otp = (int)inp.c;
					} else {
						out.otp = (int)inp.d;
					}
				}
			} else {
				if(!inp.c3) {
					if(!inp.c4) {
						out.otp = (int)inp.e;
					} else {
						out.otp = (int)inp.f;
					}
				} else {
					if(!inp.c4) {
						out.otp = (int)inp.g;
					} else {
						out.otp = (int)inp.h;
					}
				}
			}
        } else {
            if(!inp.c4) {
				out.otp = (int)inp.i;
			} else {
				out.otp = (int)inp.j;
			}
        }  */
		
		

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
        top->j = (int)inp.j;/*
        top->c1 = (int)inp.c1;
        top->c2 = (int)inp.c2;
        top->c3 = (int)inp.c3;
        top->c4 = (int)inp.c4;*/
		top->ctrlVar = inp.ctrlVar;
		advance_sim(top, trace);
        top->eval();

        if(top->otp != out.otp) {
            std::cout << "Error: ctrl = " << inp.ctrlVar << "; ";
            std::cout << "inp.a = " << (uint16_t)inp.a << "; ";
            std::cout << "inp.b = " << (uint16_t)inp.b << "; ";
            std::cout << "inp.c = " << (uint16_t)inp.c << "; ";
            std::cout << "inp.d = " << (uint16_t)inp.d << "; ";
            std::cout << "inp.e = " << (uint16_t)inp.e << "; ";
            std::cout << "inp.f = " << (uint16_t)inp.f << "; ";
            std::cout << "inp.g = " << (uint16_t)inp.g << "; ";
            std::cout << "inp.h = " << (uint16_t)inp.h << "; ";
            std::cout << "inp.i = " << (uint16_t)inp.i << "; ";
            std::cout << "inp.j = " << (uint16_t)inp.j << "; ";
            std::cout << "top->otp = " << (uint16_t)top->otp << "; ";
            std::cout << "out.otp = " << (uint16_t)out.otp << std::endl;
        }

        //sim iteration 
        iter--;
    }

    trace->close();
}
*/
