# Peeps-OOP-Demo

[![CI](https://github.com/enonymous1/Peeps-OOP-Demo/actions/workflows/ci.yml/badge.svg)](https://github.com/enonymous1/Peeps-OOP-Demo/actions/workflows/ci.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](CMakeLists.txt)

A tiny console app that teaches the one OOP idea textbooks usually hand-wave: **cloning a polymorphic object without slicing it**.

You add Teachers and Students, display them, and clone one. The clone keeps its real type — a cloned Teacher is still a Teacher, with its salary intact — even though the list only ever holds `unique_ptr<Base>`. Everything else in the program exists to make that one idea easy to read.

## What it teaches

- Inheritance and polymorphism through an abstract `Base` class
- Polymorphic cloning via a virtual `Clone()` method (the prototype pattern, in miniature)
- Ownership with `std::unique_ptr` — no raw `new` / `delete` anywhere
- Separating the record model from console I/O, so the model is testable

## Quick start

Prerequisites: a C++17 compiler and CMake 3.27 or newer. No libraries to install.

```sh
cmake --preset release
cmake --build --preset release
./out/build/release/Peeps_OOP_Demo
```

On Windows the binary is `out/build/release/Release/Peeps_OOP_Demo.exe`.

## Sample session

This is a real interactive session captured through a terminal, so the typed input is shown after each prompt (add a teacher, display, clone, display again, exit):

```
------------------------Peeps-OOP-Demo------------------------
	1) Add a peep
	2) Display all peeps
	3) Clone a peep
	4) Exit

	Selection: 1
------------------------What kind of peep?------------------------

		1) Teacher
		2) Student

	Selection: 1
------------------------Name?------------------------
		Name:  Ada

------------------------Salary?------------------------
		Salary:  50000
------------------------Peeps-OOP-Demo------------------------
	1) Add a peep
	2) Display all peeps
	3) Clone a peep
	4) Exit

	Selection: 2
------------------------Display Records------------------------

		1. Ada :: Salary == 50000

------------------------Peeps-OOP-Demo------------------------
	1) Add a peep
	2) Display all peeps
	3) Clone a peep
	4) Exit

	Selection: 3
------------------------Clone a peep------------------------
		There are 1 peeps in the records, choose one to clone.
		Peep number: 1
Cloned peep 1.
------------------------Peeps-OOP-Demo------------------------
	1) Add a peep
	2) Display all peeps
	3) Clone a peep
	4) Exit

	Selection: 2
------------------------Display Records------------------------

		1. Ada :: Salary == 50000

		2. Ada :: Salary == 50000

------------------------Peeps-OOP-Demo------------------------
	1) Add a peep
	2) Display all peeps
	3) Clone a peep
	4) Exit

	Selection: 4
```

## Usage

The menu has four options:

1. Add a peep (Teacher with a salary, or Student with a GPA)
2. Display all peeps, numbered
3. Clone a peep by number
4. Exit

Input is validated: non-numeric input and out-of-range values are rejected and re-prompted, and end-of-input (Ctrl-D, or a piped file running out) exits cleanly instead of looping forever.

## How cloning works

Records live in a `std::vector<std::unique_ptr<Base>>`. Each derived class implements `Clone()` as `std::make_unique<Derived>(*this)`, so copying through a `Base` pointer still produces the full derived object. `DisplayRecord()` takes an output stream, which is also why the classes are unit-testable without touching the console.

## Tests

Tests are a single zero-dependency binary — no Catch2 or GoogleTest to fetch, so the test build works offline. They cover clone type/field preservation and independence, setter range invariants, input validation (invalid, out-of-range, trailing junk), EOF handling, and a full scripted app session.

```sh
cmake --preset release
cmake --build --preset release
ctest --test-dir out/build/release -C Release --output-on-failure
```

CI runs the same build and tests on Ubuntu, Windows, and macOS.

## Extending the project

To add a new peep type, for example `Manager`:

1. Add `include/Manager.h` inheriting from `Base`, implementing `DisplayRecord()` and `Clone()`.
2. Add `src/Manager.cpp`.
3. Add the new source file to the `peeps_core` target in `CMakeLists.txt`.
4. Update `src/App.cpp` to include the header, add a menu option, and construct the new type when selected.

## Non-goals

This stays a teaching demo on purpose. It is not a database, it has no persistence, and there is no delete/edit/search — adding those would bury the cloning lesson under CRUD code.

## What changed in the 2.0 modernization

- C++14 to C++17. The old tree did not actually build under its declared C++14: `InputUtils` used `std::string_view`, which is C++17.
- Fixed the EOF hang: the old input helpers looped forever on Ctrl-D / piped EOF.
- `App` and the input helpers now take streams instead of hard-coding `std::cin` / `std::cout`, which is what makes the tests possible.
- `clone()` renamed to `Clone()` for consistency with `SetName` / `GetName` / `DisplayRecord`.
- Hand-written copy constructors/assignments in `Student` / `Teacher` replaced with `= default` — they did exactly what the default does.
- Setters now enforce their own invariants (`SetGPA` rejects outside [0.0, 4.0], `SetSalary` rejects negatives) instead of relying only on the input layer.
- Added a `peeps_core` library target, CMake presets, compiler warnings, tests, GitHub Actions CI, an MIT LICENSE, and a `.clang-format` file.

<details>
<summary>Project layout</summary>

- `include/` — `App.h`, `Base.h`, `InputUtils.h`, `Student.h`, `Teacher.h`
- `src/` — `main.cpp`, `App.cpp`, `InputUtils.cpp`, `Student.cpp`, `Teacher.cpp`
- `tests/` — `test_peeps.cpp` (zero-dependency test binary, run via CTest)
- `CMakeLists.txt`, `CMakePresets.json`
- `.github/workflows/ci.yml`, `.clang-format`, `LICENSE`

</details>
