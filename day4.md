# day 4

## 单源最短路

### BFS

> [!example]+ 例题 P2296 [NOIP2014提高组 D2T2 寻找道路](https://www.luogu.com.cn/problem/P2296)

### Bellman-ford算法

- 令`d[i]`为`INF`
- 对所有边依次进行松弛操作
- 重复执行步骤(2)共 **n-1** 轮

时间复杂度为$\mathcal{O}(nm)$，如果操作完毕后，还存在可松弛的边，则说明存在负环

```cpp
bool Bellman_ford() {
	// 对距离数组初始化
	for(int i = 1; i <= n; i++) {
		dis[i] = INF;
	}
	dis[S] = 0;

	for(int t = 1; t <= n; t++) {
		bool flag = false;
		for(int i = 1; i <= m; i++) {
			if(dis[g[i].u] + g[i].w < dis[g[i].v]) {
				dis[g[i].v] = dis[g[i].u] + g[i].w;
				flag = true;
			}
		}
		if(!flag) break;
		if(t == n) return false;  // 存在负环
	}
	return true;
}
```

### Dijkstra算法

无负环

没有堆优化的时间复杂度：O(n^2+m)
有堆优化的时间复杂度：O((n+m)logm)

- 将S入队
- 取没有访问过的队首，遍历邻居，松弛操作更新dis，全部入队
- 优先级队列的排序依据是：`dis`

```cpp title=一种写法，建议使用std::pair改写
struct node{
	int u,d;
	bool operator < (const node &A) const{
		return A.d < d;
	}
};

priority_queue<node> q;

void Dijkstra(){
	memset(dis, 0x3f, sizeof dis);
	dis[s] = 0;
	for(int i = head[s]; i; i = G[i].nxt){
		int v = G[i].v, w = G[i].w;
		dis[v] = w;
		q.push((node){v, w});
	}
	while(!q.empty()){
		int u = q.top().u, d = q.top().d;
		q.pop();
		if(d != dis[u]) continue;
		for(int i = head[u]; i; i = G[i].nxt){
			int v = G[i].v, w = G[i].w;
			if(dis[u] + w < dis[v]){
				dis[v] = dis[u] + w;
				q.push((node){v, dis[v]});
			}
		}
	}
}
```

> [!example]+ 例题 [P4779 【模板】单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)
### SPFA

==SPFA在稀疏图上的平均性能较好，一般图上的最坏时间复杂度为O(nm)，容易被卡掉，仅在有负环的情况下使用==

对于最短路径长度未曾更新过的顶点，不必松弛由它引出的边。
使用队列：仅在某个顶点的dis更新后，才将该顶点加入队列中，算法在每一轮取队首的顶点，并松弛其关联的边，直到队列为空

```cpp
// head : 邻接表头数组，其中head[u]为结点u的邻接表表头
// e : 邻接表数组，其中e[i].nxt为下一个邻接表元素
// dis : 记录源点到各点的距离
// val : 记录各条边的权值
// in_que : 记录各点是否在队列中以避免重复压栈
void SPFA()
{
    for (int i = 1; i <= n; i++)
    {
        dis[i] = INF;
        in_que[i] = 0;
    }

    dis[S] = 0; // 设起点最短距离为0初始化
    queue<int> q; // 普通队列存储点的队列
    q.push(S);
    in_que[S] = 1;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        in_que[u] = 0;

        for (int i = head[u]; i; i = e[i].nxt)
        {
            int v = e[i].tv;
            if (dis[u] + val[i] < dis[v])
            {
                dis[v] = dis[u] + val[i];
                if (!in_que[v])
                {
                    q.push(v);
                    in_que[v] = 1;
                }
            }
        }
    }
}
```


> [!example]+ 例题 [P9751 CSP-J 2023 T4 旅游巴士](https://www.luogu.com.cn/problem/P9751)

> [!tip]+ Solution
> Dijkstra过程中修改边权，dis数组增加一个维度考虑对k取模

> [!example]+ 例题 P1073 [NOIP2009 最优贸易](https://www.luogu.com.cn/problem/P1073)

> [!tip]+ Solution
> 建正图通过SPFA求最小值，建反图通过SPFA求最大值

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read(){
	int x=0,f=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
	return f?-x:x;
	
}

const int N=1e5+50;
const int M=5e5+50;
const int inf=0x3f3f3f3f;
int n,m,ans;
int minv[N],maxv[N];
bool vis[N],_vis[N];
queue<int> q;

struct val{
	int cost,p;
}a[N];

struct pos{
	struct Edge{
	int u,v,nxt;
	}G[M<<1];
	int head[N],cnt;
	void adde(int u,int v){
		G[++cnt].u=u;
		G[cnt].v=v;
		G[cnt].nxt=head[u];
		head[u]=cnt;
	}
	void bfs(){
		q.push(1);
		vis[1]=true;
		while(!q.empty()){
			int u=q.front(); q.pop();
			for(int i=head[u];i;i=G[i].nxt){
				int v=G[i].v;
				if(vis[v]) continue;
				vis[v]=true;
				q.push(v);
			}
		}
	}
	bool had[N];
	void work(){
		for(int i=1;i<=n;i++){
			int p=a[i].p;
			if(!vis[p]) continue;
			had[p]=true;
			for(int j=head[p];j;j=G[j].nxt){
				int v=G[j].v;
				if(had[v]) continue;
				had[v]=true;
				minv[v]=min(minv[v],minv[p]);
			}
		}
	}
}t1; 

struct neg{
	struct Edge{
	int u,v,nxt;
	}G[M<<1];
	int head[N],cnt;
	void adde(int u,int v){
		G[++cnt].u=u;
		G[cnt].v=v;
		G[cnt].nxt=head[u];
		head[u]=cnt;
	}
	void bfs(){
		q.push(n);
		_vis[n]=true;
		while(!q.empty()){
			int u=q.front(); q.pop();
			for(int i=head[u];i;i=G[i].nxt){
				int v=G[i].v;
				if(_vis[v]) continue;
				_vis[v]=true;
				q.push(v);
			}
		}
	}
	bool had[N];
	void work(){
		for(int i=n;i>=1;i--){
			int p=a[i].p;
			if(!_vis[p]) continue;
			had[p]=true;
			for(int j=head[p];j;j=G[j].nxt){
				int v=G[j].v;
				if(had[v]) continue;
				had[v]=true;
				maxv[v]=max(maxv[v],maxv[p]);
			}
		}
	}	
}t2;

void init(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)
		a[i].cost=read(),a[i].p=i;
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),z=read();
		t1.adde(u,v);
		t2.adde(v,u);
		if(z==2) {
			t1.adde(v,u);
			t2.adde(u,v);
		}
	}
	for(int i=1;i<=n;i++)
		minv[i]=maxv[i]=a[i].cost;
}

