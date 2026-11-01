#include "App.h"

#include <string_view>

#include "InputUtils.h"
#include "Student.h"
#include "Teacher.h"

namespace {

// Every banner is the same 24-dash rule on each side of the title.
// One helper keeps them identical and stops a future banner edit from
// drifting one title's width away from the rest.
void PrintBanner(std::ostream& out, std::string_view title) {
    constexpr std::string_view kRule = "------------------------";  // 24 dashes
    out << kRule << title << kRule << '\n';
}

}  // namespace

void App::Run() {
    while (true) {
        ShowMenu();
        const std::optional<Choice> choice = GetMenuChoice();
        if (!choice.has_value() || *choice == Choice::Exit) {
            break;
        }
        switch (*choice) {
            case Choice::Add:
                AddRecord();
                break;
            case Choice::Display:
                DisplayRecords();
                break;
            case Choice::Clone:
                DuplicateRecord();
                break;
            default:
                // Exit is handled by the break above the switch, so
                // this is unreachable — it exists only to keep the
                // switch exhaustive and warning-free.
                break;
        }
    }
}

void App::ShowMenu() const {
    PrintBanner(out_, "Peeps-OOP-Demo");
    out_ << "\t1) Add a peep\n"
         << "\t2) Display all peeps\n"
         << "\t3) Clone a peep\n"
         << "\t4) Exit\n";
}

std::optional<App::Choice> App::GetMenuChoice() const {
    const std::optional<int> value =
        InputUtils::GetValidatedInt(in_, out_, "\n\tSelection: ", 1, 4);
    if (!value.has_value()) {
        return std::nullopt;
    }
    return static_cast<Choice>(*value);
}

std::optional<std::string> App::PromptName() const {
    // The banner is printed separately so the prompt itself stays a
    // plain "Name:  " line; PrintBanner supplies the trailing newline.
    PrintBanner(out_, "Name?");
    return InputUtils::GetNonEmptyLine(in_, out_, "\t\tName:  ");
}

void App::AddRecord() {
    PrintBanner(out_, "What kind of peep?");
    const std::optional<int> type = InputUtils::GetValidatedInt(
        in_, out_, "\n\t\t1) Teacher\n\t\t2) Student\n\n\tSelection: ", 1, 2);
    if (!type.has_value()) {
        return;
    }
    const std::optional<std::string> name = PromptName();
    if (!name.has_value()) {
        return;
    }

    if (*type == 1) {
        out_ << '\n';
        PrintBanner(out_, "Salary?");
        const std::optional<int> salary = InputUtils::GetValidatedInt(
            in_, out_, "\t\tSalary:  ", Teacher::kMinSalary, Teacher::kMaxSalary);
        if (!salary.has_value()) {
            return;
        }
        auto teacher = std::make_unique<Teacher>();
        teacher->SetName(*name);
        teacher->SetSalary(*salary);
        peeps_.push_back(std::move(teacher));
    } else {
        out_ << '\n';
        PrintBanner(out_, "GPA?");
        const std::optional<float> gpa = InputUtils::GetValidatedFloat(
            in_, out_, "\t\tGPA:  ", Student::kMinGpa, Student::kMaxGpa);
        if (!gpa.has_value()) {
            return;
        }
        auto student = std::make_unique<Student>();
        student->SetName(*name);
        student->SetGPA(*gpa);
        peeps_.push_back(std::move(student));
    }
}

void App::DisplayRecords() const {
    PrintBanner(out_, "Display Records");
    if (peeps_.empty()) {
        out_ << "No records found. Add a peep first!\n\n";
        return;
    }
    for (std::size_t i = 0; i < peeps_.size(); ++i) {
        out_ << "\n\t\t" << (i + 1) << ". ";
        peeps_[i]->DisplayRecord(out_);
    }
    out_ << '\n';
}

void App::DuplicateRecord() {
    if (peeps_.empty()) {
        out_ << "No peeps found. Add a peep first!\n";
        return;
    }
    PrintBanner(out_, "Clone a peep");
    out_ << "\t\t";
    out_ << "There are " << peeps_.size() << " peeps in the records, choose one to clone.\n\t\t";
    const std::optional<int> choice = InputUtils::GetValidatedInt(
        in_, out_, "Peep number: ", 1, static_cast<int>(peeps_.size()));
    if (!choice.has_value()) {
        return;
    }
    peeps_.push_back(peeps_[static_cast<std::size_t>(*choice) - 1]->Clone());
    out_ << "Cloned peep " << *choice << ".\n";
}
