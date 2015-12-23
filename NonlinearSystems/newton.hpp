#ifndef NONLINEAR_SYSTEMS_NEWTON_H
#define NONLINEAR_SYSTEMS_NEWTON_H

namespace NonlinearSystems {
  template <class T>
  class Newton {
  protected:
    T initial_guess;
    T e;
  public:
  Newton(T initial_guess, T e)  : initial_guess(initial_guess), e(e) {};
    virtual T f(T x) = 0;
    virtual T df(T x) = 0;

    T iterate() {
      T fphi_i = f(this->initial_guess);
      T dfphi_i = df(this->initial_guess);
      T phi_iplusone = this->initial_guess - (fphi_i/dfphi_i);

      while(abs(phi_iplusone - fphi_i) >= e && abs(fphi_i) >= e) {
        fphi_i = f(phi_iplusone);
        dfphi_i = df(phi_iplusone);
        phi_iplusone = phi_iplusone - (fphi_i/dfphi_i);
      }

      return phi_iplusone;
    }
  };
}
#endif
