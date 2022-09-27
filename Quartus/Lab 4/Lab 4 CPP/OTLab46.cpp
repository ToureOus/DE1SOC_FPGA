
#include <iostream>
#include <string>
using namespace std;

void PrintArray (int v[], int size)
{
    cout<<"your "<<size<<" bit number is: ";
    for(int i=0;i<size;i++)
        cout<< v[i]<<"";
    cout<<endl;
}
void PrintArrayAddress (int v[], int size) {
    for (int i = 0; i < size; i++) {
        cout << "Address of slot " << i << ": " << &v[i] << endl;

    }
}





int main(){
    int array[8];
    int input;
    int count = 0;
    int condition;
    bool goodjob = true;
    std::cout << "Welcome to Lab 4, Please select one of the options below: " << std::endl;
    while(goodjob){
        std::cout << "\"1\" to Convert an unsigned binary number to Decimal"
                     " and Hexadecimal." << std::endl;
        std::cout << "\"2\" to display a 32-bit number representation of an unsigned"
                     " Decimal number." << std::endl;
        std::cout << "\"3\" to exit the main menu which ends the program."
                  << std::endl;
        std::cout << "Your input: ";
        std::cin >> condition;
        switch(condition){
            case 1:{
                while(count < 8){
                    std::cout << "Enter a number for bit [" << count << "]: ";
                    std::cin >> input;
                    if(!(input == 0 || input == 1)){std::cout << "Please enter either 0 or 1" << std::endl;}
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
                PrintArray(array,8);
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
                std::cout << std::endl;
                count = 0;
                PrintArrayAddress(array,8);
            }
                break;


            case 2:{
                std::cout << "Please enter a decimal number: ";
                std::cin >> input;
                std::string output;
                int remainder;
                int bin_arr[32] = {0};
                int c = 32;
                while(input != 0){
                    remainder = input%2;
                    bin_arr[c] = remainder;
                    c--;
                    input = input/2;
                }
                PrintArray(bin_arr,32 );
                PrintArrayAddress(bin_arr,32);
                std::cout << std::endl;
            }
                break;
            case 3:
                std::cout << "Goodbye!" << std::endl;
                std::cout << std::endl;
                goodjob = false;
                break;
            default:
                std::cout << "Your command cannot be recognized"
                             ", try again: " << std::endl;
        }
    }
    return 0;
}
