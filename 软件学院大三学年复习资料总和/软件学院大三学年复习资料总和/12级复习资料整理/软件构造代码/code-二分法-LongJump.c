// 已知n,l,x,y
// 分别表示一个尺的总刻度数，尺的长度，需要测量的值x,y
// 下面一组输入是n个刻度值，保证第一个为0，最后一个为l
// 需要计算出有没有满足x，y长度的刻度差，如果有则输出需要增加的刻度为0
// 若是有一个没有，则输出最少需要加入的刻度数（多种情况选择一种）
// http://codeforces.com/problemset/problem/479/D

#include <cstdio>  
#include <cstring>  
#include <algorithm>  
#include <vector>  
using namespace std;  
int a[100010];     
//存储所有刻度的数组
int n;  
  
 /*二分法查找对应的差开距离是都一样*/
bool find(int x)  
{  
    int l = 0, r = n-1;    //二分法
    while(l <= r)  
    {  
        int m = (l+r) >> 1;  // 取一半
        if(a[m] == x)        // 如果找到一个和该值相同的情况，则输出找到该值
            return true;   
        if(a[m] < x)	// 如果a[m]比x小，则左指针移到m右边，即比m大的值继续搜索
            l = m+1;  
        else   // 否则搜索左边
            r = m-1;  
    }  
    return false;  
}



// 查找当前的刻度值中是否有x这个刻度

int ok(int x)   
{  
    for(int i = 0; i < n; i++)  
    {  
        if(a[i] >= x) //对于每个比x大的刻度，计算他和x的差是否在刻度尺上，如果在就可以找到已有刻度差满足x
        {  
            if(find(a[i]-x))  
                return i;  
        }  
    }  
    return -1;  
} 
// 确定当前刻度尺有没有刻度值差满足x，并返回满足的刻度位置

int main()  
{  
    int l, x, y;  
    while(scanf("%d %d %d %d", &n, &l, &x, &y) != EOF)     //输入四个数字
    {  
        int f1 = -1, f2 = -1;  
        for(int i = 0; i < n; i++) //输入n个刻度
        {  
            scanf("%d", &a[i]);    //注意输入的方式..
        }
		
        f1 = ok(x);  
        f2 = ok(y);  	
		// 判断当前需要的刻度差x,y是否已经存在于刻度尺中
		
        if(f1 != -1 && f2 != -1)  
        {  
            printf("0\n");  
            continue;  
        } 
		// 都存在输出0

		// 如果刻度1存在刻度2不存在
        if(f1 != -1 && f2 == -1)  
        {  
            printf("1\n");  
            printf("%d\n", y);  
        }  
		// 如果刻度2存在刻度1不存在
        else if(f1 == -1 && f2 != -1)  
        {  
            printf("1\n");  
            printf("%d\n", x);  
        }  
        else  
        {
			// 两个都不存在就需要判断是否可以只需要一个刻度值来同时x,y
            int tmp1 = -1, tmp2 = -1;  
			
            for(int i = 0; i < n; i++)
            {  
                int s = a[i]-x;
                int e = a[i]+x;
				// 对于x而言可能存在的满足情况

				// 如果s也能满足y
                if(s >= 0 && s <= l && find(s+y))  //上界
                {     
                    tmp1 = i;  
                    break;  
                }  
                if(s >= 0 && s <= l && find(s-y))  //下界
                {     
                    tmp1 = i;  
                    break;  
                }  
				// 如果e也能满足y
                if(e >= 0 && e <= l && find(e+y))  
                {     
                    tmp2 = i;  
                    break;  
                }  
                if(e >= 0 && e <= l && find(e-y))  
                {     
                    tmp2 = i;  
                    break;  
                }
				// 其中e,s首先要存在于刻度尺的正常尺度范围内
            }  
			
			// e,s中有一个同时满足x,y
            if(tmp1 != -1)  
            {  
                printf("1\n%d\n", a[tmp1]-x);  
            }  
            else if(tmp2 != -1)  
            {  
                printf("1\n%d\n", a[tmp2]+x);  
            }  
			// e,s不能都满足
            else  
            {  
                printf("2\n");  
                printf("%d %d\n", x, y);  
            }  
        }  
    }  
    return 0;  
}  