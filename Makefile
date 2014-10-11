# File: Makefile
# Author: JT Cho
# [jonathan.t.cho@gmail.com | joncho@seas.upenn.edu]

#Set the default C compiler to gcc.
CC = gcc

#Set the compiler flags.
#	-O3			optimize a lot!
#	-std=gnu99	C99 std language
#	-W			various diagnostic warnings
#CFLAGS = -O3 -std=gnu99 -Wall -Wfloat-equal -Wtype-limits -Wpointer-arith -Wlogical-op -fno-diagnostics-show-option -I.
CFLAGS = -O3 -std=gnu99 -I.

#A naive testing program which just tests a series of random
#bulk enqueues and dequeues.
programs = bulktest

#Unit Testing Suite,
#using the CuTest framework.
unittests = alltests

#Define the target configured to build
#everything named above in the programs
#var.
all: $(programs) $(unittests)

#The test programs use the JTQueue from
#the jt lib.
$(programs): libjt.a

#Dependencies for the testing suite.
$(unittests): jtqueue.c CuTest.c unittests.c alltests.c

#Build the lib.
libjt.a: jtqueue.o
	$(AR) $(ARFLAGS) $@ $?
.INTERMEDIATE: jtqueue.o

clean:
	rm -rf $(programs) $(unittests) libjt.a *.o

.PHONY: clean all

