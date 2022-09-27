#ifndef DE1SOCFPGA_H
#define DE1SOCFPGA_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>

const unsigned int LW_BRIDGE_BASE = 0xFF200000;
const unsigned int FINAL_PHYSICAL_ADDRESS = 0xFFFEC700;
const unsigned int LW_BRIDGE_SPAN = FINAL_PHYSICAL_ADDRESS - LW_BRIDGE_BASE;
const unsigned int SW_OFFSET = 0xFF200040 - LW_BRIDGE_BASE;

class DE1SoCfpga{
protected:
    char *pBase;
    int fd;

public:
    DE1SoCfpga();
    ~DE1SoCfpga();
    //int ReadAllSwitches();
    void RegisterWrite(unsigned int offset, unsigned int value);
    int RegisterRead(unsigned int offset);
};



#endif //DE1SOCFPGA_H
