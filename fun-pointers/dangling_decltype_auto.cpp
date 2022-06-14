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

