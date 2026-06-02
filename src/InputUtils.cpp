#include "InputUtils.h"
#include <iostream>
#include <climits>

namespace InputUtils {

/// Clear any pending input from stdin.
///
/// This helper resets the stream error state and discards characters until
/// the next newline. It is used after a failed extraction to ensure the next
/// read starts from a clean buffer.
void ClearBuffer() noexcept
{
    std::cin.clear();
    std::cin.ignore(INT_MAX, '\n');
}

/// Prompt the user for an integer and validate the result.
///
/// The function prints `strMessage` and reads an integer from stdin. If the
/// extraction fails, the buffer is cleared and the user is prompted again.
/// If a range is provided, the integer must fall within [nMinimumRange,
/// nMaximumRange].
///
/// @param strMessage The prompt text to display before reading input.
/// @param nMinimumRange The minimum allowed value (inclusive).
/// @param nMaximumRange The maximum allowed value (inclusive).
/// @returns A validated integer from the user.
int GetValidatedInt(std::string_view strMessage, int nMinimumRange, int nMaximumRange)
{
    int x;

    while (true)
    {
        std::cout << strMessage;
        std::cin >> x;

        while (std::cin.fail())
        {
            ClearBuffer();
            std::cout << "\n\tError, invalid input please try again:  ";
            std::cin >> x;
        }

        // Flush any leftover characters from the line after a successful read.
        ClearBuffer();

        // If both range bounds are zero, treat it as “no range specified.”
        if ((nMaximumRange == 0 && nMinimumRange == 0) || (x >= nMinimumRange && x <= nMaximumRange))
        {
            return x;
        }

        std::cout << "\n\tYour input was out of range, lets ride this ride again =)\n\n";
    }
}

float GetValidatedFloat(std::string_view strMessage, float nMinimumRange, float nMaximumRange)
{
    float x;

    while (true)
    {
        std::cout << strMessage;
        std::cin >> x;

        while (std::cin.fail())
        {
            ClearBuffer();
            std::cout << "\n\tError, invalid input please try again:  ";
            std::cin >> x;
        }

        ClearBuffer();

        if ((nMaximumRange == 0.0f && nMinimumRange == 0.0f) ||
            (x >= nMinimumRange && x <= nMaximumRange))
        {
            return x;
        }

        std::cout << "\n\tYour input was out of range, lets ride this ride again =)\n\n";
    }
}

} // namespace InputUtils