#include <cmath>

using namespace std;

template <class T>
class Iterative {
 protected:
  T a;
  T b;
  T e;

 public:
  Iterative(T a, T b, T e) : a(a), b(b), e(e) {};
  virtual T f(T x) = 0;
    
  T iterate_bisection() {
    T p = a;
    T q = b;
    T r = (this->a+this->b)/2.0;
  
    while(abs(q - p) >= e) {
      if(f(p)*f(r) < 0)
	q = r;
      else if (f(p)*f(r) > 0)
	p = r;
      else if (f(p)*f(r) == 0)
	break;
      r = (p+q)/2.0;
    }

    return r;
  }

  T iterate_false_position() {
    T dg = 0.0;
    T p = a;
    T q = b;
    T r = 0.0;
    T fa = 0.0;
    T fb = 0.0;
    T fc = 0.0;
    
    while (abs(q - p) >= e) {
      fb = f(q);
      fa = f(p);
      dg = (fb - fa)/(q-p);
      r = q - fb/dg;
      fc = f(r);

      if(fa*fc < 0)
	q = r;
      else if (fa*fc > 0)
	p = r;
      else if (fa*fc == 0)
	break;      
    }

    return r;
  }

  T iterate_secant() {
    T t = 0.0;
    T x_i = this->a;
    T x_ip1 = this->b;

    T dg_xi = (f(x_ip1) - f(x_i))/(x_ip1-x_i);
    t = x_ip1;
    x_ip1 = x_i - (f(x_i)/dg_xi);
    x_i = t;
  
    while(abs(x_ip1 - x_i) >= e) {
      dg_xi = (f(x_ip1) - f(x_i))/(x_ip1-x_i);
      t = x_ip1;
      x_ip1 = x_i - (f(x_i)/dg_xi);
      x_i = t;
    }

    return x_ip1;
  }
};
