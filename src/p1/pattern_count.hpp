#pragma once

#include <string_view>
#include <vector>

namespace p1 {
auto pattern_count(std::string_view text, std::string_view pattern) -> std::vector<std::size_t>;
void solve();
}
