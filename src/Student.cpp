// Include the header file for the Student class.
#include "Student.h"

// Include the iostream library for console output.
#include <iostream>

/// Default constructor for the Student class.
///
/// Student records initialize the GPA field to zero so that newly created
/// students have a well-defined default state.
Student::Student()
{
    gpa = 0;
}

/// Copy constructor for the Student class.
///
/// This creates a new Student by copying both the Base state and the GPA
/// value from the source object.
Student::Student(const Student& _other) : Base(_other)
{
    gpa = _other.gpa;
}

/// Copy assignment operator for the Student class.
///
/// This ensures that assignment preserves both the base record state and
/// the derived GPA value, while protecting against self-assignment.
Student& Student::operator=(const Student& _other)
{
    if (this != &_other)
    {
        Base::operator=(_other);
        gpa = _other.gpa;
    }
    return *this;
}

/// Set the GPA for this student record.
///
/// This method stores the provided GPA value. Validation is currently
/// expected to happen before this method is called.
void Student::SetGPA(float _gpa)
{
    gpa = _gpa;
}

/// Display the student record to the console.
///
/// This prints the inherited name and the student's GPA in a consistent
/// output format for the app's list display.
void Student::DisplayRecord() const
{
    std::cout << GetName();
    std::cout << " :: GPA == " << gpa << "\n";
}

/// Clone this Student instance.
///
/// A polymorphic clone is required to preserve the concrete derived type
/// when duplicating records stored through Base pointers.
std::unique_ptr<Base> Student::clone() const
{
    return std::make_unique<Student>(*this);
}