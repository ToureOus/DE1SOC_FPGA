#ifndef SEVENSEGMENT_H
#define SEVENSEGMENT_H
#include "DE1SoCfpga.h"

const unsigned int bit_values[16] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,
                                     0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
const unsigned int HEX3_0_OFFSET = 0xFF200020 - LW_BRIDGE_BASE;
const unsigned int HEX5_4_OFFSET = 0xFF200030 - LW_BRIDGE_BASE;
const unsigned int KEY_OFFSET = 0xFF200050 - LW_BRIDGE_BASE;

class SevenSegment: public DE1SoCfpga{
public:
    SevenSegment();
    ~SevenSegment();
    void Hex_ClearAll();
    void Hex_ClearSpecific(int index);
    void Hex_WriteSpecific(int index, int value);
    void Hex_WriteNumber(int number);
    int PushButtonGet();

private:
    unsigned int reg0_hexValue;
    unsigned int reg1_hexValue;
};
#endif //SEVENSEGMENT_H
