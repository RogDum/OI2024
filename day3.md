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

```cpp title=vector
struct Edge {
    int u, v, w;
    Edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}
};

vector<vector<Edge>> adj; // 邻接表，每个索引代表一个节点，向量存储边

void addEdge(int u, int v, int w) {
    if (u >= adj.size() || v >= adj.size()) {
        int newSize = max(u, v) + 1;
        adj.resize(newSize);
    }
    adj[u].push_back(Edge(u, v, w)); // 添加一条从u到v的边，权重为w
}

// 遍历图的函数
void traverseGraph() {
    for (int u = 0; u < adj.size(); ++u) { // 遍历每一个节点
        cout << "Node " << u << " has edges to: \n";
        for (auto &e : adj[u]) { // 遍历u的所有边
            cout << "  Edge from " << e.u << " to " << e.v << " with weight " << e.w << "\n";
        }
    }
}
### 二分图的判定

换言之，我们需要知道是否可以将图中的顶点分成两个满足条件的集合。

显然，直接枚举答案集合的话实在是太慢了，我们需要更高效的方法。

考虑上文提到的性质，我们可以使用 DFS（图论） 或者 BFS 来遍历这张图。如果发现了奇环，那么就不是二分图，否则是。

```cpp
enum COLOR {
    black, white;
}

// DFS函数，用于尝试染色并检测是否为二分图
bool dfs(int u, int col) {
    color[u] = col; // 给节点u染色
    for (auto &e : adj[u]) {
        if (color[e.v] == -1) { // 如果相邻节点未被染色，尝试染相反的颜色
            if (!dfs(e.v, 1 - col)) return false;
        } else if (color[e.v] == col) { // 如果相邻节点颜色相同，表示存在奇环
            return false;
        }
    }
    return true;
}

// 检测图是否为二分图
bool isBipartite(int n) {
    color.assign(n, -1); // 初始化颜色数组，-1表示未染色
    for (int i = 0; i < n; ++i) {
        if (color[i] == -1) { // 如果节点未被染色，从该节点开始DFS
            if (!dfs(i, COLOR::black)) return false;
        }
    }
    return true;
}
```

### 拓扑排序

- 不断重复下面的过程
- 从图中选择一个入度为零的点。
- 输出该顶点，从图中删除此顶点及其所有的出边。

```cpp titl=拓扑排序
std::queue<int> q;
void topoSort() {
    (int i = 0; i < N; i++) {
        if(inDegree[i] == 0) q.push(i);
    }
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        cout << u << " ";
        for (auto &e : adj[u]) { // 遍历u的所有边
            inDegree[e.v]--;
            if(!inDegree[e.v]) q.push(e.v);
        }
    }
}
```

## 最近公共祖先LCA

LCA( lowest common ancestor )

### 倍增法

```cpp
void dfs(int u){ // 预处理深度
	vis[u]=true;
	for(int i=head[u]; i; i=G2[i].nxt){
		int v=G2[i].v, w=G2[i].w;
		if(vis[v]) continue;
		fa[v]=u;
		dep[v]=dep[u]+1;
		Min[0][v]=w;
		dfs(v);
	}
}

void lca_init(){ // 预处理每个点的2^k祖先
	for(int i=1;i<=n;i++) 
		if(!vis[i]) dfs(i);
	for(int i=1;i<=n;i++)
		anc[0][i] = fa[i];
	for(int k=1;k<=14;k++)
		for(int i=1;i<=n;i++){
			anc[k][i]=anc[k-1][anc[k-1][i]];
		}
}

for(int i = 1; i <= n; i++) //预处理 log_2(k)数组
	lg[i] = lg[i-1] + (1 << (lg[i-1] + 1) == i);

int lca(int x, int y) {
    if(dep[x] < dep[y])
        swap(x, y);
    while(dep[x] > dep[y]) {
        x = f[x][lg[dep[x] - dep[y]]];
    }
    if(x == y) return x;
    for(int k = lg[dep[x]]; k >= 0; k--) {
        if(f[x][k] != f[y][k]) {
            x = f[x][k];
            y = f[y][k];
        }
    }
    return f[x][0];
}
```

```cpp title=不使用lg数组的LCA
for(int k = 14; k >= 0; k--){
    if(dep[anc[k][x]] >= dep[y]){
    x = anc[k][x];
    }
}
```
