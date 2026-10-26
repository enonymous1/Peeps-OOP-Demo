#pragma once

#include <istream>
#include <optional>
#include <ostream>
#include <string>
#include <string_view>

namespace InputUtils {

/// Prompt for an integer and validate it.
///
/// Reads a whole line at a time, so stray characters cannot leak into the
/// next prompt. Returns `std::nullopt` on end-of-input instead of looping
/// forever, which is what the old helpers did on Ctrl-D / piped EOF.
/// A missing bound means "no bound": there is no (0, 0) sentinel anymore.
std::optional<int> GetValidatedInt(std::istream& in, std::ostream& out, std::string_view prompt,
                                   std::optional<int> minimum = std::nullopt,
                                   std::optional<int> maximum = std::nullopt);

/// Prompt for a floating-point value and validate it. Same EOF contract
/// as `GetValidatedInt`.
std::optional<float> GetValidatedFloat(std::istream& in, std::ostream& out, std::string_view prompt,
                                       std::optional<float> minimum = std::nullopt,
                                       std::optional<float> maximum = std::nullopt);

/// Prompt for a line of text, rejecting empty lines. Returns
/// `std::nullopt` on end-of-input.
std::optional<std::string> GetNonEmptyLine(std::istream& in, std::ostream& out,
                                           std::string_view prompt);

}  // namespace InputUtils
