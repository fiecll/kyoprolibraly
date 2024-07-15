#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
using ll = long long;
using Graph = vector<vector<int>>;
using P = pair<int,int>;
int n,x,a[100009];
int search(int x){
    int l=1,r=n;
    while(l<=r){
    int m = (l+r)/2;
    if(x<a[m]) r=m-1;
    if(x == a[m])return m;
    if(x>a[m])l=m+1;
    }
    return -1;
}

int main(){ 
    cin >> n >> x;
    for(int i=1;i<=n;i++) cin >> a[i];
    //sort(a+l,a+r)でa[l]からa[r-1]までソート//
    sort(a+1,a+n+1);
    int ans = search(x);
    cout << ans << endl;

}