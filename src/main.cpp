#include <exception>
#include <iostream>

#include "App.h"

int main() {
    try {
        App app(std::cin, std::cout);
        app.Run();
    } catch (const std::exception& error) {
        // One catch, at the top: a setter invariant or any other
        // unexpected failure becomes a readable message and exit code
        // 1, instead of an unhandled terminate with no context.
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
    return 0;
}
