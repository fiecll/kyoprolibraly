#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
using ll = long long;
using Graph = vector<vector<int>>;
using P = pair<int,int>;
vector<bool>seen;
void dfs(const G &G,int v){
    seen[v] = true;
    for(auto next_v:G[v]){
        if(seen[next_v]){
            continue;
        }
        dfs(G,next_v);
    }
}
int main(){ 
   int n,m;
   cin >> n >> m;
   Graph G(n);
   for(int i=0;i<m;i++){
    int a,b;
    cin >> a >> b;
    G[a].push_back(b);
    G[b].push_back(a);
   }
   
   int count =0;
   seen.assign(N,false);
   for(int v=0;v<n;v++){
    if(seen[v]){
        continue;
        dfs(G,v);
        count++;
    }
   }
   cout << count << endl;
}