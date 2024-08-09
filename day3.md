# day3

## pair

```cpp
pair f(){
    return {a,b};
}
pair<int, double> p1;  //使用默认构造函数
p1.first = 1;
p1.second = 2.5;
pair<int, double> p1;
p1 = make_pair(1, 1.2);
pair<int, double> p1(1, 1.2);
```

## tuple

## multiset

维护动态有序列；维护固定大小的滑动窗口，得到其最大最小值；

## multimap

按成绩排名

## 二维前缀和

$$S[x][y] = \sum_{x\in{[1,m]y\in{[1,y]}}}a[x][y]$$

$$\sum_{x\in{[m_1,m_2]y\in{[n_1,n_2]}}}a[x][y]=S[m_2][n_2]-S[m_2][n_1]-S[m_1][n_2]+S[m_1][n_1]$$

## 二分

lower_bound 第一个>=x的数\
upper_bound 第一个>x的数

```cpp
n = sizeof(arr)/sizeoff(arr[0]);
lower_bound(arr,arr+n,4);
lower_bound(vec.begin(),vec.end(),4);
```

### 二分答案

p2678 "最短跳跃距离的最大值"

## 全排列

```cpp
void print_permutation(int n, int* A, int cur)
{
    if(n == cur)//排列到n个长度后输出
    {
        for(int i = 0; i < n; i++)
            cout << A[i];
        cout << endl;
        return;
    }
    else
    {
        for(int i = 0; i < n; i++)
        {
            int ok = 1;
            for(int j = 0; j < cur; j++)
            //判断i是不是已经使用过了
                if(A[j] == i)
                    ok = 0;
            if(ok)
            {
                A[cur] = i;
                print_permutation(n, A, cur + 1);
            }
        }
    }
}
```

可重集的排列

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

void printPermutation(int n, int* p, int cur, int* arr)        //n是元素个数，p是初始元素集合，cur是当前位置，arr是目前已经排列的部分
{
    int i, j;
    if (cur == n)
    {
        for (i = 0; i < n; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }
    else
    {
        for (i = 0; i < n; i++){
            if (i == 0 || p[i] != p[i-1])    //只需要检查第一个元素，以及与前一个元素不相同的元素即可，保证不重复
            {
                int c1 = 0, c2 = 0;
                for (j = 0; j < cur; j++)    //已经排列的元素中p[i]出现的次数
                {
                    if (arr[j] == p[i])
                    {
                        c1++;
                    }
                }
                for (j = 0; j < n; j++)        //全部元素中p[i]出现的次数
                {
                    if (p[i] == p[j])
                    {
                        c2++;
                    }
                }
                if (c1 < c2)    //保证不遗漏
                {
                    arr[cur] = p[i];
                    printPermutation(n, p, cur+1, arr);
                }
            }
        }
    }
}

int main()
{
    int p[5] = {4, 1, 1, 4, 1};
    sort(p, p+5);    //排序
    int arr[5] = {0};
    printPermutation(5, p, 0, arr);
    return 0;
}
```

`std::next_permutation`

## 图论

### 邻接表存储
