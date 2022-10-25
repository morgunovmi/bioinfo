#include "k_universal_string.hpp"

#include <algorithm>
#include <iostream>
#include <fmt/format.h>
#include <string_view>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <fstream>

namespace p12 {
using Graph = std::unordered_map<std::string_view, std::vector<std::string_view>>;

auto generate_binary_strs(uint32_t k) -> std::vector<std::string> {
    std::vector<std::string> res{};
    for (int n = 0; n < std::pow(2, k); ++n) {
        res.emplace_back(fmt::format("{:0>{}b}", n, k));
    }
    return res;
}

const auto prefix = [](std::string_view text){ return text.substr(0, text.size() - 1); };
const auto suffix = [](std::string_view text){ return text.substr(1); };

auto suffix_composition(std::string_view text, uint32_t k) -> std::vector<std::string_view> {
    std::vector<std::string_view> res{};
    for (std::size_t i = 0; i < text.size() - k + 1; ++i) {
        res.push_back(text.substr(i, k - 1));
    }
    return res;
}

auto debruijn_from_strs(const std::vector<std::string>& strs) -> Graph {
    std::vector<std::string_view> kmers{};
    for (const auto & pattern : strs) {
        const auto suf_comp = suffix_composition(pattern, pattern.size());
        std::move(suf_comp.begin(), suf_comp.end(), std::back_inserter(kmers));
    }
    Graph g{};
    for (const auto & k : kmers) {
        g[k] = {};
    }
    for (const auto & k : strs) {
        g[prefix(k)].push_back(suffix(k));
    }
    return g;
} 

auto eulerian_cycle(Graph& g) -> std::vector<std::string_view> {
    std::vector<std::string_view> path{};
    std::stack<std::string_view> stack{};
    const auto random_vertex = g.begin()->first;
    stack.push(random_vertex);
    while (!stack.empty()) {
        const auto u_v = stack.top();
        if (!g[u_v].empty()) {
            const auto w = g[u_v].back();
            stack.push(w);
            g[u_v].pop_back();
        } else {
            path.push_back(stack.top());
            stack.pop();
        }
    }
    std::reverse(path.begin(), path.end());
    return path;
}

auto find_k_universal_circular_string(uint32_t k) -> std::string {
    auto db = debruijn_from_strs(generate_binary_strs(k));
    auto cycle = eulerian_cycle(db);

    std::string universal{cycle[0]};
    for (std::size_t i = 1; i < cycle.size() - k + 1; ++i) {
        universal += cycle[i][cycle[i].size() - 1];
    }

    return universal;
}

void solve() {
    uint32_t k = 0;
    if (auto ifs = std::ifstream{"samples/UniversalString/rosalind_ba3i.txt"}) {
        ifs >> k;
    }
    fmt::print("{}\n", find_k_universal_circular_string(k));
}
}
