#include <iostream>
#include "SevenSegment.h"

int main(){
/*
    SevenSegment *display = new SevenSegment;
    std::cout << "Program Starting...!" << std::endl;
    bool condition = true;
    int hex_value;
    while(condition){
      std::cout << "Please enter a number for display (in the range -16777216 to 16777215):";
      std::cin >> hex_value;
      display->Hex_WriteNumber(hex_value);
      std::cout << "Do you want to stop? ";
      char v;
      std::cin >> v;
      if(v == 'y'){condition = false;}
    }
    std::cout << "Terminating...!" << std::endl;
    delete display;
    return 0;
    */

   SevenSegment *display = new SevenSegment; 
   std::cout << "Program Starting...!" << std::endl;  
   
   int counter = 200000000;   // timeout = 1/(200 MHz) x 200x10^6 = 1 sec 
   display->RegisterWrite(MPCORE_PRIV_TIMER_LOAD_OFFSET, counter); 
   display->RegisterWrite(MPCORE_PRIV_TIMER_CONTROL_OFFSET, 3); 
 
   unsigned int enterindex = 0;  //points to Hex0 display 
   unsigned int entervalue = 0;  //points to segment0 
   unsigned int count = 20; 
   
   while(count > 1){
     if(display -> RegisterRead(MPCORE_PRIV_TIMER_INTERRUPT_OFFSET) != 0){
       display -> RegisterWrite(MPCORE_PRIV_TIMER_INTERRUPT_OFFSET,1);
       entervalue = entervalue ^ 0x01;
       display -> Hex_WriteSpecific(enterindex,entervalue);
       count--;
     }
   }
   delete display;  
   std::cout << "Terminating...!" << std::endl; 
   return 0; 
} 

