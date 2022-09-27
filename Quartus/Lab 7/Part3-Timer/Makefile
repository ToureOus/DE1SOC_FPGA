#Makefile

SevenSeg: SevenSegment.o DE1SoCfpga.o main.o
	g++ SevenSegment.o DE1SoCfpga.o main.o -o SevenSeg
 
SevenSegment.o: SevenSegment.cpp SevenSegment.h
	g++ -g -Wall -c SevenSegment.cpp
 
DE1SoCfpga.o: DE1SoCfpga.cpp DE1SoCfpga.h
	g++ -g -Wall -c DE1SoCfpga.cpp
 
main.o: main.cpp DE1SoCfpga.h SevenSegment.h
	g++ -g -Wall -c main.cpp
 
clean:
	rm SevenSegment.o DE1SoCfpga.o main.o SevenSeg