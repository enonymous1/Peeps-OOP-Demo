#pragma once

#include <memory>
#include <string>
#include <vector>
#include "Base.h"

/// The application controller for the Peeps-OOP-Demo program.
///
/// This class owns the primary records container and exposes the
/// top-level menu-driven workflow. It manages user choices, record
/// creation, display, and cloning using polymorphic Base-derived objects.
class App
{
public:
    /// Run the main application loop until the user exits.
    void Run();

private:
    /// Main menu choices available to the user.
    enum class Choice {
        Add = 1,
        Display,
        Clone,
        Exit
    };

    /// Container holding the polymorphic peep objects created by the app.
    std::vector<std::unique_ptr<Base>> peeps;

    /// Display the main menu prompt.
    ///
    /// This only emits the menu to stdout and does not modify application state.
    void ShowMenu() const;

    /// Query the user for the next menu choice.
    ///
    /// @returns The selected menu option as a Choice enum.
    Choice GetMenuChoice() const;

    /// Add a new record to the application state.
    ///
    /// The new record is created as either a Teacher or Student object,
    /// configured via user input, and stored in the `peeps` vector.
    void AddRecord();

    /// Display all stored records on the console.
    ///
    /// This method iterates over the polymorphic collection and calls
    /// each object's display method.
    void DisplayRecords() const;

    /// Duplicate an existing record by cloning the selected entry.
    ///
    /// This uses the virtual clone() interface exposed by Base.
    void DuplicateRecord();

    /// Prompt the user for a name and return the entered value.
    ///
    /// This helper centralizes name acquisition and can handle
    /// transient input state concerns at the presentation layer.
    std::string PromptName() const;
};