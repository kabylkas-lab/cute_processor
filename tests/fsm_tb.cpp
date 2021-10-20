/*
 * Copyright (c) 2021 Nazarbayev University, Inc. All rights reserved.
 */

// Verilator generated module include.
#include "Vfsm.h"

// C++ libraries.
#include "stdlib.h"
#include <iostream>

// Verilator libraries.
#include "verilated.h"
#include "verilated_vcd_c.h"

using dut_type = Vfsm;

const uint32_t kSimIter = 15;
uint32_t global_time = 0;

struct input_package {
	// input bits
	unsigned int a ;
	unsigned int clk ;
};

struct output_package {
	unsigned int unlck;
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
    trace->open("fsm_wave.vcd");

    input_package inp;
    output_package out;

    /*
		#define STATE_Initial
    #define State1 2
    #define State2 3
    #define State3 4
    #define State4 5
    #define State5 6
    */

		int sasa;
    int iter = kSimIter;
		int i=0;
		int a1[15]={0,1,0,1,1};
		while(iter > 0)
    {
		// generate input package


		inp.clk = global_time % 2;
		switch(inp.clk){

			case 0:
			      inp.a = a1[i];
						switch(sasa){
							case 0:
											if(inp.a = 0) {sasa = 1;}
											else if(inp.a = 1) {sasa = 0;}
							break;
							case 1:
											if(inp.a = 1) {sasa = 2;}
											else if(inp.a = 0) {sasa = 0;}
							break;
							case 2:
											if(inp.a = 0) {sasa = 3;}
											else if(inp.a = 1) {sasa = 0;}
							break;
							case 3:
											if(inp.a = 1) {sasa = 4;}
											else if(inp.a = 0) {sasa = 0;}
							break;
							case 4:
											if(inp.a = 1) {sasa = 5;}
											else if(inp.a = 0) {sasa = 0;}
							break;
							case 5:
											out.unlck=1;
							break;
						  default:
							        out.unlck = 0;
					}
					i++;
					top->a = inp.a;

			break;
		}


        //feed data

				top->clk = inp.clk;

		advance_sim(top, trace);
        //top->eval();

		// detect error
        if(top->unlck != out.unlck) {
						std::cout << "clk" << inp.clk << "; ";
						std::cout << "iter" << iter << "; ";
						std::cout << "inp.a = " << (uint16_t)inp.a << "; ";
            std::cout << "top->unlck = " << (uint16_t)top->unlck << "; ";
            std::cout << "out.unlck = " << (uint16_t)out.unlck << std::endl;
        }

        //sim iteration
        iter--;
    }

    trace->close();
}
