#include "DE1SoCfpga.h"

DE1SoCfpga::DE1SoCfpga(){
    fd = open("/dev/mem",(O_RDWR | O_SYNC));
    if(fd == -1){
        std::cout << "ERROR: could not open /dev/mem..." << std::endl;
        exit(1);
    }
    char *virtual_base = (char *)mmap(NULL, LW_BRIDGE_SPAN,(PROT_READ | PROT_WRITE), MAP_SHARED, fd, LW_BRIDGE_BASE);
    if(virtual_base == MAP_FAILED){
        std::cout << "ERROR: mmap() failed..." << std::endl;
        close(fd);
        exit(1);
    }
    pBase = virtual_base;
}

DE1SoCfpga::~DE1SoCfpga() {
    if(munmap(pBase,LW_BRIDGE_SPAN) != 0){
        std::cout << "ERROR: munmap() failed..." << std::endl;
        exit(1);
    }
    close(fd);
}

int DE1SoCfpga::RegisterRead(unsigned int offset) {
    return *(volatile unsigned int *)(pBase + offset);
}

void DE1SoCfpga::RegisterWrite(unsigned int offset, unsigned int value) {
    *(volatile unsigned int *)(pBase + offset) = value;
}

/*
int DE1SoCfpga::ReadAllSwitches(){
    return *(volatile unsigned int *)(pBase + SW_OFFSET);
}
*/