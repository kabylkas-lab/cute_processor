.PHONY: all lint alu mux1 run_alu clean

all:
	@echo "Select set of tests to run"

lint:
	verilator --assert -I./rtl --Wall --lint-only --top-module core ./rtl/*.v


alu:
	verilator --assert -I./rtl --Wall --trace --cc ./rtl/alu.v --exe tests/alu_tb.cpp
	make -C obj_dir/ -f Valu.mk Valu
	
	
mux1:
	verilator --assert -I./rtl --Wall --trace --cc ./rtl/mux1.v --exe tests/mux_tb.cpp
	make -C obj_dir/ -f Vmux.mk Vmux
	
run_alu: alu
	./obj_dir/Valu

run_mux1: mux1
	./obj_dir/Vmux
	
clean:
	rm -rf *.vcd
	rm -rf obj_dir


