Étude 1. "Overload me if you can". `T[]` is equivalent to `T*` in function declarations.

`overload_me_if_you_can.hpp`:

```cpp
void overload_me_if_you_can(char* ptr) { }
void overload_me_if_you_can(char arr[]) { }

```

`$ g++ overload_me_if_you_can.hpp`:

```cpp
overload_me_if_you_can.hpp:2:6: error: redefinition of 'overload_me_if_you_can'
void overload_me_if_you_can(char arr[]) { }
     ^
overload_me_if_you_can.hpp:1:6: note: previous definition is here
void overload_me_if_you_can(char* ptr) { }
     ^
1 error generated.
```

Étude 2. "Array size detective". Function argument that is a references to an array has type `T(&)[N]`.

`array_size_detective.hpp`:

```cpp
#include <cstddef>

template <typename T, std::size_t N>
constexpr std::size_t array_size_detective(T (&)[N]) {
  return N;
}

constexpr int arr[] = {2, 3, 4, 7, 11};
static_assert(array_size_detective(arr) == 5);
```

No more `sizeof(arr)/sizeof(arr[0])`!