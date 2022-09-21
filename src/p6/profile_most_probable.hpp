#pragma once

#include <string_view>
#include <vector>

namespace p6 {
using profile_mat = std::vector<std::vector<double>>;

auto find_profile_most_probable_kmer(std::string_view text, std::size_t k, const profile_mat& profile) -> std::string_view;
void solve();
}
