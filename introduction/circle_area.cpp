#include <iostream>
#include <cmath>

using namespace std;

int main(){
    double radius;
    double area;
    const double pi = 3.14;

    cout << "Enter the radius of the cirle: ";
    cin >> radius;

    area = pi*pow(radius, 2);
    cout << "The area of the circle is: " << area << endl;

    return 0;
}