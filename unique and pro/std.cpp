#include <bits/stdc++.h>
#include <ranges>

// #define USE_STDIO

using std::ranges::views::iota;

const int64_t M = 1e18 + 5;
const int R = 2e5 + 5;

int64_t pow2[65];

int n;
std::vector<std::pair<int64_t, int64_t>> raw_ranges;

void sanitize()
{
    int64_t max_r = -1;
    int deleted_count = 0;
    std::sort(raw_ranges.begin(), raw_ranges.end());
    for (auto i : iota(0, n - 1)) {
        auto &l1 = raw_ranges[i].first, r1 = raw_ranges[i].second;
        if (r1 <= max_r) {
            l1 = r1 = LLONG_MAX;
            ++deleted_count;
            continue;
        }
        l1 = std::max(l1, max_r + 1);
        max_r = std::max(max_r, r1);
    }
    std::sort(raw_ranges.begin(), raw_ranges.end());
    n -= deleted_count;
    raw_ranges.resize(n);
}

bool short_range_compare(const std::pair<int64_t, int>& r1, const std::pair<int64_t, int>& r2)
{
    return r1.second > r2.second;
}

std::vector<std::pair<int64_t, int>> shorts;
class pair_hash {
public:
    int64_t operator()(const std::pair<int64_t, int>& p) const
    {
        return std::hash<int64_t>()(p.first) ^ std::hash<int>()(p.second);
    }
};
std::unordered_set<std::pair<int64_t, int>, pair_hash> S;
// std::set<std::pair<int64_t, int>> S;

std::pair<int64_t, int> edit(int64_t prefix, int bit_shift, int cnt)
{
    if (bit_shift >= cnt) {
        return { 0, cnt };
    } else {
        return { prefix & (pow2[cnt] - 1), bit_shift };
    }
}

bool check(int steps)
{
    int64_t count = 0;
    shorts.clear();
    S.clear();

    for (auto p : iota(0, (int)raw_ranges.size())) {
        auto c = raw_ranges[p];
        auto l = c.first, r = c.second;
        while (l <= r) {
            int i = 0;
            while ((l & pow2[i]) == 0 && l + pow2[i + 1] - 1 <= r) {
                ++i;
            }
            shorts.push_back(edit(l, i, steps));
            l += pow2[i];
        }
    }

    std::sort(shorts.begin(), shorts.end(), short_range_compare);

    for (auto c : shorts) {
        int64_t prefix = c.first;
        int bit_shift = c.second, has = 0;
        for (int i : iota(bit_shift, 63)) {
            if (S.contains({ prefix & (~(pow2[i] - 1)), i })) {
                has = 1;
                break;
            }
        }
        if (!has) {
            count += pow2[bit_shift];
            S.insert({ prefix, bit_shift });
        }
    }

    return count < pow2[steps];
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
    for (auto i : iota(1, 63)) {
        pow2[i] = pow2[i - 1] * 2;
    }

    xin >> n;
    for (auto i : iota(0, n)) {
        int64_t l, r;
        xin >> l >> r;
        raw_ranges.push_back({ l, r });
    }
    sanitize();

    int l = 0, r = 63;
    while (l < r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }

    xout << l << "\n";
}