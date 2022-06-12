#include <bits/stdc++.h>
using namespace std;

#include "matrix.hpp"

namespace internal {
struct glue {
  vector<matrix*> args;

  glue(vector<matrix*> args) : args(args) { }

  glue(matrix* lhs, matrix* rhs) {
    args = {lhs, rhs};
  }

  glue(glue lhs, matrix* rhs) {
    args = lhs.args;
    args.push_back(rhs);
  }

  vector<int> find_order() const {
    auto n = args.size();

    vector<vector<int64_t>> dp(n, vector<int64_t>(n, numeric_limits<int64_t>::max()));
    vector<vector<int>> last(n, vector<int>(n));

    for (int i = 0; i < n; ++i) {
      dp[i][i] = 0;
    }

    for (int k = 1; k < n; ++k) {
      for (int l = 0, r = k; r < n; ++l, ++r) {
        for (int m = l; m < r; ++m) {
          auto cost = dp[l][m] + dp[m + 1][r] \
            + args[l]->data.size() * args[m]->data[0].size() * args[r]->data[0].size();
          if (dp[l][r] > cost) {
            dp[l][r] = cost;
            last[l][r] = m;
          }
        }
      }
    }

    function<vector<int>(int, int)> order = [&] (int l, int r) -> vector<int> {
      if (l == r) {
        return {};
      }
      auto m = last[l][r];
      auto lhs = order(l, m), rhs = order(m + 1, r);
      copy(rhs.begin(), rhs.end(), back_inserter(lhs));
      lhs.push_back(m);
      return lhs;
    };

    return order(0, n - 1);
  }

  operator matrix() {
    auto n = args.size();

    map<int, matrix*> mp;
    for (int i = 0; i < n; ++i) {
      mp[i] = args[i];
    }

    for (auto m : find_order()) {
      auto rhs_it = mp.upper_bound(m);
      auto lhs_it = prev(rhs_it);

      auto lhs = lhs_it->second, rhs = rhs_it->second;

      auto a = lhs->data.size(), b = (*lhs)[0].size(), c = (*rhs)[0].size();
      auto product = new matrix(a, c);
      for (int i = 0; i < a; ++i) {
        for (int j = 0; j < c; ++j) {
          for (int k = 0; k < b; ++k) {
            (*product)[i][j] += (*lhs)[i][k] * (*rhs)[k][j];
          }
        }
      }

      mp.erase(lhs_it);
      mp.erase(rhs_it);
      mp[m] = product;
    }

    return *mp.begin()->second;
  }
};

glue operator*(glue lhs, matrix& rhs) {
  return glue(lhs.args, &rhs);
}
}  // namespace internal

internal::glue operator*(matrix& lhs, matrix& rhs) {
  return internal::glue(&lhs, &rhs);
}
