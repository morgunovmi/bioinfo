#pragma once

#include <string_view>
#include <vector>

namespace p3 {
auto find_skew_minimums(std::string_view genome) -> std::vector<std::size_t>;
void solve();
}

