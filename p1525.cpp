#include<vector>
#include<iostream>
using namespace std;

struct edge
{
    int u,v,w;
    edge* head;
};

const int N = 10000;
int m,n;
int u[N],v[N],w[N],first[N],nxt[N];
vector<vector<int>> adj;
bool vis[N];

int dfs(int i){
    if(vis[i]||first[i]==-1) return;
    vis[i]=true;
    dfs(i);
    dfs(v[first[i]]);
    dfs(v[nxt[first[i]]]);
}

int main(){
    for (size_t i = 1; i < N; i++) {first[i]=-1;vis[N]=false;}
    for (int i = 1; i <= m; ++i) {
    int u1, v1, w1;
    cin >> u1 >> v1 >> w1;
    u[i]=u1;
    v[i]=v1;
    w[i]=w1;
    nxt[i]=first[u1];
    first[u1]=i;//编号i的边起始点是u1
    }

}
