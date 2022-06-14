#include <cassert>
#include <fstream>
#include <random>
#include <tuple>
#include <utility>
#include <vector>

#include "naive.hpp"

auto generate(int seed, int count,
              int min_dimension, int max_dimension,
              int min_value, int max_value) {
  std::mt19937 generator(seed);
  std::uniform_int_distribution<int>
    dimension_distribution(min_dimension, max_dimension);
  std::uniform_int_distribution<int> 
    entry_distridution(min_value, max_value);

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

  return std::make_tuple(dimensions, matrices, result);
}

int main(int argc, char** argv) {
  assert(argc == 7);

  int seed = std::stoi(argv[1]);
  int count = std::stoi(argv[2]);

  int min_dimension = std::stoi(argv[3]);
  int max_dimension = std::stoi(argv[4]);

  int min_value = std::stoi(argv[5]);
  int max_value = std::stoi(argv[6]);

  const auto [dimensions, matrices, result] \
    = generate(seed, count, min_dimension, max_dimension, min_value, max_value);

  const auto filename = std::to_string(seed) + "_" + std::to_string(count) + "_" \
    + std::to_string(min_dimension) + "_" + std::to_string(max_dimension) + "_" \
    + std::to_string(min_value) + "_" + std::to_string(max_value);

  std::ofstream input_file;
  input_file.open("in" + filename + ".txt", std::ios::out);

  input_file << count << "\n";
  for (auto dimension : dimensions) {
    input_file << dimension << " ";
  }
  input_file << "\n";

  for (const auto& matrix : matrices) {
    input_file << matrix;
  }

  input_file.close();

  std::ofstream output_file;
  output_file.open("ans" + filename + ".txt", std::ios::out);
  
  output_file << result;

  output_file.close();

  return 0;
}
