#include "App.h"
#include "InputUtils.h"
#include "Teacher.h"
#include "Student.h"
#include <iostream>

using namespace InputUtils;

/// Run the application loop until the user chooses Exit.
///
/// This method drives the main menu, dispatches actions, and pauses at the end
/// so the console output remains visible on exit.
void App::Run()
{
    Choice choice;

    do
    {
        ShowMenu();
        choice = GetMenuChoice();

        switch (choice)
        {
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
                break;
        }
    } while (choice != Choice::Exit);

    std::cout << std::endl;
    std::cin.get();
}

/// Print the application header and menu title.
///
/// This is intentionally separate from GetMenuChoice so that the header
/// remains visible before each prompt.
void App::ShowMenu() const
{
    std::cout << "------------------------Peeps-OOP-Demo------------------------\n";
}

/// Query the user for a menu selection and validate the result.
///
/// The GetValidatedInt helper ensures only 1-4 are accepted, so this method
/// can safely cast the returned integer into the Choice enum.
App::Choice App::GetMenuChoice() const
{
    const char menu[] = "\n\t\t1) Add a peep\n\t\t2) Display all peeps\n\t\t3) Clone a peep\n\t\t4) Exit\n\n\tSelection: ";
    return static_cast<Choice>(GetValidatedInt(menu, 1, 4));
}

/// Prompt the user for a name and return the entered value.
///
/// The method currently performs a second read if the first input is empty,
/// but it should ideally enforce non-empty input explicitly.
std::string App::PromptName() const
{
    std::string name;
    std::cout << "------------------------Name?------------------------\n\t\tName:  ";
    std::getline(std::cin, name);
    if (name.empty())
    {
        std::getline(std::cin, name);
    }
    return name;
}

/// Create a new record of the selected type and store it in the peeps list.
///
/// The method uses polymorphic object creation and preserves ownership via
/// std::unique_ptr<Base>.
void App::AddRecord()
{
    std::cout << "------------------------What kind of peep?------------------------\n";
    const char menu[] = "\n\t\t1) Teacher\n\t\t2) Student\n\n\tSelection: ";
    int mainMenuChoice = GetValidatedInt(menu, 1, 2);

    const std::string name = PromptName();

    if (mainMenuChoice == 1)
    {
        auto teacher = std::make_unique<Teacher>();
        teacher->SetName(name);
        int salary = GetValidatedInt("\n------------------------Salary?------------------------\n\t\tSalary:  ");
        teacher->SetSalary(salary);
        peeps.push_back(std::move(teacher));
    }
    else
    {
        auto student = std::make_unique<Student>();
        student->SetName(name);
        const float gpa = static_cast<float>(GetValidatedInt("\n------------------------GPA?------------------------\n\t\tGPA:  "));
        student->SetGPA(gpa);
        peeps.push_back(std::move(student));
    }
}

/// Display all stored records or inform the user if the list is empty.
///
/// This method iterates over the polymorphic vector and invokes each object's
/// DisplayRecord implementation.
void App::DisplayRecords() const
{
    std::cout << "------------------------Display Records------------------------\n";

    if (peeps.empty())
    {
        std::cout << "No records found. Add a peep first!\n\n";
        return;
    }

    for (const auto& record : peeps)
    {
        std::cout << "\n\t\t";
        record->DisplayRecord();
    }

    std::cout << "\n";
}

/// Clone a selected record by index and append the copy to the list.
///
/// The method validates the choice via GetValidatedInt and uses the virtual
/// clone interface to preserve the runtime type.
void App::DuplicateRecord()
{
    if (peeps.empty())
    {
        std::cout << "Sorry NO peeps FOUND!!!  Add PEEPS!\n";
        return;
    }

    std::cout << "------------------------Clone Zone------------------------\n\t\t";
    std::cout << "There are " << peeps.size() << " peeps in the records, choose one to clone.\n\t\t";
    int choice = GetValidatedInt("Peep number: ", 1, static_cast<int>(peeps.size()));
    peeps.push_back(peeps[choice - 1]->clone());
}