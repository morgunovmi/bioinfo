#pragma once

#include <cstdint>
#include <vector>
#include <iostream>
#include <cassert>

class DiGraph;
namespace p11 {
auto find_eulerian_path(DiGraph& g) -> std::vector<uint32_t>;
void solve();
}
