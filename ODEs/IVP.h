#ifndef IVP_H
#define IVP_H

#include <vector>
#include <boost/format.hpp>

using std::vector;
using std::cout;
using std::endl;
using std::ostream;

template <class T>
class IVP {
 protected:
  vector<T> y_n;
  vector<T> f_n;
  T step_size;
  int steps;
  virtual T y_nplusone(int n) = 0;
 public:
 IVP(T y, T f, T step_size, int steps) :
  step_size(step_size), steps(steps) {
    y_n.push_back(y);
    f_n.push_back(f);
  };

  virtual ~IVP() {};

  virtual void iterate()  {
    for(int n = 1; n <= this->steps; n++) {
      this->y_n.push_back(y_nplusone(n-1));
      this->f_n.push_back(this->derivative(n*this->step_size, this->y_n[n]));
    }
  };

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
