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
}

void SevenSegment::Hex_WriteNumber(int number) {
    //int temp;
    
    
    //reg0_hexValue = 0;
    //reg1_hexValue = 0;
    int x;
    unsigned int low ;
    unsigned int high;
    for(int i = 0; i < 6; i++){
        if(i < 4){
            x = bit_values[((number & (0xF << (i*4))) >> (i*4))];
            low = low | (x << (i*8));
        }
        else{
            x = bit_values[((number & (0xF << (i*4))) >> (i*4))];
            high = high | (x << ((i-4)*8));
            std::cout << x; 
        }      
    }
    */
     
    //int store[6] = {0,0,0,0,0,0};
    
    int ind_0 = bit_values[(number &  0x00F)];
    int ind_1 = bit_values[(number &  0x0F0) >> 4];
    int ind_2 = bit_values[(number &  0xF00)>> 8];
    int ind_3 = bit_values[(number &  0xF000)>> 12];
    int ind_4 = bit_values[(number &  0xF0000)>> 16];
    int ind_5 = bit_values[(number &  0xF00000)>> 20];
    
    int low = ind_0 | ind_1 << 8 | ind_2 << 16 | ind_3 << 24;
    int high = ind_4 | ind_5 << 8;

   
    RegisterWrite(HEX3_0_OFFSET,low);
    RegisterWrite(HEX5_4_OFFSET,high);
    
}

void SevenSegment::Hex_WriteSpecific(int index, int value) {
    
    int temp;
    
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
