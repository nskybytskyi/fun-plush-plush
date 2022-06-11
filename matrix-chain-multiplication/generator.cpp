#include <iostream>
#include <random>
#include <vector>

#include "naive.hpp"

int main() {
  std::mt19937 generator(time(0));
  std::uniform_int_distribution<int> dimension_distribution(100, 500);
  std::uniform_int_distribution<int> entry_distridution(1, 5);

  const int count = 10;

  std::vector<int> dimensions(count + 1);
  for (auto& dimension : dimensions) {
    dimension = dimension_distribution(generator);
  }

  std::vector<matrix> matrices(count);
  for (int i = 0; i < count; ++i) {
    matrices[i] = matrix(dimensions[i], dimensions[i + 1]);
    matrices[i].initialize_random(entry_distridution, generator);
  }

  auto product = matrices[0] * matrices[1];
  for (int i = 2; i < count; ++i) {
    product = product * matrices[i];
  }
  matrix result = product;


  std::cout << count << "\n";
  for (auto dimension : dimensions) {
    std::cout << dimension << " ";
  }
  std::cout << "\n";

  for (const auto& matrix : matrices) {
    std::cout << matrix;
  }

  std::cerr << result;

  return 0;
}
