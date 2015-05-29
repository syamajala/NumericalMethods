#include <functional>
#include <vector>

using namespace std;

class DirectFit {
 protected:
  vector<float> &x;
  vector<float> &f;
  vector<float> m;
 public:
  DirectFit(vector<float> &x, vector<float> &f);
  function<float (float)> fit(float point, int deg);
 private:
  void build_system(float point, int deg, vector<float> &M, vector<float> &sorted_f);
};
