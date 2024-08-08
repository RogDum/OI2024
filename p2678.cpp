#include<iostream>
#include<string>
#include<vector>
using namespace std;

int tmp;
int l,m,n,cnt=0,ans;
vector<int> stl;

bool j(int d){
    vector<int> st=stl;
    bool r=true;
    cnt=0;
    for(auto&i:st){
        //cout<<"j "<<i<<endl;
    }
    for (size_t i = 1; i <= n+1; i++)
    {
        if (st[i]-st[i-1]<d)
        {
            cnt++;
            st[i]=st[i-1];
            //cout<<"i"<<i<<"st[i]"<<st[i]<<"st[i-1]"<<st[i-1]<<"小了\n";
        }    
        /*if (i==n+1&&st[i]-st[i-1]<d)
        {
            //cout<<"出界了\n";
            return false;
        }   */
    }
    if (cnt>m)
    {
        cnt=0;
        //cout<<"太多了\n";
        return false;
    }
    else{
        cnt=0;
        return true;
    }
}

int main(){
    cin>>l>>n>>m;
    stl.push_back(0); 
    while(cin>>tmp){
        stl.push_back(tmp); 
    }
    stl.push_back(l);
    for(auto&i:stl){
        //cout<<i<<endl;
    }
    int lb=0,rb=l,mid;
            mid=(lb+rb)/2;
    while (lb<=rb)
    {

        //cout<<mid<<" ";
        if (j(mid)){//带入judge函数判断当前解是不是可行解
            ans = mid;
            lb = mid + 1;//cout<<"走到这里，看来是可行解，我们尝试看看是不是有更好的可行解\n";
        }
        else
            rb = mid - 1;//cout<<"//噫，你找了个非法解，赶紧回到左半边看看有没有可行解\n";
        mid=(lb+rb)/2;
    } 
    if (j(ans+1))
    {
        cout<<"!";ans++;
    }
    
    cout<<ans;
}
