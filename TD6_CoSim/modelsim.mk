V_SRC     = PGCD.sv

V_WRAPPER = PGCD.hpp
CPP_SRC   = simu.cpp
COMP_CPP  = $(patsubst %.cpp, .%.compiled, $(CPP_SRC)) 

all: simu

work:
	[ -d work ] || vlib work

%.hpp:%.sv | work
	vlog +acc $<
	scgenmod -bool -sc_uint $* > $@


.simu.compiled: PGCD.hpp

.%.compiled:%.cpp
	sccom -std=c++11 $<
	sccom -link
	touch $@

simu: $(COMP_CPP)
	vsim $(VSIM_OPT) sc_main

simu_nogui: VSIM_OPT += -c
simu_nogui: simu


clean:
	rm -fr work
	rm -f $(COMP_CPP)
	rm -f $(V_WRAPPER)