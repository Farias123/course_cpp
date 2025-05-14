// Compute the operation z = (x + 10)/(3y)
#include <iostream>

using namespace std;

int main(){
  double x = 5.0;
  double y = 2.0;
  double z;
  
  z = (x + 10)/(3*y);
  
  cout << "The value of z is: " << z << endl;

  return 0;
}
