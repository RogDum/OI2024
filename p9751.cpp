#include<bits/stdc++.h>
using namespace std;

int n,m,k;

struct Edge {
    int u, v, w, a;
    Edge(int _u, int _v, int _w, int _a) : u(_u), v(_v), w(_w), a(_a) {}
};

priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> Q,R;
vector<vector<Edge>> adj; // 邻接表，每个索引代表一个节点，向量存储边
int d[20010][],p[20010],a[20010];

void addEdge(int u, int v, int w, int a){
    if(u+1>=adj.size()||v+1>=adj.size()){
        adj.resize(max(u,v)+1);
    }
    adj[u].push_back(Edge(u,v,w,a));
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

void relax(Edge& e, int k){
    int t = 1;
    if(d[e.u][k] < e.a) {
        t += (e.a - d[e.u][k]) / k;
    }
    if(d[e.v][(k+t)%K] > d[e.u][k] + t){
            d[e.v][(k+t)%] = d[e.u][k] + t;
            p[e.v]=e.u;
            cout<<"rx"<<e.u<<" "<<e.v<<" "<<e.w<<"\n";
    }
}

int main(){
    int ui,vi,ai;
    cin>>n>>m>>k;
    for (size_t i = 1; i <= m; i++)
    {
        cin>>ui>>vi>>ai;
        addEdge(ui,vi,1,ai);
    }
    for (int u = 1; u <= m; ++u) { // 遍历每一个节点
        d[u]=0x3fffffff;
    }
    d[1]=0;
    for (int u = 1; u <= adj.size(); ++u) { // 遍历每一个节点
        Q.push(Node(d[u][k],u,k));  // d在d mod K == k时的最小值
    }
    R=Q;
    
    while (!Q.empty())
    {
        int tp = Q.top().second;//cout<<"tp:"<<tp<<"\n";
        int k = Q.top().k;

        Q.pop();

        for(auto& e : adj[tp]){
            cout<<"rx"<<e.u<<" "<<e.v<<" "<<e.w<<"\n";
            relax(e, k);
            Q.push(make_pair(d[e.v], e.v));
        }
    }

    cout<<d[n][0];
}
