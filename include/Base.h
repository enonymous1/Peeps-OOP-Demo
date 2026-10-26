#pragma once

#include <memory>
#include <ostream>
#include <string>
#include <utility>

/// Abstract base type for all peep records.
///
/// A `Base` owns its name and defines the polymorphic interface every peep
/// type must implement: how it is displayed, and how it is cloned without
/// slicing the derived type away.
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

    /// Write this record to `out`. Taking the stream as a parameter (instead
    /// of writing straight to `std::cout`) is what makes the classes
    /// testable: tests can pass a `std::ostringstream` and inspect it.
    virtual void DisplayRecord(std::ostream& out) const = 0;

    /// Return a new heap-allocated copy of this object, preserving its
    /// concrete derived type.
    virtual std::unique_ptr<Base> Clone() const = 0;

private:
    std::string name_;
};
