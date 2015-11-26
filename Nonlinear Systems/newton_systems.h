#ifndef NONLINEAR_SYSTEMS_NEWTON_SYSTEM_H
#define NONLINEAR_SYSTEMS_NEWTON_SYSTEM_H

#include <functional>
#include <vector>
#include <algorithm>
#include <lapacke.h>

using std::vector;
using std::multiplies;

namespace NonlinearSystems {
  template <class T>
    class NewtonSystems {
  private:
    vector<T> initial_guesses;
    vector<T> e;
  public:
  NewtonSystems(vector<T> initial_guesses, vector<T> e) :
    initial_guesses(initial_guesses), e(e) {};

    virtual vector<T> f(vector<T> &x) = 0;
    virtual vector<vector<T>> df(vector<T> &x) = 0;

    vector<T> iterate() {
      vector<T> r = f(initial_guesses);
      // multiply vector r by -1
      transform(r.begin(), r.end(), r.begin(), bind1st(multiplies<T>(), -1));
      vector<vector<T>> dfx = df(initial_guesses);

      vector<T> flat_dfx;

      for(size_t i = 0; i < dfx.size(); i++)
        flat_dfx.insert(end(flat_dfx), begin(dfx[i]), end(dfx[i]));

      char TRANS = 'N';
      int NRHS = 1;
      int IPIV[dfx.size()];

      LAPACKE_dgetrf(LAPACK_ROW_MAJOR, dfx.size(), dfx.size(), &(flat_dfx[0]),
                     dfx.size()+2, &IPIV[0]);

      LAPACKE_dgetrs(LAPACK_ROW_MAJOR, TRANS, dfx.size(), NRHS, &(flat_dfx[0]), dfx.size()+2,
                     &(IPIV[0]), &(r[0]), r.size());

      return r;
    };

  };
}
#endif
