#include <iostream>
#include "explicit_euler.h"
#include "lib.h"

using namespace std;

/*
 * Solve the initial value ODE:
 * y' = f(t, y), y(t_0) = y_0
 * using the finite difference equation:
 * y_(n+1) = y_n + del_t*f_n
 */

ExplicitEuler::ExplicitEuler(double initial_condition, double step_size, int steps)
  : initial_condition(initial_condition), step_size(step_size), steps(steps) {
}

double ExplicitEuler::y_nplusone(double y_n, double f_n) {
  return y_n + this->step_size*f_n;
}

void ExplicitEuler::iterate() {
  int cur_step = 1;
  double f_nminus1 = f_n.back();
  double y_nminus1 = y_n.back();

  while(cur_step <= this->steps) {
    f_n.push_back(f_nplusone(0.0, y_nminus1));
    f_nminus1 = f_n.back();
    y_n.push_back(y_nplusone(y_nminus1, f_nminus1));
    y_nminus1 = y_n.back();
    f_nminus1 = y_nminus1;
    cur_step++;
  }
}

void ExplicitEuler::print_table() {
  int cur_step = 0;
  while(cur_step <= this->steps) {
    cout.precision(dbl::digits10);
    cout << "n = " << cur_step*step_size << "\tf_" << cur_step << " = " << f_n[cur_step]
	 << "\ty_" << cur_step << " = " << y_n[cur_step] << endl;
    cur_step++;
  }
}
