//===================================================================
// File Name : 2440lib.h
// Function  : S3C2440 
// Date      : February 26, 2002
// Version   : 0.0
// History
//  0.0 :Feb.20.2002:SOP     : Programming start
//  0.01:Mar.29.2002:purnnamu: For Sleep_wake_up, the START... label is added
//===================================================================

#ifndef __2440lib_h__
#define __2440lib_h__

#ifdef __cplusplus
extern "C" {
#endif

#include "option.h"

#if USE_MAIN
#include <stdio.h>
#define Uart_Printf printf
#endif

#define min(x1,x2) (((x1)<(x2))? (x1):(x2))
#define max(x1,x2) (((x1)>(x2))? (x1):(x2))

#define ONESEC0 (62500)	             //16us resolution, max 1.04 sec
#define ONESEC1 (31250)	             //32us resolution, max 2.09 sec
#define ONESEC2 (15625)	             //64us resolution, max 4.19 sec
#define ONESEC3 (7812)	             //128us resolution, max 8.38 sec
#define ONESEC4 (PCLK/128/(0xff+1))  //@60Mhz, 128*4us resolution, max 32.53 sec

//#define NULL 0

#define EnterPWDN(clkcon) ((void (*)(int))0x20)(clkcon)
void StartPointAfterSleepWakeUp(void); //purnnamu:Mar.29.2002


// 2440lib.c
void Delay(int time);              //Watchdog Timer is used.

void *malloc(unsigned nbyte); 
void free(void *pt);

void Port_Init(void);
void Uart_Select(int ch);
void Uart_TxEmpty(int ch);
void Uart_Init(int mclk,int baud);
char Uart_Getch(void);
char Uart_GetKey(void);
int  Uart_GetIntNum(void);
void Uart_SendByte(int data);

#if !USE_MAIN
void Uart_Printf(const char *fmt,...);
#endif

void Uart_SendString(char *pt);

void Timer_Start(int divider);    //Watchdog Timer is used.
int  Timer_Stop(void);            //Watchdog Timer is used.

void Led_Display(int data);


void ChangeClockDivider(int hdivn_val,int pdivn_val);
void ChangeUPllValue(int m,int p,int s);
void ChangeMPllValue(int m,int p,int s);


void ChangeSdramParameter(char port, int minrc, int minrcd, int minrp, int refresh, int col_addr, int cl, char banksize);
void ChangeSromParameter(char bank, char minacc);


void LcdBkLtSet(U32 HiRatio);//lcd

#ifdef __cplusplus
}
#endif

#endif  //__2440lib_h__
