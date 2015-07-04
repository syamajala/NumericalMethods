#ifndef IVP_H
#define IVP_H

#include <vector>
#include <boost/format.hpp>

using namespace std;

template <class T>
class IVP {
 protected:
  vector<T> y_n;
  vector<T> f_n;
  T initial_condition;
  T step_size;
  int steps;
 public:
 IVP(T step_size, int steps) :
  step_size(step_size), steps(steps) {};
  virtual void iterate() = 0;
  virtual T derivative(T t_n, T y_n) = 0;

  friend ostream& operator<< (ostream &os, const IVP<T> &obj)  {
    for(int cur_step = 0; cur_step <= obj.steps; cur_step++) {
      os << boost::format("n = %=i\ty_%i = %f\tf_%i = %f\n")
        % (cur_step*obj.step_size) % cur_step % obj.y_n[cur_step]
        % cur_step % obj.f_n[cur_step];
    }
    return os;
  };

};

#endif
