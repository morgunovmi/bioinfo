#pragma once

#include <string_view>
#include <vector>

namespace p16 {
    auto find_substrings_encoding_peptide(std::string_view text, std::string_view peptide) -> std::vector<std::string_view>;
    void solve();
}