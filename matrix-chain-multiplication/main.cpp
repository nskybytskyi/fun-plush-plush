#include <iostream>
#include <vector>

#ifdef OPTIMAL
#include "optimal.hpp"
#else
#include "naive.hpp"
#endif

int main() {
  int count;
  std::cin >> count;

  std::vector<int> dimensions(count + 1);
  for (auto& dimension : dimensions) {
    std::cin >> dimension;
  }

  std::vector<matrix> matrices(count);
  for (int i = 0; i < count; ++i) {
    matrices[i] = matrix(dimensions[i], dimensions[i + 1]);
    std::cin >> matrices[i];
  }

  auto product = matrices[0] * matrices[1];

  #ifdef OPTIMAL
    // `product` has type `internal::glue`
    assert(typeid(product) != typeid(matrices[0]));
  #else
    assert(typeid(product) == typeid(matrices[1]));
  #endif

  for (int i = 2; i < count; ++i) {
    product = product * matrices[i];
  }

  // conversion step only necessary for `glue`
  matrix result = product;

  std::cout << result;

  return 0;
}
