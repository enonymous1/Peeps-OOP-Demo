#include "Student.h"

#include <iostream>
#include <stdexcept>
#include <utility>

Student::Student(std::string name, float gpa) : Base(std::move(name)) { SetGPA(gpa); }

void Student::SetGPA(float gpa) {
    if (gpa < 0.0F || gpa > 4.0F) {
        throw std::out_of_range("GPA must be between 0.0 and 4.0");
    }
    gpa_ = gpa;
}

void Student::DisplayRecord(std::ostream& out) const {
    out << GetName() << " :: GPA == " << gpa_ << '\n';
}

std::unique_ptr<Base> Student::Clone() const { return std::make_unique<Student>(*this); }
