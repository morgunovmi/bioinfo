#pragma once

#include <vector>
#include <string_view>
#include <map>

namespace p2 {
auto frequency_table(std::string_view text, std::size_t i) -> std::map<std::string_view, std::size_t>;
auto find_clumps(std::string_view genome, std::size_t k, std::size_t L, std::size_t t) -> std::vector<std::string_view>;
void solve();
}
