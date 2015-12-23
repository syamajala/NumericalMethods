#include <iostream>
#include <valarray>
#include "ODEs/explicit_euler.hpp"
#include "ODEs/runge_kutta.hpp"

template <class E>
class ExplicitEulerRocket : public ODEs::ExplicitEuler<valarray<E>, E> {
 public:
  ExplicitEulerRocket(valarray<E> initial_condition, E step_size, int steps) :
    ODEs::ExplicitEuler<valarray<E>, E>(initial_condition, derivative(0, initial_condition), step_size, steps) {};

  valarray<E> derivative(E t_n, valarray<E> x) {
    valarray<E> df = { x[1], (10000.0/(100.0 - 5.0*t_n)) - 9.8 };
    return df;
  };
};

template <class E>
class RungeKuttaRocket : public ODEs::RungeKutta<valarray<E>, E> {
 public:
  RungeKuttaRocket(valarray<E> initial_condition, E step_size, int steps) :
    ODEs::RungeKutta<valarray<E>, E>(initial_condition, derivative(0, initial_condition), step_size, steps) {};

  valarray<E> derivative(E t_n, valarray<E> x) {
    valarray<E> df = { x[1], (10000.0/(100.0 - 5.0*t_n)) - 9.8 };
    return df;
  };
};

int main() {
  double del_t = 1.0;
  int steps = 10;

  valarray<double> initial_condition = {0.0, 0.0};

  cout << "Explicit Euler: \n";
  ExplicitEulerRocket<double> ee_r(initial_condition, del_t, steps);
  ee_r.iterate();
  cout << ee_r;

  cout << "Runge Kutta: \n";
  RungeKuttaRocket<double> rk_r(initial_condition, del_t, steps);
  rk_r.iterate();
  cout << rk_r;
}
