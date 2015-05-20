#include <iostream>
#include <cmath>
#include "iterative.h"

using namespace std;

double rad_to_deg(double x) {
  return x*(180.0/M_PI);
}

const double deg_to_rad(double x) {
  return x*(M_PI/180.0);
}

class Link: public Iterative {
protected:
  const double alpha = deg_to_rad(40.0);
public:
  Link(double a, double b, double e) : Iterative(a, b, e) {};
  
  double f(double x) {
    return (5.0/3.0)*cos(this->alpha)-(5.0/2.0)*cos(x)+(11.0/6.0)-cos(this->alpha-x);
  }
};

int main() {
  double a = deg_to_rad(30.0);
  double b = deg_to_rad(40.0);
  double e = .000001;
  Link *l = new Link(a, b, e);
  double r = l->iterate_false_position();
  cout << rad_to_deg(r) << endl;
  return 0;
}
