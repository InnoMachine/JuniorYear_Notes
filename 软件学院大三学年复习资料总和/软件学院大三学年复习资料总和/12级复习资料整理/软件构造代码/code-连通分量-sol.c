// 计算连通分量的第二钟方法
// http://codeforces.com/contest/292/problem/D

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <ctime>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <fstream>
#include <sstream>
#include <stack>
#include <list>
#include <bitset>
#include <complex>
#include <cctype>
#include <cassert>
#include <iomanip>
#include <memory>
#include <functional>
using namespace std;
#define LL long long
int m,n;
struct dsu{
    int par[505],sum;
	// par表示并查集的数组表示
	// sum为连通分量值
    void init(){
        for(int i=0;i<=n;i++)par[i]=i;
        sum=n;                                          //一开始有n个连通分量
    }
	// 初始化并查集，所有的指向自己，即没有任何边
	// 连通分量为n
    int endparent(int x){
        while(x!=par[x])x=par[x];
        return x;
    }
	// 找到当前点的集合根节点
    bool check(int a,int b){
        a=endparent(a);int c;
        c=endparent(b);
        if(a==c)return false;
		// 如果两个不在一个连通分量
		// 合并
        par[c]=a;
        sum--;
		// 连通分量减少1
        return true;
    }
	// 检查两个点是否在同一个连通分量
}a,b;
// 并查集结构体

int p1[10010],p2[10010],lp1[10010],lp2[10010],rp1[10010],rp2[10010];
int sol[505][505],l[10010],r[10010];
int main(){
    bool left[10010],right[10010]; //按顺序加入边是否有效
    #ifndef ONLINE_JUDGE
    freopen("1.in","r",stdin);
    #endif
	// 预处理
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)cin>>p1[i]>>p2[i];
	// 读取每一条边的两个顶点
    memset(left,false,sizeof(left));
    memset(right,false,sizeof(right));
	// 将left和right数组全部置为false
    
	a.init();
    for(int i=1;i<=m;i++){
        if(a.check(p1[i],p2[i]))left[i]=true;
    }
	a.init();
    for(int i=m;i>=1;i--)
        if(a.check(p1[i],p2[i]))right[i]=true;
	// 分别从左向右link边和从右向左link边
	// 如果当前边的加入能够产生合并，则记录当前left,right为true

    int s=0;
    for(int i=1;i<=m;i++){      //对于m条边
        if(left[i]){
            s++;
            lp1[s]=p1[i];
            lp2[s]=p2[i];
        }
        l[i]=s;
    }
    s=0;
    for(int i=m;i>=1;i--){  //反着对于m条边 
        if(right[i]){
            s++;
            rp1[s]=p1[i];
            rp2[s]=p2[i];
        }
        r[i]=s;
    }
	// 遍历从左向右和从右向左的两种情况
	// 一旦当前的边能够合并两个连通分量，则将该边记下来
	// 即在两个不同方向进行link时，只有lp和rp中存入的边才会对连通分量产生影响
	// s则作为数组索引而已

    b.init();
    for(int i=0;i<=n;i++){
        if(i>0)b.check(lp1[i],lp2[i]);
        a=b;
        for(int j=0;j<=n;j++){
            if(j>0)a.check(rp1[j],rp2[j]);
            sol[i][j]=a.sum;
        }
    }
	// b作为临时的并查集
	// 从左向右和从右向左依次将影响连通分量的边加入
	// 同时用sol[i][j]来记录只有左边前i边和右边前j边的图的连通分量值
	// 相当于表示删除掉i+1到j-1的所有边的图，即题目所要求的值

    int k;
    cin>>k;
    for(int i=1;i<=k;i++){   //测试数据
        int x,y;
        cin>>x>>y;
        x--;y++;
        cout<<sol[l[x]][r[y]]<<endl;
		// 由上诉算出的所有情况，可以直接由sol求出结果
    }
    return 0;
}