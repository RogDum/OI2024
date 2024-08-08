#include<vector>
#include<iostream>
using namespace std;

int main(){
    vector<int> a;
    a.reserve(5);
    a[3]=2;
    for (size_t i = 0; i < 5; i++)
    {
        cout<<a[i]<<" ";
    }
    
}
