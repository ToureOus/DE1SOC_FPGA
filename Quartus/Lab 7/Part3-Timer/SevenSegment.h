#ifndef SEVENSEGMENT_H
#define SEVENSEGMENT_H
#include "DE1SoCfpga.h"

const unsigned int bit_values[16] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,
                                     0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
const unsigned int HEX3_0_OFFSET = 0xFF200020 - LW_BRIDGE_BASE;
const unsigned int HEX5_4_OFFSET = 0xFF200030 - LW_BRIDGE_BASE;
const unsigned int KEY_OFFSET = 0xFF200050 - LW_BRIDGE_BASE;
const unsigned int  MPCORE_PRIV_TIMER_LOAD_OFFSET = 0xDEC600;            //  Points  to LOAD 
const unsigned int  MPCORE_PRIV_TIMER_COUNTER_OFFSET = 0xDEC604;        //  Points  to  COUNTER 
const unsigned int  MPCORE_PRIV_TIMER_CONTROL_OFFSET = 0xDEC608;        //  Points  to  CONTROL 
const unsigned int  MPCORE_PRIV_TIMER_INTERRUPT_OFFSET = 0xDEC60C;    //  Points  to  INTERRUPT
const unsigned int letter_values[6] = {0x0E,0x5C,0x74,0x54,0x5E,0x79};
//In order J O H N D E

class SevenSegment: public DE1SoCfpga{
public:
    SevenSegment();
    ~SevenSegment();
    void Hex_ClearAll();
    void Hex_ClearSpecific(int index);
    void Hex_WriteSpecific(int index, int value);
    void Hex_WriteNumber(int number);
    void Write_Letter(char c,int offset);

private:
    unsigned int reg0_hexValue;
    unsigned int reg1_hexValue;
    int initialvalueLoadMPCore;
    int initialvalueControlMPCore;
    int initialvalueInterruptMPCore;
};
#endif //SEVENSEGMENT_H
