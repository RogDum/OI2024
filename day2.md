# day2

## 线段覆盖问题

$$
NOIP2010提高组T4 引水入城\\
有一个矩形。矩形上的格子有不同高度。\\你可以在第一行（x = 1）的任意多个格子放水，\\水会沿低的格子一直落下来。\\
求能否使最后一行（x = n）所有格子有水。
$$

### 贪心

不断找一个左端点在上一个右端点之内，右端点最远的区间

```cpp
    int left = 1, right = r[1][1];

    //统计区间数 
    while (left <= m) {
        for (int i = 1; i <= m; i++) {
            if (l[1][i] <= left) {
                right = max(right, r[1][i]);
            }
        }

        left = right + 1;
        ans++;
    }
```

### DP

用  $f z[i][j]$ 来表示  i  和  j  之间最少需要建多少座蓄水厂，并且用  $d[i]$  来表示  $1 \sim n$ 最少需要多少座蓄水厂（注意一开始要将这两个数组初始化为  $\infty$  哦）。我们可以将可以到达其他出口且不被其他入口所到达的点的左端点至右端点的值改为 1 ，例如左端点  =2  ，右端点  =7  时将  $f z[2][2] \sim   f z[2][7]$ 的值改为 1 。得到  $f z$  数组之后我们就可以求出  d  数组了，不难想出状态转移方程:
$$
d[i]=\min (d[i], d[j]+f z[j+1][i])
$$

## vector

### 访问元素

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // 使用[]运算符访问元素
    std::cout << "Element at index 0: " << vec[0] << std::endl;

    // 使用at方法访问元素
    std::cout << "Element at index 1: " << vec.at(1) << std::endl;

    // 使用front和back访问第一个和最后一个元素
    std::cout << "First element: " << vec.front() << std::endl;
    std::cout << "Last element: " << vec.back() << std::endl;
    // 在末尾添加元素
    vec.push_back(6);

    // 在指定位置插入元素
    vec.insert(vec.begin() + 2, 10); // 在索引2处插入10

    // 删除指定位置的元素
    vec.erase(vec.begin() + 3); // 删除索引3处的元素

    // 删除最后一个元素
    vec.pop_back();

    std::cout << "Size: " << vec.size() << std::endl;
    std::cout << "Capacity: " << vec.capacity() << std::endl;

    vec.clear();

    // 预留空间
    vec.reserve(10);
    //预留后即可下标访问

    std::cout << "Capacity after reserving: " << vec.capacity() << std::endl;
    
    return 0;
}
```

## priority_queue

`std::priority_queue` 的默认构造函数将创建一个最大堆，即优先级最高的元素具有最大的值。

```cpp
#include <iostream>
#include <queue>
#include <vector>

int main() {
    std::priority_queue<int> pq;

    pq.push(10);
    pq.push(5);
    pq.push(20);

    std::cout << "Priority queue elements in descending order:" << std::endl;
    while (!pq.empty()) {
        std::cout << pq.top() << " "; // 获取优先级最高的元素
        pq.pop(); // 移除优先级最高的元素
    }

    return 0;
}
```

### 使用自定义类型和比较器

可以使用自定义类型和比较器来实现更复杂的优先队列。例如，假设我们有一个包含任务优先级和任务描述的任务类型，我们希望按照任务优先级排序：

```cpp
#include <iostream>
#include <queue>
#include <vector>
#include <string>

struct Task {
    int priority;
    std::string description;

    // 定义比较器，优先级较高的任务排在队列前面
    bool operator<(const Task& other) const {
        return priority < other.priority;
    }
};

int main() {
    std::priority_queue<Task> pq;

    pq.push(Task{1, "Low priority task"});
    pq.push(Task{3, "High priority task"});
    pq.push(Task{2, "Medium priority task"});

    std::cout << "Tasks in priority order:" << std::endl;
    while (!pq.empty()) {
        Task t = pq.top();
        std::cout << t.priority << ": " << t.description << std::endl;
        pq.pop();
    }

    return 0;
}

## std::map

C++ 中的 `std::map` 是一种关联容器，用于存储键值对，其中每个键都是唯一的，并且键值对按键的顺序自动排序。以下是 `std::map` 的一些常见用法示例：

### 1. 创建和初始化

