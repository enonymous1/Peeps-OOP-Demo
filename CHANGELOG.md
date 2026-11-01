# Changelog

All notable changes to this project are documented here. The format
follows Keep a Changelog, and versioning follows Semantic Versioning.

## [2.1.0] - 2026-10-31

Staff-review fixes, applied in four parts. User-visible behaviour is
unchanged except for the whitespace-name fix; the sample-session
transcript is byte-identical to before.

### Fixed

- Salary bounds disagreed between App (0–1,000,000) and the setter
  (any non-negative value). Bounds are now constants on the owning
  type (`Teacher::kMinSalary` / `kMaxSalary`,
  `Student::kMinGpa` / `kMaxGpa`), read by App.
- Whitespace-only names were accepted and stored verbatim. Names are
  now trimmed, and a whitespace-only line is rejected.
- Non-finite input (NaN) could pass the range check on an
  implementation that parses it. Validated input now rejects
  non-finite values explicitly.
- Unhandled exceptions in `main()` terminated without a message.
  `main()` now catches `std::exception`, prints it, and returns 1.

### Changed

- `App` no longer knows concrete types or their fields. A
  `PeepFactory` registry (`include/PeepFactory.h`,
  `src/PeepFactory.cpp`) builds the type menu and prompts for each
  type's fields; adding a type is one registry entry, not an `App.cpp`
  edit.
- `Base` gains `TypeName()`, so a record's type is identifiable
  without `dynamic_cast`.
- `Clone()` and the validated-input helpers are `[[nodiscard]]`.
- Banners go through a shared `PrintBanner` helper (`include/Banner.h`).
- CMake warnings extracted into a `peeps_add_warnings` function;
  `CMakePresets.json` reformatted from a minified single line.
- CI now uses `ctest --preset test`, sets `permissions: contents:
  read`, and adds an Ubuntu Debug + ASan/UBSan job.

### Added

- Tests for the salary upper bound, whitespace/trimmed names,
  non-finite GPA rejection, a student smoke test, empty
  display/clone, invalid menu choice then valid, and factory
  creation through the registry. The test runner names each test
  and isolates exceptions per test.
- README rewritten with Description, Prerequisites, Installation,
  Local Development, and Deployment sections, Mermaid architecture
  and clone-sequence diagrams, and a demo GIF rendered from a real
  terminal session (`docs/assets/demo.gif`).

## [2.0.0] - 2026-10-26

- C++14 to C++17. The old tree did not build under its declared
  C++14, because `InputUtils` used `std::string_view`.
- Fixed the EOF hang: input helpers looped forever on Ctrl-D /
  piped EOF. End-of-input now exits cleanly.
- `App` and input helpers stream-injected (no hard-coded `cin` /
  `cout`), making the code testable.
- `clone()` renamed to `Clone()`; Student/Teacher copy operations
  defaulted; setter invariants added (GPA 0–4, salary non-negative).
- `peeps_core` library target, CMake presets, compiler warnings,
  zero-dependency CTest suite, GitHub Actions CI on Ubuntu, Windows,
  and macOS, MIT LICENSE, `.clang-format`, and a landing-page README
  with a real terminal-captured sample session.
