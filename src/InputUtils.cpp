#include "InputUtils.h"

#include <sstream>

namespace InputUtils {
namespace {

// Read one line. Returns false on end-of-input, so callers can stop
// instead of retrying forever (the old behaviour on Ctrl-D / piped EOF).
bool ReadLine(std::istream& in, std::string& line) { return static_cast<bool>(std::getline(in, line)); }

template <typename T>
std::optional<T> ReadValidated(std::istream& in, std::ostream& out, std::string_view prompt,
                               std::optional<T> minimum, std::optional<T> maximum) {
    std::string line;
    while (true) {
        out << prompt << std::flush;
        if (!ReadLine(in, line)) {
            return std::nullopt;
        }

        std::istringstream parsed(line);
        T value{};
        if (!(parsed >> value)) {
            out << "\n\tError, invalid input please try again.\n";
            continue;
        }
        // The whole line must be one value: no trailing junk.
        // Note: extracting whitespace at end-of-line sets failbit too, so
        // only eof() is checked here, not fail().
        parsed >> std::ws;
        if (!parsed.eof()) {
            out << "\n\tError, invalid input please try again.\n";
            continue;
        }
        if ((minimum.has_value() && value < *minimum) ||
            (maximum.has_value() && value > *maximum)) {
            out << "\n\tYour input was out of range, please try again.\n";
            continue;
        }
        return value;
    }
}

}  // namespace

std::optional<int> GetValidatedInt(std::istream& in, std::ostream& out, std::string_view prompt,
                                   std::optional<int> minimum, std::optional<int> maximum) {
    return ReadValidated<int>(in, out, prompt, minimum, maximum);
}

std::optional<float> GetValidatedFloat(std::istream& in, std::ostream& out, std::string_view prompt,
                                       std::optional<float> minimum, std::optional<float> maximum) {
    return ReadValidated<float>(in, out, prompt, minimum, maximum);
}

std::optional<std::string> GetNonEmptyLine(std::istream& in, std::ostream& out,
                                           std::string_view prompt) {
    std::string line;
    while (true) {
        out << prompt << std::flush;
        if (!ReadLine(in, line)) {
            return std::nullopt;
        }
        if (line.empty()) {
            out << "\tName cannot be empty. Please enter a valid name.\n";
            continue;
        }
        return line;
    }
}

}  // namespace InputUtils
