#include <iostream>
#include "SevenSegment.h"
#include "DE1SoCfpga.h"
SevenSegment::SevenSegment(){
    reg0_hexValue = (bit_values[0] << 24) | (bit_values[0] << 16) | (bit_values[0] << 8) | bit_values[0];
    reg1_hexValue = (bit_values[0] << 8) | bit_values[0];
    RegisterWrite(HEX3_0_OFFSET,reg0_hexValue);
    RegisterWrite(HEX5_4_OFFSET,reg1_hexValue);
}

SevenSegment::~SevenSegment() {
    Hex_ClearAll();
}

void SevenSegment::Hex_ClearAll() {
    reg0_hexValue = 0x3F3F3F3F;
    reg1_hexValue = 0x3F3F3F3F;
    RegisterWrite(HEX3_0_OFFSET,reg0_hexValue);
    RegisterWrite(HEX5_4_OFFSET,reg1_hexValue);
}

void SevenSegment::Hex_ClearSpecific(int index) {
    
    if(index == 0){reg0_hexValue = reg0_hexValue & 0x00F;}
    else if(index == 1){reg0_hexValue = reg0_hexValue & 0x0F0;}
    else if(index == 2){reg0_hexValue = reg0_hexValue & 0xF00;}
    else if(index == 3){reg0_hexValue = reg0_hexValue & 0xF000;}
    else if(index == 4){reg1_hexValue = reg1_hexValue & 0x00F;}
    else if(index == 5){reg1_hexValue = reg1_hexValue & 0x0F0;}
    else{
        std::cerr << "Index exceeding 5 or less than 0!" << std::endl;
        exit(1);
    }
    
}

void SevenSegment::Hex_WriteNumber(int number) {
    int temp;
    temp = number;
    int store[6] = {0,0,0,0,0,0};
    int remainder;
    int count = 0;
    while(temp > 0){
        remainder = temp%16;
        store[count] = remainder;
        std::cout << remainder;
        ++count;
        temp = temp/16;
    }
    reg0_hexValue = 0x00;
    reg1_hexValue = 0x00;
    
    reg0_hexValue = (bit_values[store[3]] << 24) | (bit_values[store[2]] << 16) | (bit_values[store[1]] << 8) | bit_values[store[0]];
    reg1_hexValue = (bit_values[store[5]] << 8) | bit_values[store[4]];
    
    
    RegisterWrite(HEX3_0_OFFSET,reg0_hexValue);
    RegisterWrite(HEX5_4_OFFSET,reg1_hexValue);
    
}

void SevenSegment::Hex_WriteSpecific(int index, int value) {

    int temp;
    
    if(value > 15 || value < -16) {
        std::cerr << "Value exceeding boundary!" << std::endl;
        exit(1);
    }
    else if(value >= 0) {temp = value;}
    else{temp = 16+value;}
    
    temp = value;
    if(index < 4){reg0_hexValue = reg0_hexValue | (bit_values[temp] << 8*index);}
    else{reg1_hexValue = reg1_hexValue | (bit_values[temp] << 8*(index-4));}
    RegisterWrite(HEX3_0_OFFSET,reg0_hexValue);
    RegisterWrite(HEX5_4_OFFSET,reg1_hexValue);
}

/*
int SevenSegment::PushButtonGet() {
    int value = this->RegisterRead(pBase,KEY_OFFSET);
    return value;
}
*/

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

//int DE1SoCfpga::RegisterRead(unsigned int offset) {
    //return *(volatile unsigned int *)(pBase + offset);
//}

void DE1SoCfpga::RegisterWrite(unsigned int offset, unsigned int value) {
    *(volatile unsigned int *)(pBase + offset) = value;
}

int main()
{
    SevenSegment *display = new SevenSegment;
    std::cout << "Program Starting...!" << std::endl;
    bool condition = true;
    int hex_value;
    while(condition){
      std::cout << "Please enter a number for display (in the range -16777216 to 16777215):";
      std::cin >> hex_value;
      display->Hex_WriteNumber(hex_value);
      std::cout << "Do you want to stop? press y to stop ";
      char v;
      std::cin >> v;
      if(v == 'y'){condition = false;}
    }
    std::cout << "Terminating...!" << std::endl;
    delete display;
    return 0;
}
