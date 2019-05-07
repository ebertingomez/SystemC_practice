ifeq ($(HOME),true)
SYSTEMC   ?= /Users/QQINO/Documents/TelecomParisTech/2A/SE/SE207_SystemC/systemc-2.3.3
ARCH       = macosx64
else
SYSTEMC   ?= /comelec/softs/opt/systemc/current
ARCH       = linux64
endif

CPPFLAGS  =  -isystem $(SYSTEMC)/include
CXXFLAGS  =  -Wall -g -std=c++11
CXX		  =  g++
LDFLAGS   =  -L$(SYSTEMC)/lib-$(ARCH)
LDLIBS    =  -lsystemc

OBJS	  = logique vector arbitrary_int fixed_point time

all : $(OBJS)

clean: 
	rm -rf $(OBJS)