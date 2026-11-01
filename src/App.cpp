#include "App.h"

#include <sstream>

#include "Banner.h"
#include "InputUtils.h"
#include "PeepFactory.h"

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
    // App no longer knows the concrete types or their fields: the
    // menu is built from the factory registry, in order, and the
    // chosen creator prompts for its own fields. Adding a type is
    // now one registry entry, not an edit to this function.
    const std::vector<PeepKind> kinds = AllPeepKinds();
    PrintBanner(out_, "What kind of peep?");
    std::ostringstream menu;
    menu << '\n';
    for (std::size_t i = 0; i < kinds.size(); ++i) {
        menu << "\t\t" << (i + 1) << ") " << kinds[i].label << '\n';
    }
    menu << "\n\tSelection: ";
    const std::string menu_text = menu.str();
    const std::optional<int> type = InputUtils::GetValidatedInt(
        in_, out_, menu_text, 1, static_cast<int>(kinds.size()));
    if (!type.has_value()) {
        return;
    }
    const std::optional<std::string> name = PromptName();
    if (!name.has_value()) {
        return;
    }
    std::unique_ptr<Base> peep =
        kinds[static_cast<std::size_t>(*type) - 1].create(*name, in_, out_);
    if (peep) {
        peeps_.push_back(std::move(peep));
    }
    // A null result means input ended mid-record; the record is
    // simply not added, and the main loop exits on the next prompt.
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
