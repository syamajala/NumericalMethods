#include <iostream>
#include <math.h>
#include "ODEs/IVP.hpp"
#include "ODEs/implicit_euler.hpp"
#include "ODEs/explicit_euler.hpp"
#include "ODEs/modified_midpoint.hpp"
#include "ODEs/modified_euler.hpp"
#include "ODEs/runge_kutta.hpp"
#include "ODEs/extrapolated_midpoint.hpp"
#include "ODEs/adams_moulton.hpp"

static constexpr double alpha = 4.0*10.0e-13;
static constexpr double T_a4 = pow(250.0, 4);

template<class E>
class Radiation {
 public:
  E derivative(E t_n, E T_n) {
    return -alpha*(pow(T_n, 4) - T_a4);
  };
};

template <class E>
class ImplicitRadiation : public Radiation<E>, public ODEs::ImplicitEuler<E> {
public:
  ImplicitRadiation(E initial_condition, E step_size, int steps) :
    ODEs::ImplicitEuler<E>(initial_condition, derivative(0, initial_condition),
                           step_size, steps) {};
  E derivative(E t_n, E T_n) {
    return Radiation<E>::derivative(t_n, T_n);
  };

  E dderivative(E t_n, E T_n) {
    return -4*alpha*pow(T_n, 3);
  };

};

template <class E>
class ExplicitRadiation : public Radiation<E>, public ODEs::ExplicitEuler<E> {
public:
  ExplicitRadiation(E initial_condition, E step_size, int steps) :
    ODEs::ExplicitEuler<E>(initial_condition, derivative(0, initial_condition),
                           step_size, steps) {};
    E derivative(E t_n, E T_n) {
      return Radiation<E>::derivative(t_n, T_n);
    };
};

template <class E>
class ModifiedMidpointRadiation : public Radiation<E>, public ODEs::ModifiedMidpoint<E> {
public:
  ModifiedMidpointRadiation(E initial_condition, E step_size, int steps) :
    ODEs::ModifiedMidpoint<E>(initial_condition, derivative(0, initial_condition),
                              step_size, steps) {};
  E derivative(E t_n, E T_n) {
    return Radiation<E>::derivative(t_n, T_n);
  };
};

template <class E>
class ModifiedEulerRadiation : public Radiation<E>, public ODEs::ModifiedEuler<E> {
public:
  ModifiedEulerRadiation(E initial_condition, E step_size, int steps) :
    ODEs::ModifiedEuler<E>(initial_condition, derivative(0, initial_condition),
                           step_size, steps) {};
  E derivative(E t_n, E T_n) {
    return Radiation<E>::derivative(t_n, T_n);
  };
};

template <class E>
class RungeKuttaRadiation : public Radiation<E>, public ODEs::RungeKutta<E> {
public:
  RungeKuttaRadiation(E initial_condition, E step_size, int steps) :
    ODEs::RungeKutta<E>(initial_condition, derivative(0, initial_condition),
                     step_size, steps) {};
  E derivative(E t_n, E T_n) {
    return Radiation<E>::derivative(t_n, T_n);
  };
};

template <class E>
class ExtrapolatedMidpointRadiation : public Radiation<E>, public ODEs::ExtrapolatedMidpoint<E> {
public:
  ExtrapolatedMidpointRadiation(E initial_condition, E step_size, int steps, int M) :
    ODEs::ExtrapolatedMidpoint<E>(initial_condition, derivative(0, initial_condition),
                            step_size, steps, M) {};
  E derivative(E t_n, E T_n) {
    return Radiation<E>::derivative(t_n, T_n);
  };
};

template <class E>
class AdamsMoultonRadiation : public Radiation<E>, public ODEs::AdamsMoulton<E> {
public:
  AdamsMoultonRadiation(ODEs::IVP<E> &ic, E step_size, int steps) :
    ODEs::AdamsMoulton<E>(ic, step_size, steps) {};
  E derivative(E t_n, E T_n) {
    return Radiation<E>::derivative(t_n, T_n);
  };
};


int main() {
  double initial_condition = 2500.0;
  double del_t = 2.0;
  int steps = 5;

  cout << "Implicit Euler: \n";
  ImplicitRadiation<double> implicit_r(initial_condition, del_t, steps);
  implicit_r.iterate();
  cout << implicit_r << endl;

  cout << "Explicit Euler: \n";
  ExplicitRadiation<double> explicit_r(initial_condition, del_t, steps);
  explicit_r.iterate();
  cout << explicit_r << endl;

  cout << "Modified Midpoint: \n";
  ModifiedMidpointRadiation<double> midpoint_r(initial_condition, del_t, steps);
  midpoint_r.iterate();
  cout << midpoint_r << endl;

  cout << "Modified Euler: \n";
  ModifiedEulerRadiation<double> euler_r(initial_condition, del_t, steps);
  euler_r.iterate();
  cout << euler_r << endl;

  cout << "Runge Kutta: \n";
  RungeKuttaRadiation<double> rk_r(initial_condition, del_t, steps);
  rk_r.iterate();
  cout << rk_r << endl;

  cout << "Extrapolated Modified Midpoint: \n";
  ExtrapolatedMidpointRadiation<double> exmidpoint_r(initial_condition, del_t, steps, 16);
  exmidpoint_r.iterate();
  cout << exmidpoint_r << endl;

  cout << "Adams Moulton: \n";
  RungeKuttaRadiation<double> rk_ic(initial_condition, del_t, 3);
  rk_ic.iterate();

  ODEs::IVP<double> &ic = rk_ic;
  AdamsMoultonRadiation<double> am_r(ic, del_t, steps);
  am_r.iterate();
  cout << am_r;

  return 0;
}

