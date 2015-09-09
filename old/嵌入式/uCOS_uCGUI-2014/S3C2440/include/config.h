/****************************************Copyright (c)**************************************************
**                               Guangzhou ZHIYUAN electronics Co.,LTD.
**                                     
**                                 http://www.zyinside.com
**
**--------------File Info-------------------------------------------------------------------------------
** File Name:          config.h
** Last modified Date: 2006-01-06
** Last Version:       v2.0
** Descriptions:       用户配置头文件
**
**------------------------------------------------------------------------------------------------------
** Created By:         黄绍斌
** Created date:       2005-12-31 
** Version:            v1.0
** Descriptions:       创建
**
**------------------------------------------------------------------------------------------------------
** Modified by:        甘达
** Modified date:      2006-01-06 
** Version:            v2.0
** Descriptions:       修改用于S3C2410
**
**------------------------------------------------------------------------------------------------------
** Modified by:         
** Modified date:      
** Version:            
** Descriptions:        
**
********************************************************************************************************/

#ifndef  CONFIG_H
#define  CONFIG_H

//这一段无需改动
#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL  		0
#endif

typedef unsigned char  uint8;                   // 无符号8位整型变量
typedef signed   char  int8;                    // 有符号8位整型变量
typedef unsigned short uint16;                  // 无符号16位整型变量
typedef signed   short int16;                   // 有符号16位整型变量
typedef unsigned int   uint32;                  // 无符号32位整型变量
typedef signed   int   int32;                   // 有符号32位整型变量
typedef float          fp32;                    // 单精度浮点数(32位长度)
typedef double         fp64;                    // 双精度浮点数(64位长度)


/********************************/
/*      uC/OS-II的特殊代码      */
/********************************/
#define     USER_USING_MODE    0x10             // 用户模式,ARM代码
                                                // 只能是0x10,0x30,0x1f,0x3f之一
//#include   "INCLUDES.H"  

#include "ucos_ii.h"                                      
          
                                           
/********************************/
/*        ARM的特殊代码         */
/********************************/
// 这一段无需改动
#include    "2440addr.h"
#include    <stdio.h>
#include    <ctype.h>
#include    <stdlib.h>


// IRQ中断向量地址表
//extern  uint32 VICVectAddr[];


/********************************/
/*      应用程序配置            */
/********************************/
//#include    <stdio.h>
//#include    <ctype.h>
//#include    <stdlib.h>
//#include    <setjmp.h>
//#include    <rt_misc.h>

// 以下根据需要改动

#include   "Target.h"

//#include "2440lib.h"
//#include    "uart.h"
//#include    "lcddriver.h"
//#include    "target.h"
//#include    "..\..\Arm_Pc\pc.h"

/* 系统时钟宏定义，用于串口配置 */
//#define     FCLK		(200*1000000)	// 系统时钟，修改此参数必须同时修改startup.s的参数
//#define     HCLK		(FCLK/2)		// HCLK只能为FCLK除上1、2 
//#define     PCLK		(HCLK/2)	    // PCLK只能为HCLK除上1、2 

/* 是否显示液晶背景图片 */
//#define     DISP_BGPIC  0               // 非0时表示需要显示


/********************************/
/*       用户包含文件           */
/********************************/
// 以下根据需要改动


/********************************/
/*       用户定义内容           */
/********************************/
// 以下根据需要改动

#endif

/********************************************************************************************************
**                            End Of File
********************************************************************************************************/