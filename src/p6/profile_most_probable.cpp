#include "profile_most_probable.hpp"

#include <sstream> 
#include <fmt/format.h>

#include "utils/util.hpp"

namespace p6 {
auto find_profile_most_probable_kmer(std::string_view text, std::size_t k, const profile_mat& profile) -> std::string_view {
    std::string_view most_probable{"Empty"};
    double max_prob = 0.0;

    for (std::size_t i = 0; i < text.size() - k + 1; ++i) {
        const auto pattern = text.substr(i, k);
        double cur_prob = 0.0;
        for (std::size_t j = 0; j < k; ++j) {
            std::size_t row_index = 0;
            switch (pattern[j]) {
                case 'A':
                    row_index = 0;
                    break;
                case 'C':
                    row_index = 1;
                    break;
                case 'G':
                    row_index = 2;
                    break;
                case 'T':
                    row_index = 3;
                    break;
            }

            const auto char_prob = profile[row_index][j];
            if (j == 0) {
                cur_prob = char_prob;
            } else {
                cur_prob *= char_prob;
            }
        }
        if (cur_prob > max_prob) {
            most_probable = pattern;
            max_prob = cur_prob;
        }
    }
    return most_probable;
}

auto parse_profile_mat(std::string_view mat_str, std::size_t k) -> profile_mat {
    const auto row_strs = tokenize(mat_str);

    profile_mat res = std::vector(4, std::vector<double>());
    for (std::size_t i = 0; i < 4; ++i) {
        std::stringstream ss{row_strs[i].data()};
        for (std::size_t j = 0; j < k; ++j) {
            double val = 0.0;
            ss >> val;
            res[i].push_back(val);
        }
    }
    return res;
}

void solve() {
    const auto file_str = read_file_to_string("samples/ProfileMostProbableKmer/rosalind_ba2c.txt");
    const auto [text, second_half] = split_once(file_str, "\n");
    const auto [k_str, mat_str] = split_once(second_half, "\n");

    const auto k = std::stoi(k_str.data());
    const auto profile = parse_profile_mat(mat_str, k);
    fmt::print("{}\n", find_profile_most_probable_kmer(text, k, profile));
}
}
