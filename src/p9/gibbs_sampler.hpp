#pragma once

#include <string_view>
#include <vector>

namespace p9 {
auto gibbs_sampler(const std::vector<std::string_view>& dna, std::size_t k, std::size_t t, std::size_t n) -> std::vector<std::string_view>;
void solve();
}
