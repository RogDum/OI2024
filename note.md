# 整除

## 筛法

### 埃氏筛法

从小到大标记每个数的倍数

```cpp
bitset<> is_prime;
vector<int> prime;

is_prime[0] = is_prime[1] = false;
for (i..n) is_prime[i] = true;//先全部标记为质数

for (i..n) {
    if (is_prime[i]) {
      prime.push_back(i);//在之前没有被筛掉说明没有比它小的因数，即是质数
      if (i^2 > n) continue;//到√n即筛出到n的所有质数
      for (j = i^2; j <= n; j += i)
        // 因为从 2 到 i - 1 的倍数我们之前筛过了，这里直接从i的倍数开始，提高了运行速度
        is_prime[j] = false;  // 是 i 的倍数的均不是素数
    }
}
```

### 欧拉筛

让每个合数都只被标记一次

```cpp
vector<int> pri;
bool not_prime[N];

void pre(int n) {
  for (i..n) {
    if (!not_prime[i]) pri.push_back(i);
    for (int pri_j : pri) {
      if (i * pri_j > n) break;
      not_prime[i * pri_j] = true;
      if (i % pri_j == 0) break;// i % pri_j == 0 换言之，i 之前被 pri_j 筛过了.由于 pri 里面质数是从小到大的，所以 i 乘上其他的质数的结果一定会被pri_j 的倍数筛掉，就不需要在这里先筛一次，所以这里直接 break掉就好了
    }
  }
}
```

## 模

### 快速幂

$$
\begin{align*}
\tag 1 设a^b&=\prod a^{n_i\cdot2^i}=a^{(101010)_2} \\
\tag 2 有ans&=b[-1]*a\\
ans&=b[-2]*a^2\\
&...

\end{align*}
$$

```cpp
while (b > 0) {
    if (b & 1) res = res * a;//b&1即为b[-1]
    a = a * a;
    b >>= 1;
}
```

### 扩展欧几里得

### 线性求逆元

## 欧拉定理和欧拉函数

### 质因数分解求法

### 埃氏筛求法

### 推论

$$a^b=a^{b\%\phi(m)}  (mod\ m)$$

## 中国剩余定理

有下列方程
$$ x\equiv a_1\ (mod\ n_1)\\

x\equiv a_1\ (mod\ n_1)\\

......\\

x\equiv a_k\ (mod\ n_k)
$$
解：
$$
\begin{align*}令N&=\prod n_k,\\
m_i&=\frac{N}{Ni},\\
j_i&=m_i^{-1}\ (mod\ n_i),\\
c_i&=m_i*j_i,\\
有x&=\sum a_i c_i
\end{align*}
$$
