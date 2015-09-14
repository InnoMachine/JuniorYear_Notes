// ��������
// ���ŵĻ���˼�����ѡȡ������һ��ֵ��Ϊ��׼
// Ȼ��Ӷ��е���ͷ���ϵ����м�������ȱ�׼С������ߣ��ȱ�׼�󻻵��ұ�
// �ֳ������µĶ��У��ݹ����

void swap(int a[],int left,int right)
 {
  int temp;
  temp=a[left];
  a[left]=a[right];
  a[right]=temp;
 }
//�������������

void quicksort(int a[],int left,int right)
 {
  if(left>=right) return;	// �����Ѿ�û�г����ˣ��������
  int pivot=(left+right)/2;  //��׼��Ϊ�м��Ǹ���
  swap(a,pivot,right);       //����׼��ŵ��������
  pivot=partition(a,left,right);//ͬʱ��ʼ���м��ߣ�����������
  quicksort(a,left,pivot-1);  //�ݹ�
  quicksort(a,pivot+1,right); //�ݹ�
 }


int partition(int a[],int left,int right)
 {
 int i=left;
 int j=right;
 int temp=a[j];
 //ѡ��õı�׼��
 while(i!=j)   //��������ѭ��
 {
   while((a[i]<=temp)&&(i<j)) i++;  
   // �ȱ�����ߣ����û�б�temp��ģ������Ѱ��
   if(i<j)
   {
   a[j]=a[i];
   j--;
   }
   // �����ұ�ȥ���ұ�ָ������һλ
   while(a[j]>=temp && i<j) j--; 
   // �����ұߣ����û�б�tempС�ļ���Ѱ��
   if(i<j)
   {
   a[i]=a[j];
   i++;
   }
   // ͬ��
 }
 a[i]=temp;    //����׼����뵽�����λ�ã����ֳ�������������
 return i; 
 }