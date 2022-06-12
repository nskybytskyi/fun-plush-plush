#ifndef MATRIX_HPP
#define MATRIX_HPP 1

#include <iostream>
#include <random>
#include <vector>

struct matrix {
  std::vector<std::vector<int>> data;

  matrix(int first = 0, int second = 0)
    : data(std::vector<std::vector<int>>(first, std::vector<int>(second))) { }

  template <class RNG>
  void initialize_random(std::uniform_int_distribution<int> dist, RNG& gen) {
    for (auto& row : data) {
      for (auto& val : row) {
        val = dist(gen);
      }
    }
  }

  std::vector<int>& operator[](int row) {
    return data[row];
  }

  const std::vector<int>& operator[](int row) const {
    return data[row];
  }
};

std::istream& operator>>(std::istream& is, matrix& mat) {
  for (auto& row : mat.data) {
    for (auto& val : row) {
      is >> val;
    }
  }
  return is;
}

std::ostream& operator<<(std::ostream& os, const matrix& mat) {
  for (const auto& row : mat.data) {
    for (auto val : row) {
      os << val << " ";
    }
    os << "\n";
  }
  return os;
}

#endif  // MATRIX_HPP
