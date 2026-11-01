#pragma once

#include <ostream>
#include <string_view>

// Every banner is the same 24-dash rule on each side of the title.
// One helper keeps them identical and stops a future banner edit from
// drifting one title's width away from the rest.
inline void PrintBanner(std::ostream& out, std::string_view title) {
    constexpr std::string_view kRule = "------------------------";  // 24 dashes
    out << kRule << title << kRule << '\n';
}
