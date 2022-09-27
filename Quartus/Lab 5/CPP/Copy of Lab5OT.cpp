#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
double *v;
int count;
int size;
void Shrink();
void InsertElement();
void RemoveElement();
void PrintVector();
void Grow();
void Initialize();
void Finalize();

void Shrink() {
    size /= 2;
    double *nv = new double[size*2]{0};
    for(int i = 0;i<count;i++){nv[i] = v[i];}
        delete[] v;
    v = nv;
    ++count;

}
void InsertElement() {
    int i,ele,ind;
    cout<<"Enter Desired Index: "<<endl;
    cin >>ind;
    cout<<"Enter Element to Insert: "<<endl;
    cin >>ele;
    if(ind >= size){
        Grow();
    }
    for(i=count;i>=ind;i--) {
        v[i] = v[i-1];
    }
    v[i] = ele;
    ++count;
}
void RemoveElement() {
//    int rVal;
//    cout<< <<endl;
//    cin>>rVal;
    v[count-1] = 0;
    if((double(count-1) < double(size*.3)) && (size > 2)){
        Shrink();
    }
    else{
        cout<<"There are no variables to delete."<<endl;
    }
    if(count-1 >= 0){
        --count;
    }


}
void AddElement() {
    int val;
    cout<< "Enter your element:"<<endl;
    cin>>val;
    if(count == size){
        Grow();
        v[count] = val;
    }
    else{
        v[count] = val;
    }
    ++count;

}
void PrintVector() {
    int x;
    for(x=0;x<size;x++){
        cout.precision(0);
        cout<<"v["<<x<<"] = "<<v[x]<<endl;
    }


}
void Grow() {
        int i;
        cout<<"Previous array size: "<< size <<endl;
        double *nv = new double[size*2]{0};
        for(i=0;i<size;i++) {
            nv[i] = v[i];
        }
        delete[]v;
        v = nv;
        size *= 2;
        cout<<"Vector grown"<<endl;
        cout<<"New array size: "<< size<<endl;

}
void Initialize() {
    size =1;
    count = 1;
    v = new double[size];
    v[0] = 1;

}
void Finalize() {
    delete[] v;
}

int main() {
    Initialize();
    int condition;
    bool plays = true;
    while(plays){
        cout<<"Select an option: "<<endl;
        std::cout << "1. Print the Array" << std::endl;
        std::cout << "2. Append element at the end "<< std::endl;
        std::cout << "3. Remove last element" << std::endl;
        std::cout << "4. Insert one element" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cin >> condition;

        switch(condition){
            case 1: {
                cout<<"You selected \" Print the array \""<< endl;
                PrintVector();
                break;
            }
            case 2: {
                cout<<"You selected \" Append element at the end \" "<< endl;
                AddElement();
                break;
            }
            case 3: {
                cout<<"You selected \" Remove last element \""<< endl;
                RemoveElement();



                break;
            }
            case 4: {
                cout<<"You selected \" Insert one element \""<< endl;
                InsertElement();
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


    }

    Finalize();
    return 0;
}
