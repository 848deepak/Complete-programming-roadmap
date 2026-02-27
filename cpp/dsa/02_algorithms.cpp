// ============================================================
// MODULE 11 | DSA → Sorting, DP, Greedy (C++)
// Compile: g++ -std=c++17 02_algorithms.cpp -o out && ./out
// ============================================================
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <climits>
using namespace std;

// ============================================================
// SORTING
// ============================================================
void bubbleSort(vector<int>& a){
    int n=a.size(); bool sw;
    for(int i=0;i<n-1;i++){sw=false;for(int j=0;j<n-i-1;j++) if(a[j]>a[j+1]){swap(a[j],a[j+1]);sw=true;} if(!sw)break;}
}

void merge(vector<int>& a,int l,int m,int r){
    vector<int>L(a.begin()+l,a.begin()+m+1),R(a.begin()+m+1,a.begin()+r+1);
    int i=0,j=0,k=l;
    while(i<(int)L.size()&&j<(int)R.size()) a[k++]=L[i]<=R[j]?L[i++]:R[j++];
    while(i<(int)L.size())a[k++]=L[i++];while(j<(int)R.size())a[k++]=R[j++];
}
void mergeSort(vector<int>& a,int l,int r){if(l>=r)return;int m=l+(r-l)/2;mergeSort(a,l,m);mergeSort(a,m+1,r);merge(a,l,m,r);}

int part(vector<int>& a,int lo,int hi){int piv=a[hi],i=lo-1;for(int j=lo;j<hi;j++)if(a[j]<=piv)swap(a[++i],a[j]);swap(a[i+1],a[hi]);return i+1;}
void quickSort(vector<int>& a,int lo,int hi){if(lo>=hi)return;int p=part(a,lo,hi);quickSort(a,lo,p-1);quickSort(a,p+1,hi);}

// ============================================================
// DYNAMIC PROGRAMMING
// ============================================================
// LCS:
int lcs(const string& s1, const string& s2){
    int m=s1.size(),n=s2.size();
    vector<vector<int>>dp(m+1,vector<int>(n+1,0));
    for(int i=1;i<=m;i++) for(int j=1;j<=n;j++)
        dp[i][j]=s1[i-1]==s2[j-1]?dp[i-1][j-1]+1:max(dp[i-1][j],dp[i][j-1]);
    return dp[m][n];
}

// 0/1 Knapsack:
int knapsack(vector<int>& w,vector<int>& v,int W){
    int n=w.size();
    vector<vector<int>>dp(n+1,vector<int>(W+1,0));
    for(int i=1;i<=n;i++) for(int c=0;c<=W;c++){
        dp[i][c]=dp[i-1][c];
        if(w[i-1]<=c) dp[i][c]=max(dp[i][c],dp[i-1][c-w[i-1]]+v[i-1]);
    }
    return dp[n][W];
}

// Coin Change (min coins):
int coinChange(vector<int>& coins,int amt){
    vector<int>dp(amt+1,INT_MAX);dp[0]=0;
    for(int i=1;i<=amt;i++) for(int c:coins)
        if(c<=i&&dp[i-c]!=INT_MAX) dp[i]=min(dp[i],dp[i-c]+1);
    return dp[amt]==INT_MAX?-1:dp[amt];
}

// Kadane's max subarray:
int kadane(vector<int>& a){int mx=a[0],curr=a[0];for(int i=1;i<(int)a.size();i++){curr=max(a[i],curr+a[i]);mx=max(mx,curr);}return mx;}

// ============================================================
// GREEDY
// ============================================================
int activitySelection(vector<pair<int,int>>& acts){
    sort(acts.begin(),acts.end(),[](auto&a,auto&b){return a.second<b.second;});
    int cnt=1,last=acts[0].second;
    for(int i=1;i<(int)acts.size();i++) if(acts[i].first>=last){cnt++;last=acts[i].second;}
    return cnt;
}

int main() {
    auto printV=[](vector<int>&v,const char*lbl){cout<<lbl;for(int x:v)cout<<x<<" ";cout<<"\n";};
    vector<int> a={64,34,25,12,22,11,90};

    cout << "=== SORTING ===" << endl;
    vector<int>b=a; bubbleSort(b);         printV(b,"Bubble:    ");
    vector<int>ms=a;mergeSort(ms,0,ms.size()-1);printV(ms,"Merge:     ");
    vector<int>qs=a;quickSort(qs,0,qs.size()-1);printV(qs,"Quick:     ");
    vector<int>st=a;sort(st.begin(),st.end());  printV(st,"std::sort: ");

    cout << "\n=== DYNAMIC PROGRAMMING ===" << endl;
    cout << "LCS(ABCBDAB,BDCAB)=" << lcs("ABCBDAB","BDCAB") << endl;  // 4
    vector<int>w={1,3,4,5},v={1,4,5,7};
    cout << "Knapsack(W=7)=" << knapsack(w,v,7) << endl;   // 9
    vector<int>coins={1,5,6,9};
    cout << "CoinChange(11)=" << coinChange(coins,11) << endl;   // 2
    vector<int>ka={-2,1,-3,4,-1,2,1,-5,4};
    cout << "Kadane(max subarray)=" << kadane(ka) << endl;   // 6

    cout << "\n=== BINARY SEARCH ===" << endl;
    vector<int>sorted={1,3,5,7,9,11,13};
    cout << "contains 7: " << binary_search(sorted.begin(),sorted.end(),7) << endl;

    cout << "\n=== GREEDY: ACTIVITY SELECTION ===" << endl;
    vector<pair<int,int>>acts={{1,3},{2,5},{4,6},{6,7},{5,8},{8,9}};
    cout << "Max activities=" << activitySelection(acts) << endl;   // 4

    return 0;
}
