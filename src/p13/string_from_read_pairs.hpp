#pragma once

#include <string_view>
#include <vector>

namespace p13 {
auto string_from_read_pairs(const std::vector<std::string_view>& read_pairs, uint32_t k, uint32_t d) -> std::string;
void solve();
}
