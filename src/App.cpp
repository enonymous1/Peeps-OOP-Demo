#include "App.h"

#include "InputUtils.h"
#include "Student.h"
#include "Teacher.h"

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
            case Choice::Exit:
                break;
        }
    }
}

void App::ShowMenu() const {
    out_ << "------------------------Peeps-OOP-Demo------------------------\n"
         << "\t1) Add a peep\n"
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
    return InputUtils::GetNonEmptyLine(
        in_, out_, "------------------------Name?------------------------\n\t\tName:  ");
}

void App::AddRecord() {
    out_ << "------------------------What kind of peep?------------------------\n";
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
        const std::optional<int> salary = InputUtils::GetValidatedInt(
            in_, out_, "\n------------------------Salary?------------------------\n\t\tSalary:  ", 0, 1000000);
        if (!salary.has_value()) {
            return;
        }
        auto teacher = std::make_unique<Teacher>();
        teacher->SetName(*name);
        teacher->SetSalary(*salary);
        peeps_.push_back(std::move(teacher));
    } else {
        const std::optional<float> gpa = InputUtils::GetValidatedFloat(
            in_, out_, "\n------------------------GPA?------------------------\n\t\tGPA:  ", 0.0F, 4.0F);
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
    out_ << "------------------------Display Records------------------------\n";
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
    out_ << "------------------------Clone a peep------------------------\n\t\t";
    out_ << "There are " << peeps_.size() << " peeps in the records, choose one to clone.\n\t\t";
    const std::optional<int> choice = InputUtils::GetValidatedInt(
        in_, out_, "Peep number: ", 1, static_cast<int>(peeps_.size()));
    if (!choice.has_value()) {
        return;
    }
    peeps_.push_back(peeps_[static_cast<std::size_t>(*choice) - 1]->Clone());
    out_ << "Cloned peep " << *choice << ".\n";
}
