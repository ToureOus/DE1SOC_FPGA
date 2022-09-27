#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
double *v;
int count;
int size;
void Shrink() {
}
void InsertElement() {
}
void RemoveElement() {
}
void AddElement() {
}
void PrintVector() {

}
void Grow() {
}
void Initialize() {
    size = 2;
    v = new double[size];
    v[0] = 0;
    v[1] = 1;

}
void Finalize() {
    delete[] v;
}

int main() {

    Initialize();

    
    int condition;
    bool plays = true;

    while(plays){
        std::cout << "1. Print the Array" << std::endl;
        std::cout << "2. Append element at the end "<< std::endl;
        std::cout << "3. Remove last element" << std::endl;
        std::cout << "4. Insert one element" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cin >> condition;
        
        switch(condition){
            case 1: {
                cout<<"You selected \" Insert one element \""<< endl;
                break;
            }
            case 2: {
                cout<<"You selected \" Append element at the end \""<< endl;
                break;
            }
            case 3: {
                cout<<"You selected \" Remove last element \""<< endl;
                break;
            }
            case 4: {
                cout<<"You selected \" Insert one element \""<< endl;
                break;
            }
            case 5: {
                cout<<"You selected \" Exit \""<< endl;
                plays = false;
                break;
            }
            default:
                cout<<"Please select again"<< endl;
                break;
        }
        cout<<"Select an option: "<<endl;
        
    }
    Finalize();
    return 0;
}