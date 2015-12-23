#include <iostream>
#include <valarray>
#include "ODEs/IVP.hpp"
#include "ODEs/explicit_euler.hpp"
#include "ODEs/modified_midpoint.hpp"
#include "ODEs/modified_euler.hpp"
#include "ODEs/runge_kutta.hpp"
#include "ODEs/extrapolated_midpoint.hpp"
#include "ODEs/adams_moulton.hpp"

template <class E>
class Rocket {
public:
  valarray<E> derivative(E t_n, valarray<E> x) {
    valarray<E> df = { x[1], (10000.0/(100.0 - 5.0*t_n)) - 9.8 };
    return df;
  };
};

template <class E>
class ExplicitEulerRocket : public Rocket<E>, public ODEs::ExplicitEuler<valarray<E>, E> {
 public:
  ExplicitEulerRocket(valarray<E> initial_condition, E step_size, int steps) :
    ODEs::ExplicitEuler<valarray<E>, E>(initial_condition, derivative(0, initial_condition),
                                        step_size, steps) {};

  valarray<E> derivative(E t_n, valarray<E> x) {
    return Rocket<E>::derivative(t_n, x);
  };
};

template <class E>
class ModifiedMidpointRocket : public Rocket<E>, public ODEs::ModifiedMidpoint<valarray<E>, E> {
public:
  ModifiedMidpointRocket(valarray<E> initial_condition, E step_size, int steps) :
    ODEs::ModifiedMidpoint<valarray<E>, E>(initial_condition,
                                           derivative(0, initial_condition),
                                           step_size, steps) {};

  valarray<E> derivative(E t_n, valarray<E> x) {
    return Rocket<E>::derivative(t_n, x);
  };
};

template <class E>
class ModifiedEulerRocket : public Rocket<E>, public ODEs::ModifiedEuler<valarray<E>, E> {
public:
  ModifiedEulerRocket(valarray<E> initial_condition, E step_size, int steps) :
    ODEs::ModifiedEuler<valarray<E>, E>(initial_condition, derivative(0, initial_condition),
                                        step_size, steps) {};

  valarray<E> derivative(E t_n, valarray<E> x) {
    return Rocket<E>::derivative(t_n, x);
  };
};

template <class E>
class RungeKuttaRocket : public Rocket<E>, public ODEs::RungeKutta<valarray<E>, E> {
 public:
  RungeKuttaRocket(valarray<E> initial_condition, E step_size, int steps) :
    ODEs::RungeKutta<valarray<E>, E>(initial_condition, derivative(0, initial_condition),
                                     step_size, steps) {};

  valarray<E> derivative(E t_n, valarray<E> x) {
    return Rocket<E>::derivative(t_n, x);
  };
};

template <class E>
class ExtrapolatedMidpointRocket : public Rocket<E>,
                                   public ODEs::ExtrapolatedMidpoint<valarray<E>, E> {
 public:
  ExtrapolatedMidpointRocket(valarray<E> initial_condition, E step_size, int steps, E M) :
    ODEs::ExtrapolatedMidpoint<valarray<E>, E>(initial_condition, derivative(0, initial_condition),
                                               step_size, steps, M) {};

  valarray<E> derivative(E t_n, valarray<E> x) {
    return Rocket<E>::derivative(t_n, x);
  };
};

template <class E>
class AdamsMoultonRocket : public Rocket<E>, public ODEs::AdamsMoulton<valarray<E>, E> {
 public:
  AdamsMoultonRocket(ODEs::IVP<valarray<E>, E> &ic, E step_size, int steps) :
    ODEs::AdamsMoulton<valarray<E>, E>(ic, step_size, steps) {};

  valarray<E> derivative(E t_n, valarray<E> x) {
    return Rocket<E>::derivative(t_n, x);
  };
};

int main() {
  double del_t = 1.0;
  int steps = 10;

  valarray<double> initial_condition = {0.0, 0.0};

  cout << "Explicit Euler: \n";
  ExplicitEulerRocket<double> explicit_r(initial_condition, del_t, steps);
  explicit_r.iterate();
  cout << explicit_r;

  cout << "Modified Midpoint: \n";
  ModifiedMidpointRocket<double> midpoint_r(initial_condition, del_t, steps);
  midpoint_r.iterate();
  cout << midpoint_r;

  cout << "Modified Euler: \n";
  ModifiedEulerRocket<double> euler_r(initial_condition, del_t, steps);
  euler_r.iterate();
  cout << euler_r;

  cout << "Runge Kutta: \n";
  RungeKuttaRocket<double> rk_r(initial_condition, del_t, steps);
  rk_r.iterate();
  cout << rk_r;

  cout << "Extrapolated Midpoint: \n";
  ExtrapolatedMidpointRocket<double> exmidpoint_r(initial_condition, del_t, steps, 16.0);
  exmidpoint_r.iterate();
  cout << exmidpoint_r;

  cout << "Adams Moulton: \n";
  RungeKuttaRocket<double> rk_ic(initial_condition, del_t, 3);
  rk_ic.iterate();

  ODEs::IVP<valarray<double>, double> &ic = rk_ic;
  AdamsMoultonRocket<double> am_r(ic, del_t, steps);
  am_r.iterate();
  cout << am_r;
}
