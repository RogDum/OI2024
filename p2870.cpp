#include <bits/stdc++.h>
using namespace std;

int n, P=19250825, p=131;
long long pl[10010];
vector<unsigned> ins, ha1, ha2;
unsigned uha=0, ha = 0;
char ans[500010];
char temp;
int top;

int lef, rig;//left, right
inline int che(int len) {//hash基本操作：比较两端是否相同 
	long long l = ((ha1[lef + len - 1] - ha1[lef - 1] * pl[len]) % P + P) % P;
	long long r = ((ha2[rig - len + 1] - ha2[rig + 1] * pl[len]) % P + P) % P;
	return l == r;
}

inline int halffind() {
	int l = 1, r = (rig - lef + 1) >> 1;
	int mid, res = 1;
	while (l <= r) {
		mid = (l + r) >> 1;
		if (che(mid)) {
			res = mid;
			l = mid + 1;
		} else {
			r = mid - 1;
		}
	}
	return res;
}

int main(){

    cin>>n;

    ins.insert(ins.end(), 0);
    ins.insert(ha1.end(), 0);
    ins.insert(ha2.end(), 0);

    while (cin>>temp)
    {
        ins.insert(ins.end(), temp);
    }

    pl[0]=1;

    for (int i = 1; i < 10010; i++)
    {
        pl[i]= (pl[i-1]%P * p%P)%P;
    }
    
    int cont=0;
    for (auto i = ins.begin()+1; i <= ins.end(); i++)
    {
        ha = (*i%P * (pl[cont])%P + ha%P) % P;
        ha1.insert(ha1.end(), ha);
        cont++;
    }
    cont=0;
    for (auto i = ins.end()-1; i >= ins.begin()+1; i--)
    {
        uha = (*i%P * (pl[cont])%P + uha%P) % P;
        ha2.insert(ha2.end(), uha);
        cont++;
    }

    //cout<<ha1.size()<<"\n";

    //for(auto& i : ha1){cout<<i<<"\n";}
    
    lef = 1, rig = n;int len;

    for (int i = 1; i < n; ++i) {
		if (ins[lef] < ins[rig]) {
			ans[++top] = ins[lef++];
		} else if (ins[rig] < ins[lef]) {
			ans[++top] = ins[rig--];
		} else {
			len = halffind();
			ans[++top] = ins[lef + len] < ins[rig - len] ? ins[lef++] : ins[rig--];
		}
	}

    ans[n] = ins[lef];

    for (int i = 1; i <= n; ++i) {
		cout<<ans[i];
		if (i % 80 == 0)	cont<<'\n';
	}
	return 0;

}
