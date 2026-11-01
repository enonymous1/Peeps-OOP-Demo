#include "Student.h"

#include <stdexcept>
#include <utility>

Student::Student(std::string name, float gpa) : Base(std::move(name)) { SetGPA(gpa); }

void Student::SetGPA(float gpa) {
    if (gpa < kMinGpa || gpa > kMaxGpa) {
        throw std::out_of_range("GPA must be between 0.0 and 4.0");
    }
    gpa_ = gpa;
}

std::string_view Student::TypeName() const { return "Student"; }

void Student::DisplayRecord(std::ostream& out) const {
    out << GetName() << " :: GPA == " << gpa_ << '\n';
}

std::unique_ptr<Base> Student::Clone() const { return std::make_unique<Student>(*this); }
