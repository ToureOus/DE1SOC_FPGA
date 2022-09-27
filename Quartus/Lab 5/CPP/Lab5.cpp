#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double* myarr;
int size;
int count;

void Initialize();
void Finalize();
void print_instruction();
void ArrayPrint();
void ArrayGrow();
void ArrayAppend();
void ArrayShrink();
void RemoveLast();
void ArrayInsert();

void Initialize(){
    count = 0;
    size = 2;
    myarr = new double[size];
    myarr[0] = 0;
    myarr[1] = 0;
}

void Finalize(){
    delete[] myarr;
}

void print_instruction(){
    std::cout << "Main menu:" << std::endl;
    std::cout << std::endl;
    std::cout << "1.Print the array" << std::endl;
    std::cout << "2.Append element at the end" << std::endl;
    std::cout << "3.Remove last element" << std::endl;
    std::cout << "4.Insert one element" << std::endl;
    std::cout << "5.Exit" << std::endl;
    std::cout << std::endl;
    std::cout << "Select an option :";
}

void ArrayPrint(){
    std::cout << "You selected \"Print the array\"" << std::endl;
    for(int i = 0; i < count; i++){std::cout << myarr[i] << " ";}
    std::cout << std::endl;
    std::cout << std::endl;
}

void ArrayGrow(){
    // std::cout << std::endl;
    // std::cout << "The old array is: ";
    // ArrayPrint();
    // std::cout << std::endl;
    // prev_size = size;
    size *= 2;
    double* new_arr = new double[size] {0};
    for(int i = 0; i < count; i++){new_arr[i] = myarr[i];}
    delete[] myarr;
    myarr = new_arr;
    // std::cout << "Vector Grown" << std::endl;
    // std::cout << "Previous Capacity: " << prev_size << " elements" << std::endl;
    // std::cout << "New Capacity: " << size << " elements" << std::endl;
    // std::cout << std::endl;
    // std::cout << "The new array is: ";
    // ArrayPrint();
    // std::cout << std::endl;
}

void ArrayAppend(){
    double num;
    std::cout << "You selected \"Append element at the end\"" << std::endl;
    std::cout << "Please enter the number you want to append: ";
    std::cin >> num;
    if(count+1 > size){ArrayGrow();}
    myarr[count] = num;
    count += 1;
    std::cout << std::endl;
}

void ArrayShrink(){
    size = size/2;
    double* new_arr = new double[size] {0};
    for(int i = 0; i < count; i++){new_arr[i] = myarr[i];}
    delete[] myarr;
    myarr = new_arr;
}

void RemoveLast(){
    std::cout << "You selected \"Remove last element\"" << std::endl;
    myarr[count-1] = 0;
    if((double(count-1) < double(size*0.3)) && (size > 2)){ArrayShrink();}
    if(count-1 >= 0){count -= 1;}
}

void ArrayInsert(){
    std::cout << "You selected \"Insert one element\"" << std::endl;
    int index;
    std::cout << "Enter the INDEX of the array you want to insert to: ";
    std::cin >> index;
    double num;
    std::cout << "Enter the NUMBER you want to insert to the array: ";
    std::cin >> num;
    if(index < count){
        if(count >= size) {size *= 2;}
        double *new_arr = new double[size]{0};
        for (int i = 0; i < index; i++) { new_arr[i] = myarr[i]; }
        new_arr[index] = num;
        for (int i = index; i < count; i++) { new_arr[i + 1] = myarr[i]; }
        delete[] myarr;
        myarr = new_arr;
    }
    else if(index > count){
        if(count >= size){ArrayGrow();}
        myarr[count] = num;
    }
    else{myarr[index] = num;}
    count += 1;
}

int main(){
    Initialize();
    bool condition = true;
    while(condition){
        int choice;
        print_instruction();
        std::cin >> choice;
        switch(choice){
            case 1:
                ArrayPrint();
                break;
            case 2:
                ArrayAppend();
                break;
            case 3:
                RemoveLast();
                break;
            case 4:
                ArrayInsert();
                break;
            case 5:
                std::cout << "You selected \"Exit\"" << std::endl;
                condition = false;
                break;
            default:
                std::cout << "Value Error, please re-enter your number!" << std::endl;
                std::cout << std::endl;
                break;
        }
    }
    Finalize();
    return 0;
}
