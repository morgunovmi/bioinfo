#include <set>
#include <fmt/format.h>
#include <unordered_map>
#include <stack>
#include <algorithm>

#include "find_eulerian_path.hpp"
#include "utils/util.hpp"

using AdjListMap = std::unordered_map<uint32_t, std::vector<uint32_t>>;

class DiGraph {
public:
    void AddEdge(uint32_t a, uint32_t b) {
        if (a > m_max) {
            m_max = a;
        }
        if (b > m_max) {
            m_max = b;
        }

        m_adjLists[a].push_back(b);
    }

    std::vector<uint32_t> GetList(uint32_t idx) {
        if (!m_adjLists.contains(idx)) {
            return {};
        } else {
            return m_adjLists[idx];
        }
    }

    AdjListMap m_adjLists;
    uint32_t m_max;
};

std::ostream& operator<<(std::ostream& os, const DiGraph& g) {
    for (const auto & [start, ends] : g.m_adjLists) {
        os << start << " -> ";
        for (std::size_t i = 0; i < ends.size(); ++i) {
            os << ends[i];
            if (i != ends.size() - 1) {
                os << ',';
            }
        }
        os << '\n';
    }
    return os;
}

namespace p11 {
using DegreeMap = std::unordered_map<uint32_t, std::pair<uint32_t, uint32_t>>;

auto get_degrees(const DiGraph& g) -> DegreeMap {
    DegreeMap map{};

    for (const auto & [start, list] : g.m_adjLists) {
        map[start].second += list.size();

        for (const auto & end : list) {
            ++map[end].first;
        }
    }
    return map;
}

auto is_eulerian(const DiGraph& g) -> bool {
    const auto degrees = get_degrees(g);
    for (const auto & [node, pair] : degrees) {
        if (pair.first != pair.second) {
            return false;
        }
    }
    return true;
}

auto eulerian_cycle(DiGraph& g) -> std::vector<uint32_t> {
    assert(is_eulerian(g));
    std::unordered_map<uint32_t, uint32_t> edge_count;
 
    for (const auto & [start, list] : g.m_adjLists) {
        edge_count[start] = list.size();
    }

    std::vector<uint32_t> cycle{};
    std::stack<uint32_t> cur_path{};

    cur_path.push(0);
    uint32_t cur_n = 0;
    while(!cur_path.empty()) {
        if (!g.GetList(cur_n).empty()) {
            cur_path.push(cur_n);
            const auto next_n = g.m_adjLists[cur_n].back();
            --edge_count[cur_n];
            g.m_adjLists[cur_n].pop_back();

            cur_n = next_n;
        } else {
            cycle.push_back(cur_n);

            cur_n = cur_path.top();
            cur_path.pop();
        }
    }
    std::reverse(cycle.begin(), cycle.end());
    return cycle;
} 

auto find_eulerian_path(DiGraph& g) -> std::vector<uint32_t> {
    const auto degrees = get_degrees(g);
    uint32_t bn = 0, an = 0;
    for (const auto & [node, pair] : degrees) {
        if (pair.first == pair.second + 1) {
            bn = node;
        } else if (pair.second == pair.first + 1) {
            an = node;
        } else if (pair.first != pair.second) {
            assert(0 && "Incorrect graph");
        }
    }
    g.AddEdge(bn, an);

    const auto cycle = eulerian_cycle(g);

    std::vector<uint32_t> path{};
    uint32_t index = 0;
    for (std::size_t i = 0; i < cycle.size(); ++i) {
        if (cycle[i] == bn && cycle[(i + 1) % cycle.size()] == an) {
            index = i + 1;
        }
    }

    path.push_back(cycle[index]);
    for (std::size_t i = 1; i < cycle.size(); ++i) {
        path.push_back(cycle[(index + i) % cycle.size()]);
    }

    return path;
}

void solve() {
    const auto file_str = read_file_to_string("samples/EulerianPath/rosalind_ba3g.txt");
    const auto lists = tokenize(file_str, "\n");
    const auto n = lists.size();

    DiGraph g{};
    for (std::size_t i = 0; i < n; ++i) {
        const auto [start_str, end_nodes_str] = split_once(lists[i], " -> ");
        const auto end_nodes_strs = tokenize(end_nodes_str, ","); 

        for (std::size_t j = 0; j < end_nodes_strs.size(); ++j) {
            g.AddEdge(std::stoi(start_str.data()), std::stoi(end_nodes_strs[j].data()));
        }
    }

    const auto path = find_eulerian_path(g);

    for (std::size_t i = 0; i < path.size(); ++i) {
        std::cout << path[i];
        if (i != path.size() - 1) {
            fmt::print("->");
        }
    }
    fmt::print("\n");
}
}
