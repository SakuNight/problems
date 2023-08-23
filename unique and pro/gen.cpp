#include <bits/stdc++.h>
#include <ranges>

// #define USE_STDIO

#define MAX_V 1000000000
#define INCREMENTAL_GEN

#define N 2000

using std::ranges::views::iota;

int64_t get_rd()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> gen_v(1, MAX_V);
    int64_t k = gen_v(gen);
    if (MAX_V <= 1000000000) {
        return k;
    } else {
        return k * gen_v(gen);
    }
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
    std::ofstream xout;
    xout.open("in.txt", std::ios::out | std::ios::trunc);
#endif

    xout << N << "\n";
#ifdef INCREMENTAL_GEN
    int64_t l = get_rd();
    for (auto i : iota(0, N)) {
        int64_t gap = get_rd();
        xout << l << " " << l + gap << "\n";
        l += gap + get_rd();
    }
#else
    for (auto i : iota(0, N)) {
        int64_t l = get_rd(), r = get_rd();
        if (l > r)
            std::swap(l, r);
        xout << l << " " << r << "\n";
    }
#endif
}