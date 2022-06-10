#include <bits/stdc++.h>
using namespace std;

struct matrix {
  vector<vector<int>> data;

  matrix(vector<vector<int>> data) : data(data) { }

  matrix(int first, int second) : data(first, vector(second, 0)) { }
};

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

  operator matrix() {
    auto n = args.size();
    vector dp(n, vector(n, 1e9));
    vector last(n, vector(n, 0));

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

    map<int, matrix*> mp;
    for (int i = 0; i < n; ++i) {
      mp[i] = args[i];
    }

    for (auto m : order(0, n - 1)) {
      auto it = mp.find(m);
      auto nxt = next(it);

      auto lhs = it->second, rhs = nxt->second;

      auto a = lhs->data.size(), b = lhs->data[0].size(), c = rhs->data[0].size();
      auto product = new matrix(a, c);
      for (int i = 0; i < a; ++i) {
        for (int k = 0; k < c; ++k) {
          for (int j = 0; j < b; ++j) {
            product->data[i][j] += lhs->data[i][j] * rhs->data[j][k];
          }
        }
      }

      mp.erase(nxt);
      mp[m] = product;
    }

    return *mp.begin()->second;
  }
};

glue operator*(matrix lhs, matrix rhs) {
  return glue(&lhs, &rhs);
}

glue operator*(glue lhs, matrix rhs) {
  return glue(lhs.args, &rhs);
}

int main() {
  matrix a = {{{1, 2, 3}, {4, 5, 6}}};
  matrix b = {{{7, 8}, {9, 10}, {11, 12}}};
  matrix c = {{{13, 14, 15}, {16, 17, 18}}};
  matrix d = a * b * c;

  for (auto row : d.data) {
    for (auto val : row) {
      cout << val << " ";
    }
    cout << "\n";
  }

  return 0;
}