bool cmp(val A,val B){
	return A.cost<B.cost;
}

int main(){
	//freopen("test.in","r",stdin);
	//freopen("test.out","w",stdout);
	init();
	t1.bfs();
	t2.bfs();
	sort(a+1,a+n+1,cmp);
	t1.work();
	t2.work();
	for(int i=1;i<=n;i++)
		if(vis[i] && _vis[i])
			ans=max(ans,maxv[i]-minv[i]);
	printf("%d\n",ans);
	return 0;
}
```

> [!example]+ 例题 P4568 [JLOI2011 飞行路线](https://www.luogu.com.cn/problem/P4568)

> [!tip]+ Solution
> 建分层图，或者修改dis数组的定义

## 单源次短路

1. 通过Dijkstra得到`dis`数组
2. 枚举所有顶点$v_{i}$，枚举其所有邻接的点$v_{j}$，得到次短路数组`f[i]`
3. 对`f`做Dijkstra，若`f[i]==INF`，则说明不存在次短路

```cpp
// dis : 从源点到各点的最短路径长度
// f : 从源点到各点的次短路径长度
// head: 邻接表头数组，其中head[u]为结点u的邻接表表头
// e : 邻接表数组，其中e[i].nxt为下一个邻接表元素，e[i].w为边权
void SecondShortestPath()
{
    for (int i = 1; i <= n; i++)
    {
        dis[i] = INF; // 初始化S到各点的最短路径长度
    }

    dis[S] = 0;
    Dijkstra(dis); // 找出最短路径长度
    for (int u = 1; u <= n; u++)
    {
        f[u] = INF; // 初始化S到各点的次短路径长度
    }

    for (int u = 1; u <= n; u++)
    {
        for (int i = head[u]; i; i = e[i].nxt)
        {
            int v = e[i].tv;
            if (dis[u] + e[i].w < f[v] && dis[u] + e[i].w > dis[v])
            {
                f[v] = dis[u] + e[i].w;
            }
        }
    }

    Dijkstra(f); // 用次短路径的结构来操作路径搜索和更新
}

