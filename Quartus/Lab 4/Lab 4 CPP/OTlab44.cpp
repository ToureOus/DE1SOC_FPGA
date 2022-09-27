#include <iostream>
using namespace std;

int main()
{
   char arr[33] = {0};
   int user;
   cout << "Please enter an unsigned decimal number:";
   cin >> user;

   int size = 32;
   for (int temp = user; temp; temp >>= 1)
       size--;
   for (int i = 0; i < size; ++i)
       arr[i] = ((user >> (size - i - 1)) & 1) ? '1' : '0';
   cout << arr << endl;
   return 0;
}

