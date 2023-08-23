#include <algorithm>
#include <bitset>
#include <cstdio>
#include <cstdlib>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <limits.h>
#include <random>
#include <ranges>
#include <set>
#include <tuple>
#include <utility>
#include <vector>

#define MAX_V 1000

// #define INCREMENTAL_MAKEDATA

const int N = 10;

using std::ranges::views::iota;

// #define USE_STDIO

int64_t get_rd()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> gen_v(1, MAX_V);
    return gen_v(gen);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

#ifdef USE_STDIO
    auto& xout = std::cout;
#else
    std::ofstream xout;
    xout.open("in.txt", std::ios::out | std::ios::trunc);
#endif

    xout << N << " " << get_rd() << "\n";

#ifdef INCREMENTAL_MAKEDATA
    int64_t l = get_rd();
    for (auto i : iota(0, N)) {
        int64_t gap = get_rd();
        xout << l << " " << l + gap << "\n";
        l += gap + get_rd();
    }
#else
    for (auto i : iota(0, N)) {
        int64_t l, r;
        l = get_rd() * get_rd();
        r = get_rd() * get_rd();
        if (l > r) {
            std::swap(l, r);
        }
        xout << l << " " << r << "\n";
    }
#endif
}
