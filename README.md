# Finite-State Number Parser

A C++ finite-state machine that validates integer, decimal, and scientific-notation strings.

## Motivation

This project explores how to model number-string validation as a modular finite-state machine, with each state handling the characters valid at that point in the input.

## Design Overview

### Intuition

Since we are trying to determine a valid sequence of characters by parsing them one by one to determine if transitions are valid, the problem can be conceptually reduced to a Finite State Machine.

### Approach

The parser reads the input from left to right. Each character causes a transition to another state. If a character is not valid in the current state, the parser moves to an invalid sink state, from which it cannot recover.

- **Start (`Init`):** Begins parsing and routes the first character to a number, sign, or leading-decimal state.
- **Signs (`PlusMinus`):**
  - `PlusMinus<SignType::Regular>` handles an optional sign at the start of the number.
  - `PlusMinus<SignType::Exponential>` handles an optional sign immediately after `e` or `E`.
- **Decimal point (`Dot`):**
  - `Dot<DotType::Init>` handles a leading decimal point, as in `.45`, and requires a digit next.
  - `Dot<DotType::Regular>` handles a decimal point after integer digits; it can transition to fractional digits or an exponent, so `4.` is allowed.
- **Numbers (`Number`):**
  - `Number<Type::Regular>` handles digits before a decimal point or exponent.
  - `Number<Type::Fraction>` handles digits after a decimal point and before an exponent.
  - `Number<Type::Exponential>` handles digits in the exponent.
- **Exponent (`Exponent`):** Handles `e` or `E` after the mantissa and transitions to an exponent sign or exponent digits.
- **Invalid (`Invalid`):** A sink state for malformed input.

A string is accepted only when parsing ends in a complete numeric state. This accepts `4.` but rejects incomplete values such as `.` and `1e`.

## Build and test

Requirements: CMake 3.12 or newer, a C++17 compiler, `pkg-config`, and the
CppUnit development package. CMake checks for these dependencies but does not
download or install them. Install CppUnit and `pkg-config` with your platform's
package manager before configuring the project.

For example, in the MSYS2 MINGW64 environment:

```sh
pacman -S mingw-w64-x86_64-cppunit mingw-w64-x86_64-pkgconf
```

From the project root, configure a fresh build directory, build the test
executable, then run CTest from that build directory. Testing is enabled
explicitly. `Debug` selects the configuration for multi-configuration
generators and is ignored by single-configuration generators. To choose a
specific installed generator, add an option such as `-G "MinGW Makefiles"` to
the configure command.

GitHub Actions also builds and runs the unit tests on pushes and pull requests
with Ninja, Unix Makefiles, and MinGW Makefiles.

```sh
cmake -S . -B build-ctest -DBUILD_TESTING=ON
cmake --build build-ctest --config Debug
cd build-ctest
ctest -C Debug --output-on-failure
```
