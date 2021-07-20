.PHONY: all lint alu run_alu clean

all:
	@echo "Select set of tests to run"

lint:
	verilator --assert -I./rtl --Wall --lint-only --top-module core ./rtl/*.v


alu:
	verilator --assert -I./rtl --Wall --trace --cc ./rtl/alu.v --exe tests/alu_tb.cpp 
	make -C obj_dir/ -f Valu.mk Valu

run_alu: alu
	./obj_dir/Valu


clean:
	rm -rf *.vcd
	rm -rf obj_dir