```cpp
#include <iostream>
#include <map>
#include <string>

int main() {
    // 创建一个空的map
    std::map<int, std::string> map1;

    // 使用列表初始化
    std::map<int, std::string> map2 = {
        {1, "one"},
        {2, "two"},
        {3, "three"}
    };

    // 插入键值对
    map1[1] = "one";
    map1[2] = "two";
    map1[3] = "three";

    // 使用insert函数插入
    map1.insert(std::make_pair(4, "four"));
    map1.insert({5, "five"});

    return 0;
}
```

### 2. 访问元素

```cpp
#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<int, std::string> map1 = {
        {1, "one"},
        {2, "two"},
        {3, "three"}
    };

    // 使用[]访问元素
    std::cout << "Key 1: " << map1[1] << std::endl;

    // 使用at函数访问元素
    std::cout << "Key 2: " << map1.at(2) << std::endl;

    // 遍历map
    for (const auto& pair : map1) {
        std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
    }

    return 0;
}
```

### 3. 修改元素

```cpp
#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<int, std::string> map1 = {
        {1, "one"},
        {2, "two"},
        {3, "three"}
    };

    // 修改元素
    map1[1] = "ONE";
    map1.at(2) = "TWO";

    for (const auto& pair : map1) {
        std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
    }

    return 0;
}
```

### 4. 查找元素

```cpp
#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<int, std::string> map1 = {
        {1, "one"},
        {2, "two"},
        {3, "three"}
    };

    // 使用find函数查找元素
    auto it = map1.find(2);
    if (it != map1.end()) {
        std::cout << "Found: Key: " << it->first << ", Value: " << it->second << std::endl;
    } else {
        std::cout << "Key not found" << std::endl;
    }

    // 使用count函数检查元素是否存在
    if (map1.count(3)) {
        std::cout << "Key 3 exists in the map." << std::endl;
    } else {
        std::cout << "Key 3 does not exist in the map." << std::endl;
    }

    return 0;
}
```

### 5. 删除元素

```cpp
#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<int, std::string> map1 = {
        {1, "one"},
        {2, "two"},
        {3, "three"}
    };

    // 使用erase函数删除元素
    map1.erase(2);  // 删除键为2的元素

    for (const auto& pair : map1) {
        std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
    }

    // 清空map
    map1.clear();

    if (map1.empty()) {
        std::cout << "map1 is empty." << std::endl;
    }

    return 0;
}
```

### 6. 获取大小

```cpp
#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<int, std::string> map1 = {
        {1, "one"},
        {2, "two"},
        {3, "three"}
    };

    std::cout << "Size of map1: " << map1.size() << std::endl;

    return 0;
}
```

### 7. 使用自定义比较函数

```cpp
#include <iostream>
#include <map>
#include <string>

// 自定义比较函数
struct CustomCompare {
    bool operator()(const int& lhs, const int& rhs) const {
        return lhs > rhs; // 使map按降序排列
    }
};

int main() {
    std::map<int, std::string, CustomCompare> map1 = {
        {1, "one"},
        {2, "two"},
        {3, "three"}
    };

    for (const auto& pair : map1) {
        std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
    }

    return 0;
}
```

## std::set

C++ 中的 `std::set` 是一种关联容器，用于存储唯一的元素，并且这些元素会自动按排序顺序排列。以下是 `std::set` 的一些常见用法示例：

### 1. 创建和初始化

```cpp
#include <iostream>
#include <set>

int main() {
    // 创建一个空的set
    std::set<int> set1;

    // 使用列表初始化
    std::set<int> set2 = {1, 2, 3, 4, 5};

    // 插入元素
    set1.insert(1);
    set1.insert(2);
    set1.insert(3);

    return 0;
}
```

### 2. 访问元素

`std::set` 不支持 `operator[]` 或 `at` 方法访问元素，因为它没有键值对。要访问元素，可以遍历集合。

```cpp
#include <iostream>
#include <set>

int main() {
    std::set<int> set1 = {1, 2, 3, 4, 5};

    // 遍历set
    for (const auto& elem : set1) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

### 3. 查找元素

```cpp
#include <iostream>
#include <set>

int main() {
    std::set<int> set1 = {1, 2, 3, 4, 5};

    // 使用find函数查找元素
    auto it = set1.find(3);
    if (it != set1.end()) {
        std::cout << "Found: " << *it << std::endl;
    } else {
        std::cout << "Element not found" << std::endl;
    }

    // 使用count函数检查元素是否存在
    if (set1.count(4)) {
        std::cout << "Element 4 exists in the set." << std::endl;
    } else {
        std::cout << "Element 4 does not exist in the set." << std::endl;
    }

    return 0;
}
```

### 4. 删除元素

```cpp
#include <iostream>
#include <set>

