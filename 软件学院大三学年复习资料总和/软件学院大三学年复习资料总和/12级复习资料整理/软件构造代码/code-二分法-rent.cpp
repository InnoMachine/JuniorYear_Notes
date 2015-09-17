// 学生租车问题
// 自行车出租地方提供m辆车，每辆车的价格分别记录在p数组中
// 有n个学生，每个人私有的钱记录在b数组中
// 公共的钱为a
// 私有的钱只能用来自己买车，不能分给其他人
// 现在要求出最多能有多少学生租到车，且学生要垫出多少钱才能满足
// http://codeforces.com/problemset/problem/363/D

#include <cstdio>  
#include <iostream>  
#include <cstring>  
#include <cmath>  
#include <algorithm>  
using namespace std;  
#define maxn 100010  
long long b[maxn],p[maxn],share;  
int main()  
{  
    int n,m;  
    long long share;  
    cin>>n>>m>>share;
	// 输入人数 车子数 还有最大共享金额数

	// 输入每个人拥有的钱数，以及辆车需要的费用
    for(int i=1;i<=n;i++)  
        cin>>b[i];  
    for(int i=1;i<=m;i++)  
        cin>>p[i];  
	// 将p和b进行排序
    sort(p+1,p+m+1);  
    sort(b+1,b+n+1);  
	
    long long l=0,r=min(n+1,m+1),mid,ans=0;  
    int cas=100;  
	/*二分法*/
    while(l<r && cas--)  
    {  
        mid=(l+r)/2;
		// 二分
		// 二分思想是不管怎么选择，都是尽量租最便宜的车
		// 就是不断的找最有钱的学生来选择当前最贵的车
		// 然后计算当前的公共钱是否能够支付1-mid这些车所差的钱
		// 如果行则左值变成mid，对更多的车进行尝试
		// 若是不能满足，则右值变为mid，缩小租车的范围
        bool ok=1;  
        long long res=0;  
        for(int i=1;i<=mid;i++)  
        {   
            if(b[n+1-i]<p[mid+1-i])  
            {  
                res+=p[mid+1-i]-b[n+1-i];  
            }  
			// 累计计算当前最有钱学生和当前最贵车的差值
        }  
        if(res<=share)	// 公有钱足以支付差价
        {  
            l=mid;  
            ans=mid;	// 若能支付则当前能租到最多的车就是ans辆
        }  
        else  
        {  
            r=mid;  
        }  
    }  
    cout<<ans;    //输出要租车的数目
    long long miao=0;  
    for(int i=1;i<=ans;i++)  
    {  
        if(b[n+1-i]<=p[ans+1-i])     //
        {  
            miao+=b[n+1-i];  
            share-=p[ans+1-i]-b[n+1-i];  
        }  
        else  
            miao+=p[ans+1-i];  
    }  
	// 计算贴补的差价和直接购买的钱
    cout<<" "<<max(0LL,miao-share)<<endl;  
    return 0;  
}  