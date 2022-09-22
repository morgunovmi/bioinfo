#pragma once

#include <string_view>
#include <vector>

namespace p8 {
auto randomized_motif_search(std::size_t k, std::size_t t, const std::vector<std::string_view>& dna) -> std::vector<std::string_view>;
void solve();
}
