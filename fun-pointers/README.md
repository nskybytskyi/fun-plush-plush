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

Étude 3. "Dangling `decltype(auto)`". When applied to an lvalue-expression more complicated than a name, `decltype(auto)` returns an lvalue, potentially leading to undefined behavior.

`dangling_decltype_auto.cpp`:

```cpp
#include <cassert>

decltype(auto) dangling_decltype_auto() {
  int x = 42;
  return (x);
}

int main() {
  auto x = dangling_decltype_auto();
  int y = 0;
  assert(x == 17);
}
```

`$ g++ -std=c++17 dangling_decltype_auto.cpp -o a`:

```cpp
dangling_decltype_auto.cpp:5:11: warning: reference to stack memory associated with local variable 'x' returned [-Wreturn-stack-address]
  return (x);
          ^
1 warning generated.
```

`$ ./a`

```
Assertion failed: (x == 17), function main, file dangling_decltype_auto.cpp, line 11.
zsh: abort      ./a
```
