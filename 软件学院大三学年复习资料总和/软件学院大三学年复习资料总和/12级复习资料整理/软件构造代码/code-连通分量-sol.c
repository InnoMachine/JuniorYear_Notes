// ������ͨ�����ĵڶ��ӷ���
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
	// par��ʾ���鼯�������ʾ
	// sumΪ��ͨ����ֵ
    void init(){
        for(int i=0;i<=n;i++)par[i]=i;
        sum=n;                                          //һ��ʼ��n����ͨ����
    }
	// ��ʼ�����鼯�����е�ָ���Լ�����û���κα�
	// ��ͨ����Ϊn
    int endparent(int x){
        while(x!=par[x])x=par[x];
        return x;
    }
	// �ҵ���ǰ��ļ��ϸ��ڵ�
    bool check(int a,int b){
        a=endparent(a);int c;
        c=endparent(b);
        if(a==c)return false;
		// �����������һ����ͨ����
		// �ϲ�
        par[c]=a;
        sum--;
		// ��ͨ��������1
        return true;
    }
	// ����������Ƿ���ͬһ����ͨ����
}a,b;
// ���鼯�ṹ��

int p1[10010],p2[10010],lp1[10010],lp2[10010],rp1[10010],rp2[10010];
int sol[505][505],l[10010],r[10010];
int main(){
    bool left[10010],right[10010]; //��˳�������Ƿ���Ч
    #ifndef ONLINE_JUDGE
    freopen("1.in","r",stdin);
    #endif
	// Ԥ����
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)cin>>p1[i]>>p2[i];
	// ��ȡÿһ���ߵ���������
    memset(left,false,sizeof(left));
    memset(right,false,sizeof(right));
	// ��left��right����ȫ����Ϊfalse
    
	a.init();
    for(int i=1;i<=m;i++){
        if(a.check(p1[i],p2[i]))left[i]=true;
    }
	a.init();
    for(int i=m;i>=1;i--)
        if(a.check(p1[i],p2[i]))right[i]=true;
	// �ֱ��������link�ߺʹ�������link��
	// �����ǰ�ߵļ����ܹ������ϲ������¼��ǰleft,rightΪtrue

    int s=0;
    for(int i=1;i<=m;i++){      //����m����
        if(left[i]){
            s++;
            lp1[s]=p1[i];
            lp2[s]=p2[i];
        }
        l[i]=s;
    }
    s=0;
    for(int i=m;i>=1;i--){  //���Ŷ���m���� 
        if(right[i]){
            s++;
            rp1[s]=p1[i];
            rp2[s]=p2[i];
        }
        r[i]=s;
    }
	// �����������Һʹ���������������
	// һ����ǰ�ı��ܹ��ϲ�������ͨ�������򽫸ñ߼�����
	// ����������ͬ�������linkʱ��ֻ��lp��rp�д���ı߲Ż����ͨ��������Ӱ��
	// s����Ϊ������������

    b.init();
    for(int i=0;i<=n;i++){
        if(i>0)b.check(lp1[i],lp2[i]);
        a=b;
        for(int j=0;j<=n;j++){
            if(j>0)a.check(rp1[j],rp2[j]);
            sol[i][j]=a.sum;
        }
    }
	// b��Ϊ��ʱ�Ĳ��鼯
	// �������Һʹ����������ν�Ӱ����ͨ�����ı߼���
	// ͬʱ��sol[i][j]����¼ֻ�����ǰi�ߺ��ұ�ǰj�ߵ�ͼ����ͨ����ֵ
	// �൱�ڱ�ʾɾ����i+1��j-1�����бߵ�ͼ������Ŀ��Ҫ���ֵ

    int k;
    cin>>k;
    for(int i=1;i<=k;i++){   //��������
        int x,y;
        cin>>x>>y;
        x--;y++;
        cout<<sol[l[x]][r[y]]<<endl;
		// ������������������������ֱ����sol������
    }
    return 0;
}