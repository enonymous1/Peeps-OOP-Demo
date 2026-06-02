# Peeps-OOP-Demo

This project is a simple console-based management system for "Peeps" (People). It is written in C++ and demonstrates inheritance, polymorphism, cloning via a virtual `clone()` method, and smart pointer memory management.

## Project structure

- `include/`
  - `App.h`
  - `Base.h`
  - `Teacher.h`
  - `InputUtils.h`
  - `Student.h`
- `src/`
  - `main.cpp`
  - `App.cpp`
  - `InputUtils.cpp`
  - `Base.cpp`
  - `Teacher.cpp`
  - `Student.cpp`
- `CMakeLists.txt`
- `build/`

## Modules

- `App`: Contains the application flow, menu, and user interaction logic.
- `InputUtils`: Handles validated integer input and input buffer clearing.
- `Base`: Defines the abstract base class for all peeps.
- `Teacher` / `Student`: Concrete derived types that implement `DisplayRecord()` and `clone()`.

## Build

### Using CMake

```bash
mkdir -p build
cd build
cmake ..
cmake --build .
```

### Using g++ directly

```bash
g++ -std=c++14 src/main.cpp src/App.cpp src/InputUtils.cpp src/Base.cpp src/Teacher.cpp src/Student.cpp -Iinclude -o build/Peeps_OOP_Demo
```

## Run

```bash
./build/Peeps_OOP_Demo
```

## Usage

The program shows a menu with four options:

1. Add a peep
2. Display all peeps
3. Clone a peep
4. Exit

## Extending the project

To add a new peep type, follow these steps:

1. Add a new header in `include/`, e.g. `Manager.h`, inheriting from `Base`.
2. Add an implementation file in `src/`, e.g. `Manager.cpp`, implementing `DisplayRecord()` and `clone()`.
3. Add the new source file to `CMakeLists.txt` and update any build scripts.
4. Update `src/App.cpp` to include the new header, add a menu option, and construct the new type when selected.

For example, a `Trainer` class can store a specialization field instead of salary and provide a `DisplayRecord()` implementation that prints the trainer's name and specialization.

## Notes

- The project uses `std::unique_ptr` to manage dynamic object memory.
- The code is organized into `src/` and `include/` to keep implementation and headers separate.
- `InputUtils` centralizes input validation logic.
