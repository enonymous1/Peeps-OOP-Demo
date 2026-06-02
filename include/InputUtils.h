#pragma once

#include <string_view>

namespace InputUtils {

    /// Clear any pending characters from stdin.
    ///
    /// This helper is used after numeric input in order to remove leftover
    /// newline and invalid characters from the input buffer, ensuring the next
    /// input call starts from a clean state.
    void ClearBuffer() noexcept;

    /// Prompt the user for an integer and validate the result.
    ///
    /// The function displays `strMessage`, reads an integer from stdin,
    /// clears any trailing input, and enforces the optional range
    /// `[nMinimumRange, nMaximumRange]`.
    ///
    /// @param strMessage Text to display before reading input.
    /// @param nMinimumRange Minimum accepted value, inclusive.
    /// @param nMaximumRange Maximum accepted value, inclusive.
    /// @returns A validated integer provided by the user.
    int GetValidatedInt(std::string_view strMessage,
                        int nMinimumRange = 0,
                        int nMaximumRange = 0);

    /// Prompt the user for a floating-point value and validate it.
    ///
    /// This is useful for values such as GPA, where decimals are allowed.
    float GetValidatedFloat(std::string_view strMessage,
                            float nMinimumRange = 0.0f,
                            float nMaximumRange = 0.0f);
}
