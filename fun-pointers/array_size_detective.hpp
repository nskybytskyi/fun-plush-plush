#include <cstddef>

template <typename T, std::size_t N>
constexpr std::size_t array_size_detective(T(&)[N]) {
  return N;
}

constexpr int arr[] = {2, 3, 4, 7, 11};
static_assert(array_size_detective(arr) == 5);
static_assert(sizeof(arr) / sizeof(arr[0]) == 5);

