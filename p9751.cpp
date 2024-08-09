#include<bits/stdc++.h>
using namespace std;

int n,m,k;

struct Edge {
    int u, v, w;
    Edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}
};

priority_queue<pair<int,int>,greater<int>> Q;
vector<vector<Edge>> adj; // 邻接表，每个索引代表一个节点，向量存储边
int d[20010];

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

int main(){
    int ui,vi,ai;
    cin>>n>>m>>k;
    for (size_t i = 0; i < m; i++)
    {
        cin>>ui>>vi>>ai;
        addEdge(ui,vi,ai);
    }
    for (int u = 0; u < adj.size(); ++u) { // 遍历每一个节点
        d[u]=0x3fffffff;
    }
    for (int u = 0; u < adj.size(); ++u) { // 遍历每一个节点
        for (auto &e : adj[u])  Q.push(make_pair(d[e.v],e.v));
    }
}
