#include<iostream>
#include<string>
#include<vector>
using namespace std;

vector<string> ins;
string tmp;
int i;

int main(){
    while(cin>>tmp){
        ins.insert(ins.end(), tmp);
    }
    
}