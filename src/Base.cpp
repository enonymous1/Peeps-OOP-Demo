// Include the header file for the Base class.
#include "Base.h"

/// Set the name of this Base record.
///
/// `name` is stored in the internal std::string member. This assignment
/// keeps ownership and lifetime management simple by relying on C++ string
/// semantics.
void Base::SetName(const std::string& _name)
{
    name = _name;
}

/// Retrieve the stored name.
///
/// Returning a const reference avoids a copy while ensuring the caller cannot
/// modify the internal name directly.
const std::string& Base::GetName() const noexcept
{
    return name;
}