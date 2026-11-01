#pragma once

#include <memory>
#include <ostream>
#include <string>
#include <string_view>
#include <utility>

/// Abstract base type for all peep records.
///
/// A `Base` owns its name and defines the polymorphic interface every peep
/// type must implement: how it is displayed, and how it is cloned without
/// slicing the derived type away.
///
/// Why a vector<unique_ptr<Base>> and not a vector<Base>? A vector<Base>
/// would slice every Teacher/Student down to its Base part on insertion.
/// unique_ptr keeps the full derived object alive and gives the vector
/// sole ownership: no manual delete, no shared ownership to reason about.
class Base {
public:
    Base() = default;

    explicit Base(std::string name) : name_(std::move(name)) {}

    Base(const Base&) = default;
    Base& operator=(const Base&) = default;
    Base(Base&&) noexcept = default;
    Base& operator=(Base&&) noexcept = default;

    /// Virtual destructor so derived objects are destroyed correctly
    /// through a `Base` pointer.
    virtual ~Base() = default;

    void SetName(std::string name) { name_ = std::move(name); }

    const std::string& GetName() const noexcept { return name_; }

    /// The human-readable type name ("Teacher", "Student"). This is
    /// how callers identify a record's type without dynamic_cast.
    virtual std::string_view TypeName() const = 0;

    /// Write this record to `out`. Taking the stream as a parameter (instead
    /// of writing straight to `std::cout`) is what makes the classes
    /// testable: tests can pass a `std::ostringstream` and inspect it.
    virtual void DisplayRecord(std::ostream& out) const = 0;

    /// Return a new heap-allocated copy of this object, preserving its
    /// concrete derived type. The return type must be unique_ptr<Base>,
    /// not unique_ptr<Derived>: C++ covariant return types do not apply
    /// to unique_ptr, so the base return type is required, not a style
    /// choice. Copying through a Base value would slice the derived
    /// fields away; Clone() is the escape hatch.
    /// [[nodiscard]] because silently discarding a clone is a bug.
    [[nodiscard]] virtual std::unique_ptr<Base> Clone() const = 0;

private:
    std::string name_;
};
