#include "matrix.hpp"

matrix operator*(const matrix& lhs, const matrix& rhs) {
  const int a = lhs.data.size();
  const int b = lhs[0].size();
  const int c = rhs[0].size();

  matrix out(a, c);
  for (int i = 0; i < a; ++i) {
    for (int j = 0; j < c; ++j) {
      for (int k = 0; k < b; ++k) {
        out[i][j] += lhs[i][k] * rhs[k][j];
      }
    }
  }
  return out;
}
