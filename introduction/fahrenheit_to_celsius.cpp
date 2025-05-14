// write a program to convert a temperature from fahrenheit to celsius
#include <iostream>

using namespace std;

int main(){
  double temp_fahrenheit, temp_celsius;
  
  cout << "Temperature in Fahrenheit: ";
  cin >> temp_fahrenheit;
  
  temp_celsius = 5.0*(temp_fahrenheit - 32.0)/9.0;  
  cout << "Temperature in Celsius: " << temp_celsius << endl;
  
  return 0;
}
