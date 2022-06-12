**Matrix chain multiplication** is an optimization problem concerning the most efficient way to multiply a given sequence of matrices.  The problem may be solved using dynamic programming.

```
.
├── matrix.hpp     // basic matrix class with some common utilities
├── naive.hpp      // naive implementation of matrix::operator*
├── optimal.hpp    // optimal implementation of matrix::operator*
├── generator.cpp  // correctness and performance testcases generator
├── main.cpp       // correctness and interface compliance checks
└── tests          // pregenerated tests
```

Checklist:

- [x] passing tests;
- [x] command line arguments for generator;
- [x] tests with variable number of matrices;

- [x] common matrix class;
- [x] overload `matrix::operator[]`;
- [ ] change type of `matrix.data` to `std::array`;

- [ ] `std::enable_if`;
- [ ] template size parameters.

