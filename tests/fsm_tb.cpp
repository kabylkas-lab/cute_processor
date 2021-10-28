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

const uint32_t kSimIter = 11;
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

    int sasa;
    int iter = kSimIter;
	int i=0;
	int a1[5]={0,1,0,1,1};
    int b[5];
	while(iter > 0)
    {
		inp.clk = global_time % 2;
		switch(inp.clk){
			case 0:
			      inp.a = a1[i];
                    b[i] = inp.a;
					i++;
					top->a = inp.a;
                    break;
            case 1:
                if (b[0]==a1[0]&&b[1]==a1[1]&&b[2]==a1[2]&&b[3]==a1[3]&&b[4]==a1[4]) {out.unlck = 1;}
                else {out.unlck = 0;}
                break;
		}

	    top->clk = inp.clk;

		advance_sim(top, trace);
        top->eval();

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
