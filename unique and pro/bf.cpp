#include <bits/stdc++.h>
#include <ranges>

// #define USE_STDIO

using std::ranges::views::iota;

int64_t remains, total, pow2[63];
int n;
std::vector<std::pair<int64_t, int64_t>> ranges;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

#ifdef USE_STDIO
    auto& xin = std::cin;
    auto& xout = std::cout;
    auto& xerr = std::cerr;
#else
    std::ifstream xin;
    std::ofstream xout, xerr;
    xin.open("in.txt", std::ios::in);
    xout.open("bf.txt", std::ios::out | std::ios::trunc);
    xerr.open("exp.txt", std::ios::out | std::ios::trunc);
#endif

    pow2[0] = 1;
    for (int i : iota(1, 63)) {
        pow2[i] = pow2[i - 1] * 2;
    }

    xin >> n;
    for (auto i : iota(0, n)) {
        int64_t l, r;
        xin >> l >> r;
        ranges.push_back({ l, r });
        total += r - l + 1;
    }

    for (int steps = 1; steps < 20; ++steps) {
        for (int i = 0; i < pow2[steps]; ++i) {
            int has_except = false;
            for (auto c : ranges) {
                for (auto v : iota(c.first, c.second + 1)) {
                    v &= pow2[steps] - 1;
                    if (v == i) {
                        has_except = true;
                        break;
                    }
                }
                if (has_except) {
                    break;
                }
            }
            if (!has_except) {
                xout << steps << "\n";
                return 0;
            }
        }
    }
}