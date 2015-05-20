#include <iostream>
#include <cmath>
#include "lib.h"
#include "iterative.h"
#include "newton.h"

using namespace std;

class Link {
protected:
  const double alpha = deg_to_rad(40.0);
public:
  double f(double x) {
    return (5.0/3.0)*cos(this->alpha)-(5.0/2.0)*cos(x)+(11.0/6.0)-cos(this->alpha-x);
  }
};

class Iterative_Link: public Link, public Iterative {
public:
  Iterative_Link(double a, double b, double e) : Iterative(a, b, e) {};
  double f(double x) {
    return Link::f(x);
  }
};

class Newton_Link: public Link, public Newton {
public:
  Newton_Link(double initial_guess, double e) : Newton(initial_guess, e) {};
  double f(double x) {
    return Link::f(x);
  }
  double df(double x) {
    return (5.0/2.0)*sin(x) - sin(this->alpha-x);
  }
};


int main() {
  double a = deg_to_rad(30.0);
  double b = deg_to_rad(40.0);
  double e = .000001;
  Iterative_Link il = Iterative_Link(a, b, e);
  double r = il.iterate_false_position();
  cout.precision(dbl::digits10);
  cout << rad_to_deg(r) << endl;

  Newton_Link nl = Newton_Link(a, e);
  r = nl.iterate();
  cout << rad_to_deg(r) << endl;
  
  return 0;
}
