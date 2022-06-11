#include "matrix.hpp"

matrix operator*(const matrix& lhs, const matrix& rhs) {
  const int a = lhs.data.size();
  const int b = lhs.data[0].size();
  const int c = rhs.data[0].size();

  matrix out(a, c);
  for (int i = 0; i < a; ++i) {
    for (int j = 0; j < c; ++j) {
      for (int k = 0; k < b; ++k) {
        out.data[i][j] += lhs.data[i][k] * rhs.data[k][j];
      }
    }
  }
  return out;
}
