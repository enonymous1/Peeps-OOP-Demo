#pragma once

#include <functional>
#include <istream>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>
#include <vector>

#include "Base.h"

// A creator prompts for its own fields (salary, GPA, ...) and returns
// the finished record, or nullptr if input ends mid-record. App no
// longer knows what fields any type has, so adding a type does not
// require editing App at all — only a registry entry here.
using PeepCreator = std::function<std::unique_ptr<Base>(
    const std::string& name, std::istream& in, std::ostream& out)>;

struct PeepKind {
    std::string_view label;
    PeepCreator create;
};

// The registry is the only place that knows the type list. App builds
// its type menu from this vector, in order, so the menu can never
// drift from the factory.
std::vector<PeepKind> AllPeepKinds();
