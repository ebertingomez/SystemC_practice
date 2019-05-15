SYSTEMC   ?= /Users/QQINO/Documents/TelecomParisTech/2A/SE/SE207_SystemC/systemc-2.3.3
ARCH      ?= macosx64

CPPFLAGS  =  -isystem $(SYSTEMC)/include
CXXFLAGS  =  -Wall -g -std=c++11
CXX		  =  g++
LDFLAGS   =  -L$(SYSTEMC)/lib-$(ARCH)
LDLIBS    =  -lsystemc

OBJS	  = example traces signal_example pixel time

all : $(OBJS)

clean: 
	rm -rf $(OBJS)