/* 初始化mini2440目标板 
1. 设定系统运行时钟频率
2. 端口初始化
3. MMU初始化
4. 串口初始化
5. LED指示灯初始化
*/
#include "config.h"

extern void Lcd_N35_Init(void);

void TargetInit(void)
{
    int i;
	U8 key;
	U32 mpll_val=0;
    #if ADS10   
    __rt_lib_init(0,0); //for ADS 1.0
 
    #endif
    
	i = 2 ;	//use 400M!
		
	switch ( i ) {
	case 0:	//200
		key = 12;
		mpll_val = (92<<12)|(4<<4)|(1);
		break;
	case 1:	//300
		key = 14;
		mpll_val = (67<<12)|(1<<4)|(1);
		break;
	case 2:	//400
		key = 14;
		mpll_val = (92<<12)|(1<<4)|(1);
		break;
	case 3:	//440!!!
		key = 14;
		mpll_val = (102<<12)|(1<<4)|(1);
		break;
	default:
		key = 14;
		mpll_val = (92<<12)|(1<<4)|(1);
		break;
	}
	
	//init FCLK=400M, so change MPLL first
	ChangeMPllValue((mpll_val>>12)&0xff, (mpll_val>>4)&0x3f, mpll_val&3);
	ChangeClockDivider(key, 12);    

    //MMU_EnableICache();
    //MMU_EnableDCache();
    
    MMU_DisableICache();
    MMU_DisableDCache();
  	Port_Init();
    MMU_Init();

    Delay(0);
    Uart_Init(0,115200);
    Uart_Select(0);
    Uart_SendString("hello,FriendlyARM\n");
    /*若使用printf语句，将使目标代码增加很多*/
    // Uart_Printf("hello,qq2440, printf\n");

    
   rGPBCON = 0x00555555;
   rGPBDAT = 0x0000;
//   rGPBDAT = 0x07ff;
 //  Delay(0);
 	
 }