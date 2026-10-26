#pragma once

#include <memory>
#include <ostream>
#include <string>

#include "Base.h"

/// A concrete peep type representing a teacher, storing a salary.
class Teacher : public Base {
public:
    Teacher() = default;

    Teacher(std::string name, int salary);

    Teacher(const Teacher&) = default;
    Teacher& operator=(const Teacher&) = default;
    Teacher(Teacher&&) noexcept = default;
    Teacher& operator=(Teacher&&) noexcept = default;
    ~Teacher() override = default;

    /// Set the salary. Throws `std::out_of_range` for a negative salary.
    void SetSalary(int salary);

    int GetSalary() const noexcept { return salary_; }

    void DisplayRecord(std::ostream& out) const override;
    std::unique_ptr<Base> Clone() const override;

private:
    int salary_ = 0;
};