int main() {
    std::set<int> set1 = {1, 2, 3, 4, 5};

    // 删除元素
    set1.erase(3);

    // 遍历set
    for (const auto& elem : set1) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    // 清空set
    set1.clear();

    if (set1.empty()) {
        std::cout << "set1 is empty." << std::endl;
    }

    return 0;
}
```

### 5. 获取大小

```cpp
#include <iostream>
#include <set>

int main() {
    std::set<int> set1 = {1, 2, 3, 4, 5};

    std::cout << "Size of set1: " << set1.size() << std::endl;

    return 0;
}
```

### 6. 使用自定义比较函数

```cpp
#include <iostream>
#include <set>

// 自定义比较函数
struct CustomCompare {
    bool operator()(const int& lhs, const int& rhs) const {
        return lhs > rhs; // 使set按降序排列
    }
};

int main() {
    std::set<int, CustomCompare> set1 = {1, 2, 3, 4, 5};

    // 遍历set
    for (const auto& elem : set1) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

### 7. 使用 `emplace` 插入元素

```cpp
#include <iostream>
#include <set>

int main() {
    std::set<int> set1;

    // 使用emplace插入元素
    set1.emplace(1);
    set1.emplace(2);
    set1.emplace(3);

    // 遍历set
    for (const auto& elem : set1) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

## std::multiset

C++ 中的 `std::multiset` 是一种关联容器，用于存储多个键相同的元素。`std::multiset` 会自动对元素进行排序。

### `std::multiset` 的作用

1. **维护动态有序序列**：
    - `std::multiset` 允许我们快速插入、删除和查找元素，并且始终保持元素有序。
    - 适用于需要频繁插入和删除元素，并且需要快速获取最小值或最大值的场景。

2. **解决滑动窗口问题**：
    - 可以用来维护一个固定大小的滑动窗口，方便地获取窗口内的最小值、最大值或中位数。

3. **处理具有重复元素的集合问题**：
    - 能处理包含重复元素的集合，并提供便捷的统计和查找功能。

#### 示例：求滑动窗口的最大值

```cpp
#include <iostream>
#include <vector>
#include <set>

std::vector<int> maxSlidingWindow(std::vector<int>& nums, int k) {
    std::multiset<int> window;
    std::vector<int> result;

    for (int i = 0; i < nums.size(); ++i) {
        if (i >= k) {
            window.erase(window.find(nums[i - k]));
        }
        window.insert(nums[i]);
        if (i >= k - 1) {
            result.push_back(*window.rbegin());
        }
    }
    return result;
}

int main() {
    std::vector<int> nums = {1, 3, 1, 2, 0, 5};
    int k = 3;
    std::vector<int> result = maxSlidingWindow(nums, k);

    for (int val : result) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

## 哈希 Hash

### 字符串Hash

```cpp
const int P = 1e9+7;
const int p = 31;

int hash(string s) {
    int ans = 0;
    for(int i = 0; i < s.length(); i++) {
    ans = ans * p % P;
        ans = (ans + s[i] - 'a') % P;
    }
    return ans;
}

```

前缀Hash
后缀Hash
区间Hash

```cpp
    for(int i = 1; i <= n; i++) {
        Hash[i] = (Hash[i-1]*MP%P + a[i])%P;
        base[i] = base[i-1]*MP%P;
    }
    for(int i = n; i >= 1; i--) {
        Hash_rev[i] = (Hash_rev[i+1]*MP%P + a[i])%P;
    }
```

区间hash[l,r]

```cpp
((Hash[r] - Hash[l-1] * base[r-l+1]) % P + P) % P;
```

## 哈夫曼树

### PFC编码

对某种不等长编码，每个字符的编码都不是其他字符的前缀\
可以发现将每个字符放在一棵树的叶节点上即可实现

有了上面的想法就能构造出一棵编码树，令叶节点的权重等于每个字符的词频，对文本编码的总长即是：从根结点到各叶结点的路径长度与相应叶节点权值的乘积之和，称为树的带权路径长度（Weighted Path Length of Tree，WPL）

### 定义

对于给定一组具有确定权值的叶结点，可以构造出不同的二叉树，其中，WPL 最小的二叉树 称为 霍夫曼树（Huffman Tree）。

### 构造

每次取权值最小的两个树或叶子组成二叉树，以此类推
