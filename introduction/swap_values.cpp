#include <iostream>

using namespace std;

int main(){
  int a = 1;
  int b = 2;
  
  int temp = a;
  a = b;
  b = temp;

  cout << "Value of a: " << a << endl
       << "Value of b: " << b << endl;

  return 0;
}