```

## Floyd-Warshall算法


Floyd-Warshall算法基于动态规划思想。此算法同时考虑了所有节点对之间的间接关系，通过三重循环实现对每一个节点对的距离的最小值的迭代更新。复杂度为$O(n^3)$，空间复杂度为$O(n^2)$。

### 应用：求解传递闭包

通过额外的位操作（例如bitset）来减少空间复杂度也是可行的，尤其是对于邻接矩阵，可以减少存储占用。

```cpp
// dis: 存储所有节点之间距离的二维数组
// n: 图的顶点数量
for (int k = 1; k <= n; k++)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (dis[i][k] + dis[k][j] < dis[i][j])
                dis[i][j] = dis[i][k] + dis[k][j];
        }
    }
}

// 可以使用Floyd-Warshall算法来得到图的传递闭包
// b: 存储节点之间可达关系的数组
// MaxN: 不小于顶点数量的一个定值
bitset<MaxN> b[MaxN];
for (int k = 1; k <= n; k++)
{
    for (int i = 1; i <= n; i++)
    {
        if (b[i][k])
            b[i] |= b[k];
    }
}
```


> [!example]+ 例题 P1850 [NOIP2016 换教室](https://www.luogu.com.cn/problem/P1850)

## 最小生成树

### Kruskal算法

稀疏图使用，时间复杂度为$\mathcal{O}(m\log m)$

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int src, dest, weight;
};

// Comparator function to sort edges based on their weight
bool compareEdge(const Edge& e1, const Edge& e2) {
    return e1.weight < e2.weight;
}

struct DisjointSet {
    vector<int> parent, rank;

    // Constructor to initialize the disjoint set
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    // Find the root of the set containing node u
    int find(int u) {
        if (u != parent[u])
            parent[u] = find(parent[u]); // Path compression
        return parent[u];
    }

    // Union by rank
    void unionSet(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU != rootV) {
            if (rank[rootU] > rank[rootV]) {
	            parent[rootV] = rootU;
	            rank[rootU] += rank[rootV];
            }  
            else {
                parent[rootU] = rootV;
                rank[rootV] += rank[rootU];
            }
        }
    }
};

vector<Edge> kruskalMST(int V, vector<Edge>& edges) {
    vector<Edge> result;
    sort(edges.begin(), edges.end(), compareEdge); // Sort all edges

    DisjointSet ds(V);

    for (auto& e : edges) {
        int u = e.src;
        int v = e.dest;
        if (ds.find(u) != ds.find(v)) {
            result.push_back(e);
            ds.unionSet(u, v);
        }
    }

    return result;
}

int main() {
    int V = 4;  // Number of vertices
    vector<Edge> edges = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    vector<Edge> mst = kruskalMST(V, edges);
    
    cout << "Edges in the MST:" << endl;
    for (auto& e : mst) {
        cout << e.src << " - " << e.dest << " : " << e.weight << endl;
    }

    return 0;
}

```
### Prim算法

稠密图使用，时间复杂度为$\mathcal{O}((n+m)\log n)$。

一般情况下都使用 Kruskal 算法，在稠密图尤其是完全图上，暴力 Prim 的复杂度比 Kruskal 优，但 不一定 实际跑得更快。

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// Structure to represent an edge in the priority queue
struct Edge {
    int to, weight;
    bool operator>(const Edge& other) const {
        return weight > other.weight;
    }
};

// Function to find MST using Prim's algorithm
void primMST(const vector<vector<Edge>>& graph) {
    int V = graph.size();
    vector<bool> inMST(V, false);
    vector<int> minWeight(V, INT_MAX);
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;

    // Start with the first vertex
    minWeight[0] = 0;
    pq.push({0, 0}); // {vertex, weight}

    int mstWeight = 0;
    cout << "Edges in the MST:" << endl;

    while (!pq.empty()) {
        // Select the edge with minimum weight
        int u = pq.top().to;
        pq.pop();

        if (inMST[u]) continue;
        inMST[u] = true;
        mstWeight += minWeight[u];

        // Process all adjacent vertices
        for (auto& e : graph[u]) {
            int v = e.to;
            int weight = e.weight;
            if (!inMST[v] && weight < minWeight[v]) {
                minWeight[v] = weight;
                pq.push({v, weight});
            }
        }
    }

    cout << "Total weight of MST: " << mstWeight << endl;
}

