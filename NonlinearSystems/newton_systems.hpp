#ifndef NONLINEAR_SYSTEMS_NEWTON_SYSTEM_H
#define NONLINEAR_SYSTEMS_NEWTON_SYSTEM_H

#include <functional>
#include <vector>
#include <armadillo>

using std::vector;
using namespace arma;

namespace NonlinearSystems {
  template <class T>
    class NewtonSystems {
  private:
    vector<T> initial_guesses;
    Col<T> e;
  public:
  NewtonSystems(vector<T> initial_guesses, vector<T> e) :
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
