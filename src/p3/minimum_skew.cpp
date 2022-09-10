#include <fmt/format.h>

#include "minimum_skew.hpp"
#include "utils/util.hpp"

namespace p3 {
[[nodiscard]] auto find_skew_minimums(std::string_view genome) -> std::vector<std::size_t> {
    int32_t minimum_skew = INT_MAX;
    std::vector<std::size_t> min_indices{};

    int32_t skew = 0;
    for (std::size_t i = 0; i < genome.size(); ++i) {
        if (skew < minimum_skew) {
            min_indices.clear();
            minimum_skew = skew;
            min_indices.push_back(i);
        } else if (skew == minimum_skew) {
            min_indices.push_back(i);
        }
        switch (genome[i]) {
            case 'G':
                ++skew;
                break;
            case 'C':
                --skew;
                break;
            case 'A':
                break;
            case 'T':
                break;
        }
    }
    return min_indices;
}

void solve() {
    const auto genome = read_file_to_string("samples/MinimumSkew/rosalind_ba1f.txt");
    const auto mins = find_skew_minimums(genome);
    for (const auto & min : mins) {
        fmt::print("{} ", min);
    }
}
}
