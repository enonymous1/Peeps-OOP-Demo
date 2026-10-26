#pragma once

#include <istream>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <vector>

#include "Base.h"

/// The application controller for Peeps-OOP-Demo.
///
/// `App` owns the polymorphic record list and drives the menu loop. It
/// reads from and writes to the streams it is given, rather than
/// hard-coding `std::cin` / `std::cout`, so tests can drive it with
/// `std::istringstream` / `std::ostringstream` and the real program can
/// pass the console streams (see `main.cpp`).
class App {
public:
    App(std::istream& in, std::ostream& out) : in_(in), out_(out) {}

    /// Run the main loop until the user exits or input ends.
    void Run();

private:
    enum class Choice { Add = 1, Display, Clone, Exit };

    std::istream& in_;
    std::ostream& out_;
    std::vector<std::unique_ptr<Base>> peeps_;

    void ShowMenu() const;
    std::optional<Choice> GetMenuChoice() const;
    void AddRecord();
    void DisplayRecords() const;
    void DuplicateRecord();
    std::optional<std::string> PromptName() const;
};
