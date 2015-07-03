#ifndef DIFFERENCE_H
#define DIFFERENCE_H

using namespace std;

template <class T>
class Difference {
 protected:
  vector<vector<T>> table;
  virtual void build_table(const T point, const int deg) {};
 public:
  T operator()(int i, int j) {
    if ((i > 0 && i < table.size()) && (j > 0 && j < table[i].size()))
      return table[i][j];
  }
};

#endif
