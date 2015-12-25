#ifndef NONLINEAR_SYSTEMS_NEWTON_H
#define NONLINEAR_SYSTEMS_NEWTON_H

#include <vector>
#include <armadillo>

using std::vector;
using namespace arma;

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


  template <class T>
  class Newton<vector<T>> {
  private:
    vector<T> initial_guesses;
    Col<T> e;
  public:
    Newton<vector<T>>(vector<T> initial_guesses, vector<T> e) :
    initial_guesses(initial_guesses), e(conv_to<Col<T>>::from(e)) {};

    virtual vector<T> f(vector<T> &x) = 0;
    virtual vector<vector<T>> df(vector<T> &x) = 0;

    bool convergence(Col<T> x, Col<T> prev_x) {
      Col<T> del_x =  x - prev_x;
      del_x = sqrt(square(del_x));
      return all((del_x <= e) == true);
    }

    vector<T> iterate() {
      Col<T> x = conv_to<Col<T>>::from(initial_guesses);
      Col<T> prev_x(x.size(), fill::zeros);

      while(!convergence(x, prev_x)) {
        vector<T> vx = conv_to<vector<T>>::from(x);
        vector<T> fx = f(vx);
        Col<T> r = conv_to<Col<T>>::from(fx);
        r = -1*r;
        vector<vector<T>> dfx = df(vx);
        vector<T> vflat_dfx;
        for(size_t i = 0; i < dfx.size(); i++)
          vflat_dfx.insert(end(vflat_dfx), begin(dfx[i]), end(dfx[i]));

        Mat<T> mdfx = conv_to<Mat<T>>::from(vflat_dfx);
        mdfx = reshape(mdfx, dfx.size(), dfx.size());
        r = solve(mdfx, r);
        prev_x = x;
        x += r;
      }

      return conv_to<vector<T>>::from(x);
    }
  };
}
#endif
