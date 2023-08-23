// compile under C++ 20

#include "limits.h"
#include <algorithm>
#include <array>
#include <bitset>
#include <cstdio>
#include <cstdlib>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <iterator>
#include <ranges>
#include <set>
#include <stack>
#include <tuple>
#include <utility>
#include <vector>

// #define USE_STDIO

using std::ranges::views::iota;
using RType = std::tuple<int64_t, int>;

const int R = 3e7 + 5;
const int64_t M = 1e18 + 5;

int64_t pow2[63];

std::pair<int64_t, int64_t> raw_ranges[R];
int n, fragment_count;
int64_t v, answer;
std::array<RType, R> raws;
std::array<RType, R>::iterator raws_begin, raws_end;
std::set<RType> S;

bool rtype_compare(const RType& lt, const RType& rt)
{
    return std::get<1>(lt) > std::get<1>(rt);
}

RType edit(int64_t prefix, int bit_shift)
{
    int64_t vt = v, new_prefix = 0;
    int new_bit_shift = 0, bit_count = 0, bit_position = 0;
    while (vt) {
        if (vt & 1) {
            if (prefix & pow2[bit_position]) {
                new_prefix |= pow2[bit_count];
            }
            if (bit_shift > bit_position) {
                ++new_bit_shift;
            }
            ++bit_count;
        }
        vt >>= 1;
        ++bit_position;
    }
    return { new_prefix, new_bit_shift };
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

#ifdef USE_STDIO
    auto& xin = std::cin;
    auto& xout = std::cout;
#else
    std::ifstream xin;
    std::ofstream xout;
    xin.open("in.txt", std::ios::in);
    xout.open("std.txt", std::ios::out | std::ios::trunc);
#endif

    pow2[0] = 1;
    for (int i = 1; i < 63; ++i) {
        pow2[i] = 2 * pow2[i - 1];
    }

    xin >> n >> v;

    for (auto i : iota(0, n)) {
        int64_t l, r;
        xin >> l >> r;
        raw_ranges[i] = { l, r };
    }
    std::sort(raw_ranges, raw_ranges + n);
    int64_t max_r = -1, deleted_count = 0;
    for (auto i : iota(0, n)) {
        int64_t &l = raw_ranges[i].first, r = raw_ranges[i].second;
        if (max_r >= r) {
            l = r = LLONG_MAX;
            ++deleted_count;
            continue;
        } else if (l <= max_r) {
            l = max_r + 1;
        }
        max_r = std::max(max_r, r);
    }
    std::sort(raw_ranges, raw_ranges + n);
    n -= deleted_count;

    for (auto c : iota(0, n)) {
        // xout << "Result of new range:\n";
        int64_t l = raw_ranges[c].first, r = raw_ranges[c].second;
        while (l <= r) {
            int i = 0;
            while ((l & pow2[i]) == 0 && l + pow2[i + 1] - 1 <= r) {
                ++i;
            }
            raws[fragment_count] = edit(l, i);
            // xout << (std::bitset<8>(std::get<0>(raws[fragment_count]))) << " (" << std::get<0>(raws[fragment_count]) << ") " << std::get<1>(raws[fragment_count]);
            l += pow2[i];
            ++fragment_count;
        }
    }

    std::swap(n, fragment_count);
    raws_begin = raws.begin();
    raws_end = raws.begin();
    std::advance(raws_end, n);
    std::sort(raws_begin, raws_end, rtype_compare);

    for (auto it = raws_begin; it != raws_end; ++it) {
        int64_t prefix;
        int bit_shift, has = false;
        std::tie(prefix, bit_shift) = *it;
        for (auto i : iota(bit_shift, 63)) {
            if (S.contains({ prefix & (~(pow2[i] - 1)), i })) {
                has = true;
                break;
            }
        }
        if (!has) {
            S.insert({ prefix, bit_shift });
            answer += pow2[bit_shift];
        }
    }

    xout << answer << "\n";

    return 0;
}