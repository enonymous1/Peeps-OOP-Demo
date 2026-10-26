#pragma once

#include <memory>
#include <ostream>
#include <string>

#include "Base.h"

/// A concrete peep type representing a student, storing a GPA.
class Student : public Base {
public:
    Student() = default;

    Student(std::string name, float gpa);

    Student(const Student&) = default;
    Student& operator=(const Student&) = default;
    Student(Student&&) noexcept = default;
    Student& operator=(Student&&) noexcept = default;
    ~Student() override = default;

    /// Set the GPA. Throws `std::out_of_range` outside [0.0, 4.0], so the
    /// invariant lives in the class instead of only in the input layer.
    void SetGPA(float gpa);

    float GetGPA() const noexcept { return gpa_; }

    void DisplayRecord(std::ostream& out) const override;
    std::unique_ptr<Base> Clone() const override;

private:
    float gpa_ = 0.0F;
};
