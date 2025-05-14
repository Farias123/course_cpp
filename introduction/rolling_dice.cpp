// write a program for rolling dice
#include <iostream>
#include <ctime>

using namespace std;

int main(){
  srand(time(0));
  
  short value_rolled1 = rand() % 6 + 1;
  short value_rolled2 = rand() % 6 + 1;
  cout << "Dice values rolled: " << value_rolled1 
       << ", " << value_rolled2 << endl;

  return 0;
}
