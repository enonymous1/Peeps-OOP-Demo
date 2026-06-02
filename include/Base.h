#pragma once

#include <memory>
#include <string>

/// Abstract base type for all peep records.
///
/// The Base class encapsulates the common `name` property and provides
/// the polymorphic interface required by the application. Derived types
/// must implement both display and clone behavior.
class Base
{
private:
    /// Owned name string for the record.
    std::string name;

public:
    /// Default construct a Base object with an empty name.
    Base() = default;

    /// Default copy constructor is sufficient because std::string handles
    /// deep copy semantics correctly.
    Base(const Base& _other) = default;

    /// Default copy assignment operator preserves the same behavior.
    Base& operator=(const Base& _other) = default;

    /// Virtual destructor ensures derived objects are destroyed properly
    /// through a Base pointer.
    virtual ~Base() = default;

    /// Set the display name for this record.
    ///
    /// Using std::string here keeps ownership simple and avoids
    /// manual memory management.
    void SetName(const std::string& name);

    /// Retrieve the stored name.
    ///
    /// Returning a const reference avoids an extra string copy while
    /// preserving immutability for the caller.
    const std::string& GetName() const noexcept;

    /// Display the record contents.
    ///
    /// Derived classes must implement how their own fields are shown.
    virtual void DisplayRecord() const = 0;

    /// Clone this object polymorphically.
    ///
    /// Derived classes must return a new heap-allocated copy of themselves.
    virtual std::unique_ptr<Base> clone() const = 0;
};