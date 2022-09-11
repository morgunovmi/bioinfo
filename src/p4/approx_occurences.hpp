#pragma once

#include <vector>
#include <string_view>

namespace p4 {
auto hamming_distance(std::string_view s1, std::string_view s2) -> std::size_t;
auto find_approx_occurences(std::string_view pattern, std::string_view text, std::size_t d) -> std::vector<std::size_t>;
void solve();
}
