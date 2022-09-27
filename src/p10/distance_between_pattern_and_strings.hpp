#pragma once

#include <vector>
#include <string_view>

namespace p10 {
auto distance_between_pattern_and_strings(std::string_view pattern, const std::vector<std::string_view>& dna) -> std::size_t;
void solve();
}
