/****************************************Copyright (c)**************************************************
**                               Guangzhou ZHIYUAN electronics Co.,LTD.
**                                     
**                                 http://www.zyinside.com
**
**--------------File Info-------------------------------------------------------------------------------
** File Name:          config.h
** Last modified Date: 2006-01-06
** Last Version:       v2.0
** Descriptions:       �û�����ͷ�ļ�
**
**------------------------------------------------------------------------------------------------------
** Created By:         ���ܱ�
** Created date:       2005-12-31 
** Version:            v1.0
** Descriptions:       ����
**
**------------------------------------------------------------------------------------------------------
** Modified by:        �ʴ�
** Modified date:      2006-01-06 
** Version:            v2.0
** Descriptions:       �޸�����S3C2410
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

//��һ������Ķ�
#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL  		0
#endif

typedef unsigned char  uint8;                   // �޷���8λ���ͱ���
typedef signed   char  int8;                    // �з���8λ���ͱ���
typedef unsigned short uint16;                  // �޷���16λ���ͱ���
typedef signed   short int16;                   // �з���16λ���ͱ���
typedef unsigned int   uint32;                  // �޷���32λ���ͱ���
typedef signed   int   int32;                   // �з���32λ���ͱ���
typedef float          fp32;                    // �����ȸ�����(32λ����)
typedef double         fp64;                    // ˫���ȸ�����(64λ����)


/********************************/
/*      uC/OS-II���������      */
/********************************/
#define     USER_USING_MODE    0x10             // �û�ģʽ,ARM����
                                                // ֻ����0x10,0x30,0x1f,0x3f֮һ
//#include   "INCLUDES.H"  

#include "ucos_ii.h"                                      
          
                                           
/********************************/
/*        ARM���������         */
/********************************/
// ��һ������Ķ�
#include    "2440addr.h"
#include    <stdio.h>
#include    <ctype.h>
#include    <stdlib.h>


// IRQ�ж�������ַ��
//extern  uint32 VICVectAddr[];


/********************************/
/*      Ӧ�ó�������            */
/********************************/
//#include    <stdio.h>
//#include    <ctype.h>
//#include    <stdlib.h>
//#include    <setjmp.h>
//#include    <rt_misc.h>

// ���¸�����Ҫ�Ķ�

#include   "Target.h"

//#include "2440lib.h"
//#include    "uart.h"
//#include    "lcddriver.h"
//#include    "target.h"
//#include    "..\..\Arm_Pc\pc.h"

/* ϵͳʱ�Ӻ궨�壬���ڴ������� */
//#define     FCLK		(200*1000000)	// ϵͳʱ�ӣ��޸Ĵ˲�������ͬʱ�޸�startup.s�Ĳ���
//#define     HCLK		(FCLK/2)		// HCLKֻ��ΪFCLK����1��2 
//#define     PCLK		(HCLK/2)	    // PCLKֻ��ΪHCLK����1��2 

/* �Ƿ���ʾҺ������ͼƬ */
//#define     DISP_BGPIC  0               // ��0ʱ��ʾ��Ҫ��ʾ


/********************************/
/*       �û������ļ�           */
/********************************/
// ���¸�����Ҫ�Ķ�


/********************************/
/*       �û���������           */
/********************************/
// ���¸�����Ҫ�Ķ�

#endif

/********************************************************************************************************
**                            End Of File
********************************************************************************************************/