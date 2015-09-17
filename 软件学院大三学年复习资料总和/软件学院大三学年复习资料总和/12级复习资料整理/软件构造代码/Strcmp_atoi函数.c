
// Strcmp�������Ƚ������ַ������Ƿ���ͬ

int strcmp(const char *dest, const char *source)
{
   assert((NULL != dest) && (NULL != source));
   while (*dest && *source && (*dest == *source))
           {
                    dest ++;
                   source ++;
           }
   return *dest - *source;
   // �����ֲ�һ�������ص�ǰָ����ָ����ĸ���ֵ�˳��
   //���dest > source,�򷵻�ֵ����0�����dest = source,�򷵻�ֵ����0�����dest  < source ,�򷵻�ֵС��0
}




// atoi�ַ���ת��������
// ���ϵĸ���ʵ��
#include <iostream>
#include <assert.h>
using namespace std;
int atoi_mf(char s[])
{
	assert(s != NULL);
	int i = 0;
	int sum = 0;
	int sign;
	//�����ո���Ʊ��
	while(' ' == s[i] || '\t' == s[i])
	{
		i++;
	}
	//��������ķ���
	sign = ('-'==s[i] ? -1:1);
	//��������
	if('-' == s[i] || '+' == s[i])
	{
		i++;
	}
	//
	while(s[i] != '\0')
	{
		if(s[i] >= '0' && s[i] <= '9')
		{
			sum = s[i]-'0'+sum*10;
		}
		else
		{
			break;
		}
		i++;
	}
	return sign*sum;
}

void main()
{
	char *str = "-12dd34";
	cout << atoi_mf(str) <<endl;
}