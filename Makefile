.PHONY: all lint alu mux fsm run_alu run_mux run_fsm cufsm run_cufsm clean

all:
	@echo "Select set of tests to run"

lint:
	verilator --assert -I./rtl --Wall --lint-only --top-module core ./rtl/*.v


alu:
	verilator --assert -I./rtl --Wall --trace --cc ./rtl/alu.v --exe tests/alu_tb.cpp
	make -C obj_dir/ -f Valu.mk Valu
	
	
mux:
	verilator --assert -I./rtl --Wall --trace --cc ./rtl/mux.v --exe tests/mux_tb.cpp
	make -C obj_dir/ -f Vmux.mk Vmux

fsm:
	verilator --assert -I./rtl --Wall --trace --cc ./rtl/fsm.v --exe tests/fsm_tb.cpp
	make -C obj_dir/ -f Vfsm.mk Vfsm

cufsm:
	verilator --assert -I./rtl --Wall --trace --cc ./rtl/cufsm.v --exe tests/cufsm_tb.cpp
	make -C obj_dir/ -f Vcufsm.mk Vcufsm
	
run_alu: alu
	./obj_dir/Valu

run_mux: mux
	./obj_dir/Vmux
	
run_fsm: fsm
	./obj_dir/Vfsm	
	
run_cufsm: cufsm
	./obj_dir/Vcufsm	
	
clean:
	rm -rf *.vcd
	rm -rf obj_dir


