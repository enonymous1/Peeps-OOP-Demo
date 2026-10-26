#include "Teacher.h"

#include <iostream>
#include <stdexcept>
#include <utility>

Teacher::Teacher(std::string name, int salary) : Base(std::move(name)) { SetSalary(salary); }

void Teacher::SetSalary(int salary) {
    if (salary < 0) {
        throw std::out_of_range("Salary cannot be negative");
    }
    salary_ = salary;
}

void Teacher::DisplayRecord(std::ostream& out) const {
    out << GetName() << " :: Salary == " << salary_ << '\n';
}

std::unique_ptr<Base> Teacher::Clone() const { return std::make_unique<Teacher>(*this); }
