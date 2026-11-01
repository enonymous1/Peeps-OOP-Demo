#pragma once

#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "Base.h"

/// A concrete peep type representing a teacher, storing a salary.
class Teacher : public Base {
public:
    // Salary bounds are the single source of truth for this type: App
    // reads these constants instead of inventing its own range, so the
    // UI and the setter can never disagree again. The 1,000,000 cap is
    // an arbitrary demo cap, not a business rule.
    static constexpr int kMinSalary = 0;
    static constexpr int kMaxSalary = 1'000'000;

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

    std::string_view TypeName() const override;
    void DisplayRecord(std::ostream& out) const override;
    std::unique_ptr<Base> Clone() const override;

private:
    int salary_ = 0;
};
