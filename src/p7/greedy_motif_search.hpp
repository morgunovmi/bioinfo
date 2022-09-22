#pragma once

#include <vector>
#include <string_view>

#include "p6/profile_most_probable.hpp"

namespace p7 {
[[nodiscard]] auto form_profile_with_laplace(const std::vector<std::string_view>& motifs, std::size_t k) -> p6::profile_mat;
[[nodiscard]] auto score_motifs(const std::vector<std::string_view>& motifs, std::size_t k) -> std::size_t;
auto greedy_motif_search(std::size_t k, std::size_t t, const std::vector<std::string_view>& dna) -> std::vector<std::string_view>;
void solve();
}
