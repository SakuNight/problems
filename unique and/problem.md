# Unique And

## Description

给定一个非负整数集合 $S$，该集合由 $n$ 个**闭**区间 $[l_i, r_i](0 \leq l_i \leq r_i)$ 组成，集合包含区间中所有的整数。对于集合所有数执行同 $v$ 的按位与操作。输出操作后集合大小。

## Input

第一行包含两个正整数 $n, v$。$n$ 表示初始集合中的区间数量，$v$ 表示按位与操作的对象。  
接下来 $n$ 行，每行一对**闭**区间 $[l_i, r_i]$，表示区间中所有非负整数皆在集合中。

提示：
- 区间可能相交。
- 开 `long long`。

## Output

一个非负整数，表示操作后集合中的元素数量。

## Examples

### 1

```plain
1 127
0 100
```

```plain
101
```

### 2

```plain
1 0
0 100
```

```plain
1
```

## Ranges

$1 \leq n \leq 10^4$  
$1 \leq v \leq 10^{18}$  
$0 \leq l_i \leq r_i \leq 10^{18},1 \leq i \leq n$  
$0 \leq v \leq 10^{18}$