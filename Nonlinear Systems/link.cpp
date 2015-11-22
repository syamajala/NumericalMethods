#include <iostream>
#include <cmath>
#include "radians.h"
#include "iterative.h"
#include "newton.h"

using namespace std;

template <class R>
class Link {
protected:
  const R alpha = deg_to_rad<R>(40.0);
public:
  R f(R x) {
    return (5.0/3.0)*cos(this->alpha)-(5.0/2.0)*cos(x)+(11.0/6.0)-cos(this->alpha-x);
  }
};

template <class R>
class Iterative_Link: public Link<R>, public Iterative<R> {
public:
  Iterative_Link(R a, R b, R e) : Iterative<R>(a, b, e) {};
  R f(R x) {
    return Link<R>::f(x);
  }
};

template <class R>
class Newton_Link: public Link<R>, public Newton<R> {
public:
  Newton_Link(R initial_guess, R e) : Newton<R>(initial_guess, e) {};
  R f(R x) {
    return Link<R>::f(x);
  }
  R df(R x) {
    return (5.0/2.0)*sin(x) - sin(this->alpha-x);
  }
};

int main() {
  double a = deg_to_rad<double>(30.0);
  double b = deg_to_rad<double>(40.0);
  double e = .000001;
  cout.precision(15);

  Iterative_Link<double> il(a, b, e);
  cout << "Bisection: " << rad_to_deg<double>(il.iterate_bisection()) << endl;
  cout << "False Position: " << rad_to_deg<double>(il.iterate_false_position()) << endl;
  cout << "Secant: " << rad_to_deg<double>(il.iterate_secant()) << endl;

  Newton_Link<double> nl(a, e);
  cout << "Newton: " << rad_to_deg<double>(nl.iterate()) << endl;

  return 0;
}
