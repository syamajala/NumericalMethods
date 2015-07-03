/*
 * Solve the initial value ODE:
 * y' = f(t, y), y(t_0) = y_0
 * using the finite difference equation:
 * y_(n+1) = y_n + del_t*f_n
 */

#ifndef EXPLICIT_EULER_H
#define EXPLICIT_EULER_H

#include <vector>
#include <ostream>
#include <boost/format.hpp>

using namespace std;

template <class T>
class ExplicitEuler {
 protected:
  T initial_condition;
  T step_size;
  int steps;
  vector<T> y_n;
  vector<T> f_n;
 public:
 ExplicitEuler(T initial_condition, T step_size, int steps) :
  initial_condition(initial_condition), step_size(step_size), steps(steps) {};
  virtual ~ExplicitEuler() {};
  virtual T derivative(T t_n, T y_n) = 0;

  T y_nplusone(T y_n, T f_n) {
    return y_n + this->step_size*f_n;
  };

  void iterate()  {
    int cur_step = 1;
    T f_nminus1 = f_n.back();
    T y_nminus1 = y_n.back();

    while(cur_step <= this->steps) {
      f_n.push_back(derivative(cur_step*step_size, y_nminus1));
      f_nminus1 = f_n.back();
      y_n.push_back(y_nplusone(y_nminus1, f_nminus1));
      y_nminus1 = y_n.back();
      f_nminus1 = y_nminus1;
      cur_step++;
    }
  };

  friend ostream& operator<< (ostream &os, const ExplicitEuler<T> &obj)  {
    int cur_step = 0;
    while(cur_step <= obj.steps) {
      os << boost::format("n = %=2i \t y_%i = %f \t f_%i = %f\n") % (cur_step*obj.step_size) % cur_step % obj.y_n[cur_step]
        % cur_step % obj.f_n[cur_step+1];
      cur_step++;
    }
    return os;
  };

};
 #endif
