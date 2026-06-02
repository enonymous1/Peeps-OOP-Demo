// Include the header file for the Teacher class.
#include "Teacher.h"

// Include the iostream library for console output.
#include <iostream>

/// Default constructor for the Teacher class.
///
/// Initializes the teacher salary to zero so the object has a well-defined
/// default state before any input is assigned.
Teacher::Teacher()
{
    salary = 0;
}

/// Copy constructor for the Teacher class.
///
/// Copies the base class state and the salary value from the source object.
Teacher::Teacher(const Teacher& _other) : Base(_other)
{
    salary = _other.salary;
}

/// Copy assignment operator for the Teacher class.
///
/// Ensures that both the inherited Base state and the Teacher salary
/// are updated, while protecting against self-assignment.
Teacher& Teacher::operator=(const Teacher& _other)
{
    if (this != &_other)
    {
        Base::operator=(_other);
        salary = _other.salary;
    }
    return *this;
}

/// Set the salary of this teacher record.
///
/// Validation is intentionally left to the caller, allowing the input layer
/// to enforce appropriate business rules.
void Teacher::SetSalary(int _salary)
{
    salary = _salary;
}

/// Display the teacher record.
///
/// This prints the teacher's name and salary in the same format used by
/// other record types, preserving a consistent list display.
void Teacher::DisplayRecord() const
{
    std::cout << GetName();
    std::cout << " :: Salary == " << salary << "\n";
}

/// Clone this Teacher instance polymorphically.
///
/// This supports the Base interface and allows the app to duplicate records
/// without slicing.
std::unique_ptr<Base> Teacher::clone() const
{
    return std::make_unique<Teacher>(*this);
}