// The header guard prevents the header file from being included more than once.
#pragma once

#include "Base.h"

/// A concrete Base-derived type representing a teacher.
///
/// Teacher stores a salary and implements the Base interface required
/// by the application for displaying and cloning polymorphic records.
class Teacher : public Base
{
private:
    /// The salary associated with this teacher record.
    int salary = 0;

public:
    /// Default constructor initializes the teacher with zero salary.
    Teacher();

    /// Copy constructor performs a shallow copy of the salary and Base state.
    Teacher(const Teacher& _other);

    /// Copy assignment operator updates this object from another Teacher.
    ///
    /// This preserves the same behavior as the copy constructor for the
    /// derived Teacher type.
    Teacher& operator=(const Teacher& _other);

    /// Default virtual destructor ensures proper cleanup through Base pointers.
    ~Teacher() override = default;

    /// Set the salary for this teacher.
    ///
    /// The caller is responsible for ensuring the salary is within
    /// an acceptable range.
    void SetSalary(int _salary);

    /// Display this teacher's record.
    ///
    /// Implements Base::DisplayRecord by printing the teacher's name and salary.
    void DisplayRecord() const override;

    /// Clone this Teacher instance polymorphically.
    ///
    /// Returns a unique pointer to a copy of this object so it can be
    /// stored in a `std::vector<std::unique_ptr<Base>>`.
    std::unique_ptr<Base> clone() const override;
};