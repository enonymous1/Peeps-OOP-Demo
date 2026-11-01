#include "PeepFactory.h"

#include "Banner.h"
#include "InputUtils.h"
#include "Student.h"
#include "Teacher.h"

std::vector<PeepKind> AllPeepKinds() {
    return {
        {"Teacher",
         [](const std::string& name, std::istream& in, std::ostream& out) {
             out << '\n';
             PrintBanner(out, "Salary?");
             const auto salary = InputUtils::GetValidatedInt(
                 in, out, "\t\tSalary:  ", Teacher::kMinSalary, Teacher::kMaxSalary);
             if (!salary.has_value()) {
                 return std::unique_ptr<Base>{};
             }
             auto teacher = std::make_unique<Teacher>();
             teacher->SetName(name);
             teacher->SetSalary(*salary);
             return std::unique_ptr<Base>(std::move(teacher));
         }},
        {"Student",
         [](const std::string& name, std::istream& in, std::ostream& out) {
             out << '\n';
             PrintBanner(out, "GPA?");
             const auto gpa = InputUtils::GetValidatedFloat(
                 in, out, "\t\tGPA:  ", Student::kMinGpa, Student::kMaxGpa);
             if (!gpa.has_value()) {
                 return std::unique_ptr<Base>{};
             }
             auto student = std::make_unique<Student>();
             student->SetName(name);
             student->SetGPA(*gpa);
             return std::unique_ptr<Base>(std::move(student));
         }},
    };
}
