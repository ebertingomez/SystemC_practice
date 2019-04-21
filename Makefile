SYSTEMC   ?= /comelec/softs/opt/systemc/current
ARCH       = linux64

CPPFLAGS  =  -isystem $(SYSTEMC)/include
CXXFLAGS  =  -Wall -g
LDFLAGS   =  -L$(SYSTEMC)/lib-$(ARCH)
LDLIBS    =  -lsystemc

OBJS	  = logique vector arbitrary_int fixed_point

all : $(OBJS)

clean: 
	rm -rf $(OBJS)