int main() {
    // Number of vertices
    int V = 5;

    // Adjacency list of graph
    vector<vector<Edge>> graph(V);

    // Constructing the graph
    graph[0] = {{1, 2}, {3, 6}};
    graph[1] = {{0, 2}, {2, 3}, {3, 8}, {4, 5}};
    graph[2] = {{1, 3}, {4, 7}};
    graph[3] = {{0, 6}, {1, 8}};
    graph[4] = {{1, 5}, {2, 7}};

    // Calculate MST using Prim's algorithm
    primMST(graph);

    return 0;
}
```

> [!example]+ 例题 P1967 [NOIP2013 货车运输](https://www.luogu.com.cn/problem/P1967)

## 次小生成树

### 严格次小生成树

1. 求出某个最小生成树
2. 选择图中不在最小生成树的一条边$e =(u,v)$，在T上有u到v的路径中，如果存在边权严格小于w的边，那么删去小于w的边中的最大边，将边e加入树中，得到一棵生成树$T_{i}$【*实际代码操作中，如果路径中的最大边不等于w(因为最小生成树的性质, 一定是小于)，那么用e替换最大边；如果最大值等于w，那么用e替换严格次大边*】
3. 选出每次这样更新后的最小生成树 $\min T_{i}$

> [!note]+ 
> 因为*最小生成树保证生成树中 u 到 v 路径上的边权最大值一定 不大于 其他从 u 到 v 路径的边权最大值*。换言之，当我们用于替换的边的权值与原生成树中被替换边的权值相等时，得到的次小生成树是非严格的。
> 
> 解决的办法很自然：我们维护到 2^i 级祖先路径上的最大边权的同时维护 严格次大边权，当用于替换的边的权值与原生成树中路径最大边权相等时，我们用严格次大值来替换即可。

- 使用LCA维护路径上边权最大和严格次大的边
- 如果不限定边权严格小于w，小于等于也可以，那么得到的是**非严格次小生成树**

```cpp
struct max2
{
    int fst, sec;

    max2 combine(max2 a, max2 b)
    {
        max2 ans = *this;
        if (b.fst > ans.fst)
        {
            ans.sec = ans.fst;
            ans.fst = b.fst;
            if (b.sec > ans.sec)
                ans.sec = b.sec;
        }
        else if (b.fst > ans.sec && b.fst != ans.fst)
            ans.sec = b.fst;

        return ans;
    }
};

int anc[N][18];
max2 wt[N][18];
int dep[N];

void DFS(int u)
{
    for (int i = 1; i < 17; i++)
    {
        anc[u][i] = anc[anc[u][i-1]][i-1];
        wt[u][i] = combine(wt[u][i-1], wt[anc[u][i-1]][i-1]);
    }
    for (int i = head[u]; i != e[i].nxt; i++)
    {
        if (e[i].tv != anc[u][0])
        {
            DFS(e[i].tv);
        }
    }
}

max2 query(int u, int v)
{
    if (dep[u] < dep[v])
        swap(u, v);
    for (int d = dep[u] - dep[v], i = 0; d; d >>= 1, i++)
        if (d & 1)
            r = combine(r, wt[u][i]), u = anc[u][i];
    if (u == v)
        return r;
    for (int i = 16; i >= 0; i--)
        if (anc[u][i] != anc[v][i])
        {
            r = combine(r, wt[u][i]);
            r = combine(r, wt[v][i]);
            u = anc[u][i];
            v = anc[v][i];
        }
    r = combine(r, wt[u][0]);
    r = combine(r, wt[v][0]);
    return r;
}

// 用来寻找secondMST需要使用的函数
int secondMST()
{
    int ans = INF;
    for (int i = 0; i < m; i++)
    {
        max2 x = query(g[i].u, g[i].v);
        if (g[i].w == x.fst)
            ans = min(ans, MST - x.fst + g[i].w);
        else if (x.sec != INF)
            ans = min(ans, MST - x.sec + g[i].w);
    }
    return ans;
}

```
