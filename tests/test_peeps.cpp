// Zero-dependency tests for Peeps-OOP-Demo.
//
// Deliberately no Catch2 / GoogleTest: this is a small teaching demo, and
// keeping the test build offline and one command matters more here than a
// test framework. `ctest` runs this one binary; a non-zero exit fails CI.

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

#include "App.h"
#include "InputUtils.h"
#include "Student.h"
#include "Teacher.h"

namespace {

int failures = 0;

void Check(bool condition, const char* expression, int line) {
    if (!condition) {
        std::cerr << "FAIL line " << line << ": " << expression << '\n';
        ++failures;
    }
}

#define CHECK(condition) Check((condition), #condition, __LINE__)

template <typename F>
void CheckThrowsOutOfRange(F&& fn, const char* expression, int line) {
    try {
        fn();
    } catch (const std::out_of_range&) {
        return;
    } catch (...) {
        std::cerr << "FAIL line " << line << ": " << expression << " threw the wrong exception\n";
        ++failures;
        return;
    }
    std::cerr << "FAIL line " << line << ": " << expression << " did not throw\n";
    ++failures;
}

#define CHECK_THROWS_OUT_OF_RANGE(expression) \
    CheckThrowsOutOfRange([&] { (void)(expression); }, #expression, __LINE__)

bool Contains(const std::string& haystack, const std::string& needle) {
    return haystack.find(needle) != std::string::npos;
}

void TestClonePreservesTypeAndFields() {
    Teacher teacher("Ada", 50000);
    const std::unique_ptr<Base> clone = teacher.Clone();
    const auto* cloned_teacher = dynamic_cast<Teacher*>(clone.get());
    CHECK(cloned_teacher != nullptr);
    CHECK(clone->GetName() == "Ada");
    if (cloned_teacher != nullptr) {
        CHECK(cloned_teacher->GetSalary() == 50000);
    }

    Student student("Ben", 3.5F);
    const std::unique_ptr<Base> student_clone = student.Clone();
    const auto* cloned_student = dynamic_cast<Student*>(student_clone.get());
    CHECK(cloned_student != nullptr);
    if (cloned_student != nullptr) {
        CHECK(cloned_student->GetGPA() == 3.5F);
    }
}

void TestCloneIsIndependent() {
    Teacher teacher("Ada", 50000);
    std::unique_ptr<Base> clone = teacher.Clone();
    clone->SetName("Clone");
    CHECK(teacher.GetName() == "Ada");
    CHECK(clone->GetName() == "Clone");
}

void TestSetterInvariants() {
    Student student;
    CHECK_THROWS_OUT_OF_RANGE(student.SetGPA(4.1F));
    CHECK_THROWS_OUT_OF_RANGE(student.SetGPA(-0.1F));
    student.SetGPA(4.0F);
    CHECK(student.GetGPA() == 4.0F);

    Teacher teacher;
    CHECK_THROWS_OUT_OF_RANGE(teacher.SetSalary(-1));
    CHECK_THROWS_OUT_OF_RANGE(teacher.SetSalary(Teacher::kMaxSalary + 1));
    teacher.SetSalary(0);
    CHECK(teacher.GetSalary() == 0);
    teacher.SetSalary(Teacher::kMaxSalary);
    CHECK(teacher.GetSalary() == Teacher::kMaxSalary);
}

void TestValidatedInt() {
    {
        std::istringstream in("abc\n5\n");
        std::ostringstream out;
        const auto value = InputUtils::GetValidatedInt(in, out, "Selection: ", 1, 10);
        CHECK(value.has_value() && *value == 5);
        CHECK(Contains(out.str(), "invalid input"));
    }
    {
        std::istringstream in("99\n3\n");
        std::ostringstream out;
        const auto value = InputUtils::GetValidatedInt(in, out, "Selection: ", 1, 10);
        CHECK(value.has_value() && *value == 3);
        CHECK(Contains(out.str(), "out of range"));
    }
    {
        // Trailing junk is rejected, not silently accepted.
        std::istringstream in("5x\n7\n");
        std::ostringstream out;
        const auto value = InputUtils::GetValidatedInt(in, out, "Selection: ");
        CHECK(value.has_value() && *value == 7);
    }
    {
        // EOF returns nullopt instead of looping forever (the old bug).
        std::istringstream in("");
        std::ostringstream out;
        CHECK(!InputUtils::GetValidatedInt(in, out, "Selection: ").has_value());
    }
}

void TestValidatedFloat() {
    std::istringstream in("4.5\n3.5\n");
    std::ostringstream out;
    const auto value = InputUtils::GetValidatedFloat(in, out, "GPA: ", 0.0F, 4.0F);
    CHECK(value.has_value() && *value == 3.5F);

    std::istringstream empty("");
    std::ostringstream empty_out;
    CHECK(!InputUtils::GetValidatedFloat(empty, empty_out, "GPA: ").has_value());
}

void TestNonEmptyLine() {
    std::istringstream in("\nBob\n");
    std::ostringstream out;
    const auto value = InputUtils::GetNonEmptyLine(in, out, "Name: ");
    CHECK(value.has_value() && *value == "Bob");

    {
        // Whitespace-only is not a name, and surrounding spaces are trimmed.
        std::istringstream ws_in("   \n  Bob  \n");
        std::ostringstream ws_out;
        const auto ws_value = InputUtils::GetNonEmptyLine(ws_in, ws_out, "Name: ");
        CHECK(ws_value.has_value() && *ws_value == "Bob");
    }

    std::istringstream empty("");
    std::ostringstream empty_out;
    CHECK(!InputUtils::GetNonEmptyLine(empty, empty_out, "Name: ").has_value());
}

void TestValidatedFloatRejectsNonFinite() {
    // "nan" must never become a GPA, on any standard library: it is
    // rejected and the next valid value is used.
    std::istringstream in("nan\n3.5\n");
    std::ostringstream out;
    const auto value = InputUtils::GetValidatedFloat(in, out, "GPA: ", 0.0F, 4.0F);
    CHECK(value.has_value() && *value == 3.5F);
}

void TestAppStudentSmoke() {
    // Add a student, display, exit. The teacher path alone is not
    // enough coverage for AddRecord's second branch.
    std::istringstream in("1\n2\nBen\n3.5\n2\n4\n");
    std::ostringstream out;
    App app(in, out);
    app.Run();
    CHECK(Contains(out.str(), "1. Ben :: GPA == 3.5"));
}

void TestAppEmptyDisplayAndClone() {
    std::istringstream in("2\n3\n4\n");
    std::ostringstream out;
    App app(in, out);
    app.Run();
    CHECK(Contains(out.str(), "No records found."));
    CHECK(Contains(out.str(), "No peeps found."));
}

void TestAppInvalidMenuThenValid() {
    std::istringstream in("9\n4\n");
    std::ostringstream out;
    App app(in, out);
    app.Run();
    CHECK(Contains(out.str(), "out of range"));
}

void TestAppSmoke() {
    // Add a teacher, display, clone, display again, exit.
    std::istringstream in("1\n1\nAda\n50000\n2\n3\n1\n2\n4\n");
    std::ostringstream out;
    App app(in, out);
    app.Run();
    const std::string output = out.str();
    CHECK(Contains(output, "1. Ada :: Salary == 50000"));
    CHECK(Contains(output, "2. Ada :: Salary == 50000"));
    CHECK(Contains(output, "Cloned peep 1."));
}

void TestAppExitsCleanlyOnEof() {
    std::istringstream in("");
    std::ostringstream out;
    App app(in, out);
    app.Run();
    CHECK(Contains(out.str(), "Peeps-OOP-Demo"));
}

}  // namespace

int main() {
    // One entry per test, run in isolation: a test that throws
    // unexpectedly is counted as a failure instead of aborting the
    // whole binary with no summary, and the output names the test.
    const std::pair<const char*, void (*)()> tests[] = {
        {"ClonePreservesTypeAndFields", TestClonePreservesTypeAndFields},
        {"CloneIsIndependent", TestCloneIsIndependent},
        {"SetterInvariants", TestSetterInvariants},
        {"ValidatedInt", TestValidatedInt},
        {"ValidatedFloat", TestValidatedFloat},
        {"ValidatedFloatRejectsNonFinite", TestValidatedFloatRejectsNonFinite},
        {"NonEmptyLine", TestNonEmptyLine},
        {"AppSmoke", TestAppSmoke},
        {"AppStudentSmoke", TestAppStudentSmoke},
        {"AppEmptyDisplayAndClone", TestAppEmptyDisplayAndClone},
        {"AppInvalidMenuThenValid", TestAppInvalidMenuThenValid},
        {"AppExitsCleanlyOnEof", TestAppExitsCleanlyOnEof},
    };
    for (const auto& [name, fn] : tests) {
        const int before = failures;
        std::cout << "test: " << name << '\n';
        try {
            fn();
        } catch (const std::exception& error) {
            std::cerr << "FAIL: " << name << " threw: " << error.what() << '\n';
            ++failures;
        } catch (...) {
            std::cerr << "FAIL: " << name << " threw an unknown exception\n";
            ++failures;
        }
        if (failures == before) {
            std::cout << "  ok\n";
        }
    }

    if (failures != 0) {
        std::cerr << failures << " check(s) failed\n";
        return 1;
    }
    std::cout << "All tests passed\n";
    return 0;
}
