# use normal make for this Makefile
#
# Makefile for building user programs to run on top of Nachos
#
# Several things to be aware of:
#
#    Nachos assumes that the location of the program startup routine (the
# 	location the kernel jumps to when the program initially starts up)
#       is at location 0.  This means: start.o must be the first .o passed 
# 	to ld, in order for the routine "Start" to be loaded at location 0
#

# if you are cross-compiling, you need to point to the right executables
# and change the flags to ld and the build procedure for as

GCCDIR = ../../../gnu-decstation-ultrix/decstation-ultrix/2.95.3/

LDFLAGS = -T script -N
ASFLAGS = -mips2
CPPFLAGS = $(INCDIR)

# if you aren't cross-compiling:
# GCCDIR =
# LDFLAGS = -N -T 0
# ASFLAGS =
# CPPFLAGS = -P $(INCDIR)

PATH = $(GCCDIR):/lib:/usr/bin:/bin

CC = $(GCCDIR)gcc -B../../../gnu-decstation-ultrix/
AS = $(GCCDIR)as
LD = $(GCCDIR)ld

CPP = gcc -E
INCDIR =-I../userprog -I../threads
CFLAGS = -G 0 -c $(INCDIR)

all: halt shell matmult sort MemoryEater StudentSort WordCount1 WordCount2 testcase1 testcase2 testcase3

start.o: start.s ../userprog/syscall.h
	$(CPP) $(CPPFLAGS) start.c > strt.s
	$(AS) $(ASFLAGS) -o start.o strt.s
	rm strt.s

halt.o: halt.c
	$(CC) $(CFLAGS) -c halt.c
halt: halt.o start.o
	$(LD) $(LDFLAGS) start.o halt.o -o halt.coff
	../bin/coff2noff halt.coff halt

shell.o: shell.c
	$(CC) $(CFLAGS) -c shell.c
shell: shell.o start.o
	$(LD) $(LDFLAGS) start.o shell.o -o shell.coff
	../bin/coff2noff shell.coff shell

sort.o: sort.c
	$(CC) $(CFLAGS) -c sort.c
sort: sort.o start.o
	$(LD) $(LDFLAGS) start.o sort.o -o sort.coff
	../bin/coff2noff sort.coff sort

matmult.o: matmult.c
	$(CC) $(CFLAGS) -c matmult.c
matmult: matmult.o start.o
	$(LD) $(LDFLAGS) start.o matmult.o -o matmult.coff
	../bin/coff2noff matmult.coff matmult

MemoryEater.o: MemoryEater.c
	$(CC) $(CFLAGS) -c MemoryEater.c
MemoryEater: MemoryEater.o start.o
	$(LD) $(LDFLAGS) start.o MemoryEater.o -o MemoryEater.coff
	../bin/coff2noff MemoryEater.coff MemoryEater

StudentSort.o: StudentSort.c
	$(CC) $(CFLAGS) -c StudentSort.c
StudentSort: StudentSort.o start.o
	$(LD) $(LDFLAGS) start.o StudentSort.o -o StudentSort.coff
	../bin/coff2noff StudentSort.coff StudentSort

WordCount1.o: WordCount1.c
	$(CC) $(CFLAGS) -c WordCount1.c
WordCount1: WordCount1.o start.o
	$(LD) $(LDFLAGS) start.o WordCount1.o -o WordCount1.coff
	../bin/coff2noff WordCount1.coff WordCount1

WordCount2.o: WordCount2.c
	$(CC) $(CFLAGS) -c WordCount2.c
WordCount2: WordCount2.o start.o
	$(LD) $(LDFLAGS) start.o WordCount2.o -o WordCount2.coff
	../bin/coff2noff WordCount2.coff WordCount2

testcase1.o: testcase1.c
	$(CC) $(CFLAGS) -c testcase1.c
testcase1: testcase1.o start.o
	$(LD) $(LDFLAGS) start.o testcase1.o -o testcase1.coff
	../bin/coff2noff testcase1.coff testcase1

testcase2.o: testcase2.c
	$(CC) $(CFLAGS) -c testcase2.c
testcase2: testcase2.o start.o
	$(LD) $(LDFLAGS) start.o testcase2.o -o testcase2.coff
	../bin/coff2noff testcase2.coff testcase2

testcase3.o: testcase3.c
	$(CC) $(CFLAGS) -c testcase3.c
testcase3: testcase3.o start.o
	$(LD) $(LDFLAGS) start.o testcase3.o -o testcase3.coff
	../bin/coff2noff testcase3.coff testcase3