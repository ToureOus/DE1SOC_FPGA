#include <iostream>
#include <string>

int main(){
   int array[8];
   int input;
   int count = 0;
   while(count < 8){
      std::cout << "Enter a number for bit [" << count << "]: ";
      std::cin >> input;
      if(!(input == 0 || input == 1)){
         std::cout << "Please enter either 0 or 1" << std::endl;
      }
      else{
         array[count] = input;
         count ++;
      }
   }
   int decimal = 0;
   std::string hex;
   for(int i = 0; i < 8; i++){
       if(i == 0){decimal += array[i];}
       else{
         int temp = 1;
         for(int j = 0; j < i; j++){temp = 2*temp*array[i];}
         decimal += temp;
       }
   }
   std::cout << "Decimal: " << decimal << std::endl;
   int temp = decimal;
   int remainder;
   char temp_string;
   while(temp != 0){
      remainder = temp%16;
      if(remainder < 10){temp_string = '0' + remainder;}
      else if(remainder == 10){temp_string = 'A';}
      else if(remainder == 11){temp_string = 'B';}
      else if(remainder == 12){temp_string = 'C';}
      else if(remainder == 13){temp_string = 'D';}
      else if(remainder == 14){temp_string = 'E';}
      else{temp_string = 'F';}
      hex.insert(hex.begin(),temp_string);
      temp = temp/16;
   }
   std::cout << "Hexadecimal: " << hex << std::endl;
   return 0;
}
