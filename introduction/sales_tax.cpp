// given a sales value of $95000, a state tax rate of 4% and a county tax rate of 2%,
// compute the state tax, county tax and total tax being paid.
#include <iostream>

using namespace std;

int main(){
  double sales = 95'000.00;
  double state_tax_rate = 0.04;
  double county_tax_rate = 0.02;
  
  double state_tax = sales*state_tax_rate;
  double county_tax = sales*county_tax_rate;
  
  double total_tax = state_tax + county_tax;
  
  cout << "Sales total: $" << sales << endl
       << "State tax paid: $" << state_tax << endl
       << "County tax paid: $" << county_tax << endl
       << "Total tax paid: $" << total_tax << endl;

  return 0;
}
