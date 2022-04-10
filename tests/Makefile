.PHONY: all lint alu mux cufsm cute com run_alu run_mux run_cute run_com translate clean

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

cufsm:
	verilator --assert -I./rtl --Wall --trace --cc ./rtl/cufsm.v --exe tests/cufsm_tb.cpp
	make -C obj_dir/ -f Vcufsm.mk Vcufsm

cute:
	verilator --assert -I./rtl --Wall --trace --cc ./rtl/cute.v --exe tests/cute_tb.cpp
	make -C obj_dir/ -f Vcute.mk Vcute

com:
	verilator --assert -I./rtl --Wall --trace --cc ./rtl/com.v --exe tests/com_tb.cpp
	make -C obj_dir/ -f Vcom.mk Vcom
	
run_alu: alu
	./obj_dir/Valu

run_mux: mux
	./obj_dir/Vmux

run_cufsm: cufsm
	./obj_dir/Vcufsm

run_cute: cute
	./obj_dir/Vcute

run_com: com
	./obj_dir/Vcom

translate:
	/bin/python3 ./cmd/translator.py

clean:
	rm -rf *.vcd
	rm -rf obj_dir
