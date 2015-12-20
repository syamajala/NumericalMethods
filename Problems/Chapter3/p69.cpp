#include <iostream>
#include <cmath>
#include "NonlinearSystems/iterative.hpp"
#include "NonlinearSystems/newton.hpp"

using std::cout;
using std::endl;

static constexpr double _R = 461.495;
static constexpr double _a = 1703.28;
static constexpr double _b = 0.00169099;
static constexpr double _P = 10000.0;
static constexpr double _T = 800.0;

template <class R>
class VanDerWaal {
public:
  R f(R v) {
    return _P*pow(v, 3) - (_P*_b + _R*_T)*pow(v, 2) + _a*v - _a*_b;
  };
};

template <class R>
class Iterative_VanDerWaal: public VanDerWaal<R>, public NonlinearSystems::Iterative<R> {
public:
  Iterative_VanDerWaal(R a, R b, R e) : NonlinearSystems::Iterative<R>(a, b, e) {};

  R f(R v) {
    return VanDerWaal<R>::f(v);
  };
};


template <class R>
class Newton_VanDerWaal: public VanDerWaal<R>, public NonlinearSystems::Newton<R> {
public:
  Newton_VanDerWaal(R initial_guess, R e) : NonlinearSystems::Newton<R>(initial_guess, e) {};

  R f(R v) {
    return VanDerWaal<R>::f(v);
  }

  R df(R v) {
    return 3*_P*pow(v, 2) - 2*(_P*_b + _R*_T)*v + _a;
  }
};

int main() {
  double e = 0.00000001;
  cout.precision(15);

  double a = _R*(_T-50.0)/_P;
  double b = _R*(_T+50.0)/_P;

  Iterative_VanDerWaal<double> iv(_R*_T/_P, _R*(_T+100.0)/_P, e);
  cout << "Secant: " << iv.iterate_secant() << endl;

  Newton_VanDerWaal<double> nv(a, e);
  cout << "Newton: " << nv.iterate() << endl;
}
