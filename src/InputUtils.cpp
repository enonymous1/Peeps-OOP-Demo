#include "InputUtils.h"

#include <cmath>
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
        // Portability guard, not a workaround for this platform: on
        // GCC/libstdc++ "nan"/"inf" are already rejected above, but on
        // an implementation that parses NaN, the range check below
        // would pass it (every comparison with NaN is false). Reject
        // non-finite values explicitly so behaviour does not depend
        // on the standard library implementation.
        if (!std::isfinite(value)) {
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
        // A whitespace-only line is not a name: trim it, and reject
        // the line if nothing is left. Trimming also stops leading /
        // trailing spaces from being stored verbatim in the record.
        const std::size_t first = line.find_first_not_of(" \t\r\n");
        const std::size_t last = line.find_last_not_of(" \t\r\n");
        if (first == std::string::npos) {
            out << "\tName cannot be empty. Please enter a valid name.\n";
            continue;
        }
        return line.substr(first, last - first + 1);
    }
}

}  // namespace InputUtils
