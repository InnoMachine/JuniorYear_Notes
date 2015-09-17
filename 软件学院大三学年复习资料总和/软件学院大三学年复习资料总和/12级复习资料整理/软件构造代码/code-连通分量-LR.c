/**
	对于输入的m和n
	有m条边，n个顶点
	输入的Q表示有多少组数据
	构建图之后删除第l到r边
	求出剩余图的连通分量
	http://codeforces.com/contest/292/problem/D
*/

#include<cstdio>
#include<cstring>
#define N 10005
int n,m,Q,l,r,x[N],y[N];
struct DSU{
	int f[505],c;
	// f为并查集的数组表示，即f[x]表示当前x所对应的并查集树的父节点
	// c记录当前link进行的次数，即连通了多少次，顶点数减去c即表示连通分量的值
	int get(int x){return f[x]?f[x]=get(f[x]):x;}
	// 如果get(f[x])=0即该节点已经为根节点，则到了并查集的根
	void Link(int x,int y){x=get(x),y=get(y); if (x!=y) f[x]=y,c++;}
	// 找到两个点的根，连在一起则合并
	// 如果两个点同源，就不认为进行合并了
}L[N],R[N],ans;
// 并查集结构的定义

int main()
{
	scanf("%d%d",&n,&m);
	// 读入顶点数，边数
	for (int i=1;i<=m;i++) scanf("%d%d",x+i,y+i),L[i]=L[i-1],L[i].Link(x[i],y[i]);
	// 从左向右读取所有的边，并且把新加入的边和之前的图连接起来
	// 存储在L里面
	// L[i]表示的是从左向右加入边时，加入i条边时的图
	// 其中x,y数组对应存储一条边的两端顶点
	for (int i=m;i;i--) R[i]=R[i+1],R[i].Link(x[i],y[i]);
	// 从右向左把边依次加入图中
	// 存储在R里面
	// R[i]同上
	scanf("%d",&Q);
	
	while (Q--){
		// 处理每组数据
		scanf("%d%d",&l,&r); DSU ans=L[l-1];
		// 读取删除的边的左边界l和右边界r
		// ans代表已经删掉l之后所有边的图
		
		/*对R的n个节点进行遍历*/
		for (int i=1;i<=n;i++) if (R[r+1].f[i]) ans.Link(i,R[r+1].f[i]);
		
		// R[r+1]，就是r边之后的图，最终的图就是L[l-1]和R[r+1]组成
		// 这里遍历所有的顶点，一旦找到R[r+1]的f[i]不为0，即当前找到一个可连通的点
		// 将该可以连通的边加入到ans中，直到全部加入
		printf("%d\n",n-ans.c);
		// 最终的ans中含有1到l,r之后的所有边的图，顶点数n-ans.c则为连通分量
		}
	return 0;
}