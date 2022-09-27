#include <iostream>
#include "SevenSegment.h"

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
      std::cout << "Do you want to stop? ";
      char v;
      std::cin >> v;
      if(v == 'y'){condition = false;}
    }
    std::cout << "Terminating...!" << std::endl;
    delete display;
    return 0;
}
