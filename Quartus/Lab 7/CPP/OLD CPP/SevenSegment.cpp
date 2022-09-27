#include "SevenSegment.h"

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

    if(index == 0){reg0_hexValue = reg0_hexValue & 0xFFFFFF00;}
    else if(index == 1){reg0_hexValue = reg0_hexValue & 0xFFFF00FF;}
    else if(index == 2){reg0_hexValue = reg0_hexValue & 0xFF00FFFF;}
    else if(index == 3){reg0_hexValue = reg0_hexValue & 0x00FFFFFF;}
    else if(index == 4){reg1_hexValue = reg1_hexValue & 0xFFFFFF00;}
    else if(index == 5){reg1_hexValue = reg1_hexValue & 0xFFFF00FF;}
    else{
        std::cerr << "Index exceeding 5 or less than 0!" << std::endl;
        exit(1);
    }
    /*
    if(index == 0){reg0_hexValue = reg0_hexValue & 0x00F;}
    else if(index == 1){reg0_hexValue = reg0_hexValue & 0x0F0;}
    else if(index == 2){reg0_hexValue = reg0_hexValue & 0xF00;}
    else if(index == 3){reg0_hexValue = reg0_hexValue & 0xF000;}
    else if(index == 4){reg1_hexValue = reg1_hexValue & 0xF0000;}
    else if(index == 5){reg1_hexValue = reg1_hexValue & 0xF00000;}
    else{
        std::cerr << "Index exceeding 5 or less than 0!" << std::endl;
        exit(1);
    }
    */
}

void SevenSegment::Hex_WriteNumber(int number) {
    int temp;
    /*
    if(number > 0xFFFFFF) {
        std::cerr << "Number exceeding boundary." << std::endl;
        exit(1);
    }
    */
    //else if(number >= 0) {temp = number;}
    //else {temp = 0xFFFFFF+1+number;}
    temp = number;
    int store[6] = {0,0,0,0,0,0};
    int remainder;
    int count = 0;
    while(temp > 0){
        remainder = temp%16;
        store[count] = remainder;
        std::cout << remainder;
        count++;
        temp = temp/16;
    }
    reg0_hexValue = 0;
    reg1_hexValue = 0;
    for(int i = 0; i < 6; i++){
        Hex_WriteSpecific(i,store[i]);
        /*
        if(i < 4){reg0_hexValue = reg0_hexValue | (bit_values[store[i]] << (8*i));}
        else{reg1_hexValue = reg1_hexValue | (bit_values[store[i]] << (8*(i-4)));}
        */
    }
    /*
    reg0_hexValue = (bit_values[store[3]] << 24) | (bit_values[store[2]] << 16) | (bit_values[store[1]] << 8) | bit_values[store[0]];
    reg1_hexValue = (bit_values[store[5]] << 8) | bit_values[store[4]];
    */
    /*
    RegisterWrite(HEX3_0_OFFSET,reg0_hexValue);
    RegisterWrite(HEX5_4_OFFSET,reg1_hexValue);
    */
}

void SevenSegment::Hex_WriteSpecific(int index, int value) {
    //Hex_ClearSpecific(index);
    int temp;
    /*
    if(value > 15 || value < -16) {
        std::cerr << "Value exceeding boundary!" << std::endl;
        exit(1);
    }
    else if(value >= 0) {temp = value;}
    else{temp = 16+value;}
    */
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
