
// Strcmp函数，比较两个字符数组是否相同

int strcmp(const char *dest, const char *source)
{
   assert((NULL != dest) && (NULL != source));
   while (*dest && *source && (*dest == *source))
           {
                    dest ++;
                   source ++;
           }
   return *dest - *source;
   // 若出现不一样，返回当前指针所指的字母的字典顺序
   //如果dest > source,则返回值大于0，如果dest = source,则返回值等于0，如果dest  < source ,则返回值小于0
}




// atoi字符串转换成整数
// 网上的个人实现
#include <iostream>
#include <assert.h>
using namespace std;
int atoi_mf(char s[])
{
	assert(s != NULL);
	int i = 0;
	int sum = 0;
	int sign;
	//跳过空格和制表符
	while(' ' == s[i] || '\t' == s[i])
	{
		i++;
	}
	//检测整数的符号
	sign = ('-'==s[i] ? -1:1);
	//跳过符号
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