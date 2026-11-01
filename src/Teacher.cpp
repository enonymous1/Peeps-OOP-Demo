#include "Teacher.h"

#include <stdexcept>
#include <utility>

Teacher::Teacher(std::string name, int salary) : Base(std::move(name)) { SetSalary(salary); }

void Teacher::SetSalary(int salary) {
    if (salary < kMinSalary || salary > kMaxSalary) {
        throw std::out_of_range("Salary must be between 0 and 1000000");
    }
    salary_ = salary;
}

void Teacher::DisplayRecord(std::ostream& out) const {
    out << GetName() << " :: Salary == " << salary_ << '\n';
}

std::unique_ptr<Base> Teacher::Clone() const { return std::make_unique<Teacher>(*this); }
