#pragma once

#include <vector>
#include <string_view>

namespace p7 {
auto greedy_motif_search(std::size_t k, std::size_t t, const std::vector<std::string_view>& dna) -> std::vector<std::string_view>;
void solve();
}
