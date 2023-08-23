#include <algorithm>
#include <bitset>
#include <cstdio>
#include <cstdlib>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <set>
#include <tuple>
#include <utility>
#include <vector>

// #define USE_STDIO
// #define SHOW_EXPLANATION
#define BITSET_WIDTH 10

std::vector<std::tuple<int64_t, int64_t>> ranges;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

#ifdef USE_STDIO
    auto& xout = std::cout;
    auto& xin = std::cin;
    auto& xerr = std::cerr;
#else
    std::ofstream xout, xerr;
    std::ifstream xin;
    xout.open("sol.txt", std::ios::out | std::ios::trunc);
    xin.open("in.txt", std::ios::in);
#ifdef SHOW_EXPLANATION
    xerr.open("explanation.txt", std::ios::out | std::ios::trunc);
#endif
#endif

    int n;
    int64_t v;
    xin >> n >> v;
    while (n--) {
        int64_t l, r;
        xin >> l >> r;
        ranges.push_back({ l, r });
    }

    std::set<int64_t> S;
    for (int i = 0; i < ranges.size(); ++i) {
        int64_t l, r;
        std::tie(l, r) = ranges[i];
        for (int64_t j = l; j <= r; ++j) {
            S.insert(j & v);
        }
    }

    xout << (S.size()) << "\n";

#ifdef SHOW_EXPLANATION
    xerr << "v:\n"
         << std::bitset<10>(v) << "\n";

    xerr << "Number list:\n";
    for (auto n : S) {
        xerr << (std::bitset<BITSET_WIDTH>(n)) << " " << n << "\n";
    }
    xerr << "\n";
#endif
}