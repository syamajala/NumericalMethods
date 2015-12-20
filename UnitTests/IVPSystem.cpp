#include <iostream>
#include <valarray>
#include "ODEs/runge_kutta.hpp"

template <class E>
class RungeKuttaRocket : public ODEs::RungeKuttaSystem<E> {
 public:
  RungeKuttaRocket(valarray<E> initial_condition, E step_size, int steps) :
    ODEs::RungeKuttaSystem<E>(initial_condition, derivative(0, initial_condition), step_size, steps) {};

  valarray<E> derivative(E t_n, valarray<E> x) {
    valarray<E> df = { x[1], (10000.0/(100.0 - 5.0*t_n)) - 9.8 };
    return df;
  };
};

int main() {
  double del_t = 1.0;
  int steps = 10;

  valarray<double> initial_condition = {0.0, 0.0};
  RungeKuttaRocket<double> rk_r(initial_condition, del_t, steps);
  rk_r.iterate();
  cout << rk_r << endl;
}
