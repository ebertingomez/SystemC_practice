SYSTEMC   ?= /Users/QQINO/Documents/TelecomParisTech/2A/SE/SE207_SystemC/systemc-2.3.3
ARCH      ?= macosx64

CPPFLAGS  =  -isystem $(SYSTEMC)/include
CXXFLAGS  =  -Wall -g -std=c++11
CXX		  =  g++
LDFLAGS   =  -L$(SYSTEMC)/lib-$(ARCH)
LDLIBS    =  -lsystemc

EXEC	  = mod_thread mod_method pixel_gen_method pixel_gen_thread pixel_gen_cthread
OBJS	  = pixel.o

all : $(EXEC)

$(EXEC) : $(OBJS)

clean: 
	rm -rf $(OBJS) $(EXEC) *.o
