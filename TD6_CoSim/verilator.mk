V_SRC     = PGCD.sv
TOP_MODULE = PGCD

V_WRAPPER = PGCD.hpp
CPP_SRC   = simu.cpp
COMP_CPP  = $(patsubst %.cpp, .%.compiled, $(CPP_SRC)) 

all: compile
	obj_dir/run_verilator

compile:
	verilator -sc --pins-sc-uint $(V_SRC) $(CPP_SRC) --exe -o run_verilator
	make -C obj_dir -f V$(TOP_MODULE).mk


clean:
	rm -fr obj_dir