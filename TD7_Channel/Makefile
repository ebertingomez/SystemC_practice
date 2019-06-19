SYSTEMC   ?= /Users/QQINO/Documents/TelecomParisTech/2A/SE/SE207_SystemC/systemc-2.3.3
ARCH      ?= macosx64

CPPFLAGS  =  -isystem $(SYSTEMC)/include
CXXFLAGS  =  -Wall -g -std=c++11
CXX		  =  g++
LDFLAGS   =  -L$(SYSTEMC)/lib-$(ARCH)
LDLIBS    =  -lsystemc

OBJS	  = pixel.o
EXEC	  = interfaces_example canal_example fifo_example
EXEC      += signal_buffer fifo_thread fifo_method mutex channel

all : $(EXEC)

fifo : $(OBJS)

clean: 
	rm -rf $(OBJS) $(EXEC) *.o