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

## 模

### 逆元

#### 快速幂法

>费马小定理
> 若模数p是质数，则有 
> $$ n^{p-1} \equiv 1 (mod \ p ) $$

$$inv(x) \equiv x^{p-2} $$

#### 扩展欧几里得法

$$a \cdot inv(a) = kb + 1 \iff inv(a) \cdot a - k \cdot b = 1$$

```cpp title=扩展欧几里得算法求逆元
void exgcd(int a, int b, int& x, int& y) {
  if (b == 0) {
    x = 1, y = 0;
    return;
  }
  exgcd(b, a % b, y, x);
  y -= a / b * x;
}
```

#### 对区间线性求逆元

##### 线性求逆元：递推

如何  $\mathrm{O}(n)$  求  $1 \sim n$  模  p  (  p  为素数) 的逆元?
假设现在要求  i  的逆元 $i^{-1}$

由带余除法可设  $p=i q+r$  ，则有
$$
i q+r \equiv 0(\bmod p)
$$

注意到  p  是质数，因此  r  不为  0 ， r  的逆元存在。
等式两边乘  $i^{-1} r^{-1}$  ，得到
$$
\begin{array}{c}
r^{-1} * q+i^{-1} \equiv 0(\bmod p) \\
i^{-1} \equiv-r^{-1} * q \equiv-(p \bmod i)^{-1}\left[\frac{p}{i}\right\rfloor(\bmod p)
\end{array}
$$

#### 线性求逆元：倒推

先求  $n  !$ 的逆元（可以使用扩展欧几里得算法，或者快速幂），然后利用
$$
((k-1)!)^{-1} \equiv k *(k!)^{-1}(\bmod p)
$$

倒推求出  $1!\ldots(n-1)  !$ 的逆元

## 欧拉定理和欧拉函数

### 定义

欧拉函数（Euler's totient function），即  $\varphi(n)$  ，表示的是小于等于  n  且和  n  互质的数的个数。比如说  $\varphi(1)=1$  。

当 n 是质数的时候，显然有  $\varphi(n)=n-1$  。

设  $n=p_{1}^{k_{1}} p_{2}^{k_{2}} \cdots p_{m}^{k_{m}}$  ，有

$$
\varphi(n)=n\left(1-\frac{1}{p_{1}}\right)\left(1-\frac{1}{p_{2}}\right) \cdots\left(1-\frac{1}{p_{m}}\right) \tag{1}
$$

### 质因数分解求法

即式(1)

```cpp
int euler_phi(int n){
  int res = n;
  for(int i = 2; i * i <= n; i++) {
    if(n % i == 0) {
      res = res / i * (i - 1); 
      for (; n % i == 0; n /= i);
    }
  }
  if (n != 1) res = res / n * (n - 1);
  return res;
}

```

### 埃氏筛求法

```cpp
int euler[MAX_N];
void euler_phi2(){
  for (int i = 0; i < MAX_N; i++) euler[i] = i;
  for (int i = 2; i < MAX_N; i++) {
    if (euler[i] == i) {
      for (int j = i; j < MAX_N; j += i) euler[j] = euler[j] / i * (i - 1);//对i的倍数的/phi（n）乘以这一项
    }
  }
}
```

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