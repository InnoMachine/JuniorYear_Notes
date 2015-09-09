#include "config.h"
U8 IntCnt;
//#define OSTickISR() Timer0_ISR()
/*********************************************************************************************************
Timer_Isr()
********************************************************************************************************/
void  Timer0_ISR(void)
{
	rSRCPND =rSRCPND|( 1 << 10);
	rINTPND = rINTPND;
	IntCnt++;
	/*
	if(IntCnt%2)
		rGPBDAT = 0x07fe;
	else
		rGPBDAT = 0x0000;*/
	OSTimeTick();
}

/*********************************************************************************************************
Initial Timer0 use for ucos time tick
********************************************************************************************************/
void Timer0Init(void)
{
	// ��ʱ������

	
	rTCON = rTCON & (~0xf) ;			// clear manual update bit, stop Timer0
	
	
	rTCFG0 	&= 0xffffff00;					// set Timer 0&1 prescaler 0
	rTCFG0 |= 15;							//prescaler = 15+1

	rTCFG1 	&= 0xfffffff0;					// set Timer 0 MUX 1/4
	rTCFG1  |= 0x00000001;					// set Timer 0 MUX 1/4
    rTCNTB0 = (PCLK / (4 *15* OS_TICKS_PER_SEC)) - 1;
 
    
    rTCON = rTCON & (~0xf) |0x02;              // updata 		
	rTCON = rTCON & (~0xf) |0x09; 	// star
 }

/*********************************************************************************************************
system IsrInit
********************************************************************************************************/
extern void OSTickISR(void);
void ISRInit(void)
{
	// �����жϿ�����
	rPRIORITY = 0x00000000;		// ʹ��Ĭ�ϵĹ̶������ȼ�
	rINTMOD = 0x00000000;		// �����жϾ�ΪIRQ�ж�
	pISR_TIMER0= (uint32) OSTickISR;
	rINTMSK &= ~(1<<10);			// ��TIMER0�ж�����
	IntCnt=0;
 }