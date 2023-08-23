# Unique And

考虑到对于两个数 $x > y$，执行位操作后可能使得 $x' < y'$，因此不能直接对区间端点进行操作。考虑将区间分为若干段使得每一段都可以对端点直接进行位操作。

分开后的每一个小区间需要满足以下两个条件：

- 区间内所有数的二进制表示需要有相同的前缀。
- 假设除去相同的二进制前缀外， 还剩下 $k$ 位，需要确保区间内包含 $2^k$ 个不同的数，即只考虑后 $k$ 位的话，需要包含从 $0$ 到 $2^k - 1$ 的所有数。

容易发现此时的区间可以直接执行位操作且不会导致左右端点失效。对于相同的前缀，执行位操作后所有数的前缀依然是相同的。对于后缀，$0\&1=0,1\&1=0$，即不会导致上述条件失效。

考虑将操作后的所有区间的数去重，此时每个区间用两个数表示：前缀的值 $v_i$（用 $0$ 填充后缀），后缀长度 $len_i$。若两个区间 $[l_i,r_i],[l_j,r_j]\ (len_i<=len_j)$ 出现重复的数，那么一定有区间 $j$ 的前缀是区间 $i$ 前缀的一部分，且区间 $i$ 所有的数均被区间 $j$ 包含。于是考虑将所有区间按照 $len$ 从大到小排序，然后枚举区间，若该区间中的数已被 $len$ 更大的区间包含，则舍弃。否则累计答案。该过程可以使用 `set` 维护。