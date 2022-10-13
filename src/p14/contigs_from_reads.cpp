#include <fmt/format.h>
#include <unordered_map>

#include "contigs_from_reads.hpp"
#include "utils/util.hpp"

namespace p14 {
using Graph = std::unordered_map<std::string, std::vector<std::string>>;

const auto prefix = [](const std::string& text){ return text.substr(0, text.size() - 1); };
const auto suffix = [](const std::string& text){ return text.substr(1); };

auto suffix_composition(const std::string& text, uint32_t k) -> std::vector<std::string> {
    std::vector<std::string> res{};
    for (std::size_t i = 0; i < text.size() - k + 1; ++i) {
        res.push_back(text.substr(i, k - 1));
    }
    return res;
}

auto debruijn_from_strs(const std::vector<std::string>& strs) -> Graph {
    std::vector<std::string> kmers{};
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

using DegreeMap = std::unordered_map<std::string, std::pair<uint32_t, uint32_t>>;

auto get_degrees(const Graph& g) -> DegreeMap {
    DegreeMap map{};

    for (const auto & [start, list] : g) {
        map[start].second += list.size();

        for (const auto & end : list) {
            ++map[end].first;
        }
    }
    return map;
}

auto generate_contigs(const std::vector<std::string>& reads) -> std::vector<std::string> {
    auto graph = debruijn_from_strs(reads);
    auto degrees = get_degrees(graph);
    std::vector<std::string> contigs{};
    for (const auto & [start, list] : graph) {
        if (degrees[start].first == 1 && degrees[start].second == 1) {
            continue;
        }
    for (const auto & u : list) {
            auto contig = start;
            auto w = u;
            while (true) {
                contig += w[w.size() - 1];
                const auto w_degree = degrees[w];
                if (w_degree.first == 1 && w_degree.second == 1) {
                    w = graph[w][0];
                } else {
                    break;
                }
            }
            contigs.push_back(contig);
        }
    }
    return contigs;
}

void solve() {
    const auto file_str = read_file_to_string("samples/ContigsFromReads/rosalind_ba3k.txt");
    const auto reads = tokenize_str(file_str.data(), "\n\r\t");
    for (const auto & str : generate_contigs(reads)) {
        fmt::print("{} ", str);
    }
    fmt::print("\n");
}
}
