#include <iostream>
#include <vector>
#include <cmath>
#include "include/radians.hpp"
#include "NonlinearSystems/iterative.hpp"
#include "NonlinearSystems/newton.hpp"

using std::cout;
using std::vector;

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
class Iterative_Link: public Link<R>, public NonlinearSystems::Iterative<R> {
public:
  Iterative_Link(R a, R b, R e) : NonlinearSystems::Iterative<R>(a, b, e) {};
  R f(R x) {
    return Link<R>::f(x);
  }
};

template <class R>
class Newton_Link: public Link<R>, public NonlinearSystems::Newton<R> {
public:
  Newton_Link(R initial_guess, R e) : NonlinearSystems::Newton<R>(initial_guess, e) {};
  R f(R x) {
    return Link<R>::f(x);
  }
  R df(R x) {
    return (5.0/2.0)*sin(x) - sin(this->alpha-x);
  }
};

static constexpr double r1 = 10.0;
static constexpr double r2 = 6.0;
static constexpr double r3 = 8.0;
static constexpr double r4 = 4.0;
static const double theta_4 = deg_to_rad<double>(220.0);

template <class R>
class Systems_Link : public NonlinearSystems::Newton<vector<R>> {
public:
  Systems_Link(vector<R> initial_guesses, vector<R> e) :
    NonlinearSystems::Newton<vector<R>>(initial_guesses, e) {};

  vector<R> f(vector<R> &x) {
    vector<R> fx = {
      r2*cos(x[0]) + r3*cos(x[1]) + r4*cos(theta_4) - r1,
      r2*sin(x[0]) + r3*sin(x[1]) + r4*sin(theta_4)
    };
    return fx;
  };

  // Must be in column major format
  vector<vector<R>> df(vector<R>& x) {
    vector<vector<R>> dfx = {
      { -r2*sin(x[0]),  r2*cos(x[0])},
      {  -r3*sin(x[1]), r3*cos(x[1]) }
    };
    return dfx;
  };
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

  vector<double> initial_guesses = { deg_to_rad<double>(30.0),
                                     deg_to_rad<double>(0.0) };
  vector<double> ev(2, 0.000001);
  Systems_Link<double> slink(initial_guesses, ev);
  vector<double> r = slink.iterate();

  cout << "Newton Systems: ";
  for(auto &x : r)
    cout << rad_to_deg<double>(x) << " ";
  cout << endl;

  return 0;
}
