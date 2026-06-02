// The header guard prevents the header file from being included more than once.
#pragma once

#include "Base.h"

/// Student is a concrete Base-derived record type representing a student.
///
/// This class stores a GPA and implements the required Base interface for
/// display and cloning. The polymorphic `clone()` method enables copying
/// records through Base pointers without slicing.
class Student : public Base
{
private:
    /// The student's GPA.
    float gpa = 0;

public:
    /// Default constructor initializes a student with a zero GPA.
    Student();

    /// Copy constructor performs a field-wise copy of the student.
    ///
    /// The default copy behavior is sufficient because Base and float already
    /// manage their own memory and value semantics.
    Student(const Student& _other);

    /// Copy assignment operator performs a field-wise assignment.
    ///
    /// This keeps assignment semantics consistent with the copy constructor,
    /// while allowing derived-type state to be reused.
    Student& operator=(const Student& _other);

    /// Default virtual destructor ensures correct cleanup through Base pointers.
    ~Student() override = default;

    /// Set the GPA for this student record.
    ///
    /// The caller is responsible for any validation of the GPA range.
    void SetGPA(float _gpa);

    /// Display this student's record.
    ///
    /// Implements the Base contract by printing the stored name and GPA.
    void DisplayRecord() const override;

    /// Clone this object polymorphically.
    ///
    /// Returns a new unique_ptr containing a copy of this Student.
    std::unique_ptr<Base> clone() const override;
};