// 快速排序
// 快排的基本思想就是选取队列中一个值作为标准
// 然后从队列的两头不断地向中间遍历，比标准小换到左边，比标准大换到右边
// 分成两个新的队列，递归快排

void swap(int a[],int left,int right)
 {
  int temp;
  temp=a[left];
  a[left]=a[right];
  a[right]=temp;
 }
//交换数组的数据

void quicksort(int a[],int left,int right)
 {
  if(left>=right) return;	// 队列已经没有长度了，排序完成
  int pivot=(left+right)/2;  //标准球为中间那个；
  swap(a,pivot,right);       //将标准球放到队伍最后
  pivot=partition(a,left,right);//同时开始往中间走，往两边扔球；
  quicksort(a,left,pivot-1);  //递归
  quicksort(a,pivot+1,right); //递归
 }


int partition(int a[],int left,int right)
 {
 int i=left;
 int j=right;
 int temp=a[j];
 //选择好的标准球
 while(i!=j)   //外面最大的循环
 {
   while((a[i]<=temp)&&(i<j)) i++;  
   // 先遍历左边，如果没有比temp大的，则继续寻找
   if(i<j)
   {
   a[j]=a[i];
   j--;
   }
   // 换到右边去，右边指针左移一位
   while(a[j]>=temp && i<j) j--; 
   // 遍历右边，如果没有比temp小的继续寻找
   if(i<j)
   {
   a[i]=a[j];
   i++;
   }
   // 同上
 }
 a[i]=temp;    //将标准球插入到碰面的位置，划分出两个队列来；
 return i; 
 }