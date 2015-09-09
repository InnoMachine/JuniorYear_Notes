/**************************************************************
The initial and control for 320×240 16Bpp TFT LCD----LCD_LTV350QV-F04
**************************************************************/
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "option.h"
#include "2440addr.h"
#include "2440lib.h"
#include "2440slib.h" 
#include "N35_lcd.h"


#define MVAL		(13)
#define MVAL_USED 	(0)		//0=each frame   1=rate by MVAL
#define INVVDEN		(1)		//0=normal       1=inverted
#define BSWP		(0)		//Byte swap control
#define HWSWP		(1)		//Half word swap control

#define M5D(n) ((n) & 0x1fffff)	// To get lower 21bits

/*#if LCD_TYPE == LCD_TYPE_N35
//TFT 240320
#define LCD_TFT_XSIZE 	(800)	
#define LCD_TFT_YSIZE 	(480)

#define SCR_XSIZE_TFT 	(800)
#define SCR_YSIZE_TFT 	(480)

//TFT240320
#define HOZVAL_TFT	(LCD_TFT_XSIZE-1)
#define LINEVAL_TFT	(LCD_TFT_YSIZE-1)

//Timing parameter for LCD LQ035Q7DB02
#define VBPD		(1)		//垂直同步信号的后肩
#define VFPD		(5)		//垂直同步信号的前肩
#define VSPW		(1)		//垂直同步信号的脉宽

#define HBPD		(35)		//水平同步信号的后肩
#define HFPD		(19)		//水平同步信号的前肩
#define HSPW		(5)		//水平同步信号的脉宽

#define CLKVAL_TFT	(4) 	
//FCLK=180MHz,HCLK=90MHz,VCLK=6.5MHz
*/
#if LCD_TYPE == LCD_TYPE_A70

#define LCD_TFT_XSIZE 	(800)	
#define LCD_TFT_YSIZE 	(480)

#define SCR_XSIZE_TFT 	(800)
#define SCR_YSIZE_TFT 	(480)

//TFT240320
#define HOZVAL_TFT	(LCD_TFT_XSIZE-1)
#define LINEVAL_TFT	(LCD_TFT_YSIZE-1)

//Timing parameter for LCD LQ035Q7DB02
#define VBPD		(32)		//垂直同步信号的后肩
#define VFPD		(9)		//垂直同步信号的前肩
#define VSPW		(1)		//垂直同步信号的脉宽

#define HBPD		(47)		//水平同步信号的后肩
#define HFPD		(15)		//水平同步信号的前肩
#define HSPW		(95)		//水平同步信号的脉宽

#define CLKVAL_TFT	(2) 	
//FCLK=180MHz,HCLK=90MHz,VCLK=6.5MHz

#elif LCD_TYPE == LCD_TYPE_VGA1024x768

#define LCD_TFT_XSIZE 	(1024)	
#define LCD_TFT_YSIZE 	(768)

#define SCR_XSIZE_TFT 	(1024)
#define SCR_YSIZE_TFT 	(768)

//TFT240320
#define HOZVAL_TFT	(LCD_TFT_XSIZE-1)
#define LINEVAL_TFT	(LCD_TFT_YSIZE-1)

//Timing parameter for LCD LQ035Q7DB02
#define VBPD		(1)		//垂直同步信号的后肩
#define VFPD		(1)		//垂直同步信号的前肩
#define VSPW		(1)		//垂直同步信号的脉宽

#define HBPD		(15)		//水平同步信号的后肩
#define HFPD		(19)		//水平同步信号的前肩
#define HSPW		(15)		//水平同步信号的脉宽

#define CLKVAL_TFT	(2) 	
//FCLK=180MHz,HCLK=90MHz,VCLK=6.5MHz
#endif

// GPB1/TOUT1 for Backlight control(PWM)
#define GPB1_TO_OUT()   (rGPBUP &= 0xfffd, rGPBCON &= 0xfffffff3, rGPBCON |= 0x00000004)
#define GPB1_TO_1()     (rGPBDAT |= 0x0002)
#define GPB1_TO_0()     (rGPBDAT &= 0xfffd)

//extern void Uart_Printf(char *f, ...) ;

extern unsigned char __CHS[];
extern unsigned char __VGA[];

//volatile static
  unsigned short LCD_BUFFER[SCR_YSIZE_TFT][SCR_XSIZE_TFT];

/**************************************************************
320×240 16Bpp TFT LCD功能模块初始化
**************************************************************/
static void Lcd_PowerEnable(int invpwren,int pwren);
static void Lcd_Init(void)
{
    rGPCUP  = 0x00000000;
	 rGPCCON = 0xaaaa02a9; 
	 
//    rGPDUP=0xffffffff; // Disable Pull-up register
     rGPDUP  = 0x00000000;
   rGPDCON=0xaaaaaaaa; //Initialize VD[15:8]

	rLCDCON1=(CLKVAL_TFT<<8)|(MVAL_USED<<7)|(3<<5)|(12<<1)|0;
    	// TFT LCD panel,16bpp TFT,ENVID=off
	rLCDCON2=(VBPD<<24)|(LINEVAL_TFT<<14)|(VFPD<<6)|(VSPW);
	rLCDCON3=(HBPD<<19)|(HOZVAL_TFT<<8)|(HFPD);
	rLCDCON4=(MVAL<<8)|(HSPW);
#if LCD_TYPE==LCD_TYPE_VGA1024x768
	rLCDCON5=(1<<11)|(0<<9)|(0<<8)|(0<<3)|(1<<0);
#else	
    rLCDCON5 = (1<<11) | (1<<10) | (1<<9) | (1<<8) | (0<<7) | (0<<6)
             | (1<<3)  |(BSWP<<1) | (HWSWP);
             //5:6:5 VCLK posedge BSWP=0,HWSWP=1;
#endif             

	rLCDSADDR1=(((U32)LCD_BUFFER>>22)<<21)|M5D((U32)LCD_BUFFER>>1);
	rLCDSADDR2=M5D( ((U32)LCD_BUFFER+(SCR_XSIZE_TFT*LCD_TFT_YSIZE*2))>>1 );
	rLCDSADDR3=(((SCR_XSIZE_TFT-LCD_TFT_XSIZE)/1)<<11)|(LCD_TFT_XSIZE/1);
	rLCDINTMSK|=(3); // MASK LCD Sub Interrupt
    rTCONSEL &= (~7) ;     // Disable LPC3480
	rTPAL=0; // Disable Temp Palette
}

/**************************************************************
LCD视频和控制信号输出或者停止，1开启视频输出
**************************************************************/
 void Lcd_EnvidOnOff(int onoff)
{
    if(onoff==1)
	rLCDCON1|=1; // ENVID=ON
    else
	rLCDCON1 =rLCDCON1 & 0x3fffe; // ENVID Off
}

/**************************************************************
320×240 16Bpp TFT LCD 电源控制引脚使能
**************************************************************/
static void Lcd_PowerEnable(int invpwren,int pwren)
{
    //GPG4 is setted as LCD_PWREN
    rGPGUP=rGPGUP&(~(1<<4))|(1<<4); // Pull-up disable
    rGPGCON=rGPGCON&(~(3<<8))|(3<<8); //GPG4=LCD_PWREN
    rGPGDAT = rGPGDAT | (1<<4) ;
//	invpwren=pwren;
    //Enable LCD POWER ENABLE Function
    rLCDCON5=rLCDCON5&(~(1<<3))|(pwren<<3);   // PWREN
    rLCDCON5=rLCDCON5&(~(1<<5))|(invpwren<<5);   // INVPWREN
}

/**************************************************************
320×240 16Bpp TFT LCD移动观察窗口
**************************************************************/
static void Lcd_MoveViewPort(int vx,int vy)
{
    U32 addr;

    SET_IF(); 
	#if (LCD_TFT_XSIZE<32)
    	    while((rLCDCON1>>18)<=1); // if x<32
	#else	
    	    while((rLCDCON1>>18)==0); // if x>32
	#endif
    
    addr=(U32)LCD_BUFFER+(vx*2)+vy*(SCR_XSIZE_TFT*2);
	rLCDSADDR1= ( (addr>>22)<<21 ) | M5D(addr>>1);
	rLCDSADDR2= M5D(((addr+(SCR_XSIZE_TFT*LCD_TFT_YSIZE*2))>>1));
	CLR_IF();
}    

/**************************************************************
320×240 16Bpp TFT LCD移动观察窗口
**************************************************************/
static void MoveViewPort(void)
{
    int vx=0,vy=0,vd=1;

    Uart_Printf("\n*Move the LCD view windos:\n");
    Uart_Printf(" press 8 is up\n");
    Uart_Printf(" press 2 is down\n");
    Uart_Printf(" press 4 is left\n");
    Uart_Printf(" press 6 is right\n");
    Uart_Printf(" press Enter to exit!\n");

    while(1)
    {
    	switch( Uart_GetKey() )
    	{
    	case '8':
	    if(vy>=vd)vy-=vd;    
	    Uart_Printf("vx=%3d,vy=%3d\n",vx,vy);
		Lcd_MoveViewPort(vx,vy);	   	
        break;

    	case '4':
    	    if(vx>=vd)vx-=vd;
    	    Uart_Printf("vx=%3d,vy=%3d\n",vx,vy);
			Lcd_MoveViewPort(vx,vy);	
    	break;

    	case '6':
                if(vx<=(SCR_XSIZE_TFT-LCD_TFT_XSIZE-vd))vx+=vd;  
                 Uart_Printf("vx=%3d,vy=%3d\n",vx,vy);
			    Lcd_MoveViewPort(vx,vy);	 	    
   	    break;

    	case '2':
                if(vy<=(SCR_YSIZE_TFT-LCD_TFT_YSIZE-vd))vy+=vd; 
                 Uart_Printf("vx=%3d,vy=%3d\n",vx,vy);
			   Lcd_MoveViewPort(vx,vy);	  	    
   	    break;

    	case '\r':
   	    return;

    	default:
	    break;
		}
	//Uart_Printf("vx=%3d,vy=%3d\n",vx,vy);
	//Lcd_MoveViewPort(vx,vy);
    }
}

/**************************************************************
320×240 16Bpp TFT LCD单个象素的显示数据输出
**************************************************************/
void PutPixel(U32 x,U32 y, U16 c )
{
	if ( (x < SCR_XSIZE_TFT) && (y < SCR_YSIZE_TFT) )
		LCD_BUFFER[(y)][(x)] = c;
}

unsigned int GetPixel(int x, int y)
{
	if ( (x < SCR_XSIZE_TFT) && (y < SCR_YSIZE_TFT) )
		return LCD_BUFFER[(y)][(x)];
}
 
void GUI_Point(U32 x,U32 y, U16 c )
{
	if ( (x < SCR_XSIZE_TFT) && (y < SCR_YSIZE_TFT) )
		LCD_BUFFER[(y)][(x)] = c;
}

/**************************************************************
320×240 16Bpp TFT LCD全屏填充特定颜色单元或清屏
**************************************************************/
void Lcd_ClearScr( U16 c)
{
	unsigned int x,y ;
		
    for( y = 0 ; y < SCR_YSIZE_TFT ; y++ )
    {
    	for( x = 0 ; x < SCR_XSIZE_TFT ; x++ )
    	{
			LCD_BUFFER[y][x] = c ;
    	}
    }
}

/**************************************************************
LCD屏幕显示垂直翻转
// LCD display is flipped vertically
// But, think the algorithm by mathematics point.
//   3I2
//   4 I 1
//  --+--   <-8 octants  mathematical cordinate
//   5 I 8
//   6I7
**************************************************************/
 void Glib_Line(int x1,int y1,int x2,int y2,int color)
{
	int dx,dy,e;
	dx=x2-x1; 
	dy=y2-y1;
    
	if(dx>=0)
	{
		if(dy >= 0) // dy>=0
		{
			if(dx>=dy) // 1/8 octant
			{
				e=dy-dx/2;
				while(x1<=x2)
				{
					PutPixel(x1,y1,color);
					if(e>0){y1+=1;e-=dx;}	
					x1+=1;
					e+=dy;
				}
			}
			else		// 2/8 octant
			{
				e=dx-dy/2;
				while(y1<=y2)
				{
					PutPixel(x1,y1,color);
					if(e>0){x1+=1;e-=dy;}	
					y1+=1;
					e+=dx;
				}
			}
		}
		else		   // dy<0
		{
			dy=-dy;   // dy=abs(dy)

			if(dx>=dy) // 8/8 octant
			{
				e=dy-dx/2;
				while(x1<=x2)
				{
					PutPixel(x1,y1,color);
					if(e>0){y1-=1;e-=dx;}	
					x1+=1;
					e+=dy;
				}
			}
			else		// 7/8 octant
			{
				e=dx-dy/2;
				while(y1>=y2)
				{
					PutPixel(x1,y1,color);
					if(e>0){x1+=1;e-=dy;}	
					y1-=1;
					e+=dx;
				}
			}
		}	
	}
	else //dx<0
	{
		dx=-dx;		//dx=abs(dx)
		if(dy >= 0) // dy>=0
		{
			if(dx>=dy) // 4/8 octant
			{
				e=dy-dx/2;
				while(x1>=x2)
				{
					PutPixel(x1,y1,color);
					if(e>0){y1+=1;e-=dx;}	
					x1-=1;
					e+=dy;
				}
			}
			else		// 3/8 octant
			{
				e=dx-dy/2;
				while(y1<=y2)
				{
					PutPixel(x1,y1,color);
					if(e>0){x1-=1;e-=dy;}	
					y1+=1;
					e+=dx;
				}
			}
		}
		else		   // dy<0
		{
			dy=-dy;   // dy=abs(dy)

			if(dx>=dy) // 5/8 octant
			{
				e=dy-dx/2;
				while(x1>=x2)
				{
					PutPixel(x1,y1,color);
					if(e>0){y1-=1;e-=dx;}	
					x1-=1;
					e+=dy;
				}
			}
			else		// 6/8 octant
			{
				e=dx-dy/2;
				while(y1>=y2)
				{
					PutPixel(x1,y1,color);
					if(e>0){x1-=1;e-=dy;}	
					y1-=1;
					e+=dx;
				}
			}
		}	
	}
}

/**************************************************************
在LCD屏幕上画一个矩形
**************************************************************/
void Glib_Rectangle(int x1,int y1,int x2,int y2,int color)
{
    Glib_Line(x1,y1,x2,y1,color);
    Glib_Line(x2,y1,x2,y2,color);
    Glib_Line(x1,y2,x2,y2,color);
    Glib_Line(x1,y1,x1,y2,color);
}

/**************************************************************
在LCD屏幕上用颜色填充一个矩形
**************************************************************/
void Glib_FilledRectangle(int x1,int y1,int x2,int y2,int color)
{
    int i;

    for(i=y1;i<=y2;i++)
	Glib_Line(x1,i,x2,i,color);
}

/**************************************************************
在LCD屏幕上指定坐标点画一个指定大小的图片
**************************************************************/
void Paint_Bmp(int x0,int y0,int h,int l,unsigned char bmp[])
{
	int x,y;
	U32 c;
	int p = 0;
	
    for( y = y0 ; y < l ; y++ )
    {
    	for( x = x0 ; x < h ; x++ )
    	{
    		c = bmp[p+1] | (bmp[p]<<8) ;

			if ( ( (x0+x) < SCR_XSIZE_TFT) && ( (y0+y) < SCR_YSIZE_TFT) )
				LCD_BUFFER[y0+y][x0+x] = c ;
			
    		p = p + 2 ;
    	}
    }
}

#if 1
/**************************************************************
在LCD屏幕上指定坐标点写ASCII码
**************************************************************/
void Lcd_PutASCII(unsigned int x,unsigned int y,unsigned char ch,unsigned int c,unsigned int bk_c,unsigned int st)
{
	unsigned short int i,j;
	unsigned char *pZK,mask,buf;
	
	

	pZK = &__VGA[ch*16];
	for( i = 0 ; i < 16 ; i++ )
	{
		mask = 0x80;
		buf = pZK[i];
        for( j = 0 ; j < 8 ; j++ )
        {
            if( buf & mask )
            {
                PutPixel(x+j,y+i,c);
            }else
            {
                if( !st )
                {
                    PutPixel(x+j,y+i,bk_c);
                }
            }
            
            mask = mask >> 1;
        }
	}
}

/**************************************************************
在LCD屏幕上指定坐标点写汉字
**************************************************************/
void Lcd_PutHZ(unsigned int x,unsigned int y,unsigned short int QW,unsigned int c,unsigned int bk_c,unsigned int st)
{
	unsigned short int i,j;
	unsigned char *pZK,mask,buf;

	pZK = &__CHS[ (  ( (QW >> 8) - 1 )*94 + (QW & 0x00FF)- 1 )*32 ];
	for( i = 0 ; i < 16 ; i++ )
	{
		//左
		mask = 0x80;
        buf = pZK[i*2];
        for( j = 0 ; j < 8 ; j++ )
        {
            if( buf & mask )
            {
                PutPixel(x+j,y+i,c);
            }else
            {
                if( !st )
                {
                    PutPixel(x+j,y+i,bk_c);
                }
            }
            mask = mask >> 1;
        } 
        
		//右
		mask = 0x80;
        buf = pZK[i*2 + 1];
        for( j = 0 ; j < 8 ; j++ )
        {
            if( buf & mask )
            {
                PutPixel(x+j + 8,y+i,c);
            }else
            {
                if( !st )
                {
                    PutPixel(x+j + 8,y+i,bk_c);
                }
            }
            mask = mask >> 1;
        }                 
	}
}

//----------------------
void Lcd_printf(unsigned int x,unsigned int y,unsigned int c,unsigned int bk_c,unsigned int st,char *fmt,...)
{
    char __LCD_Printf_Buf[256];
    va_list ap;
	unsigned char *pStr = (unsigned char *)__LCD_Printf_Buf;
    unsigned int i = 0;

    va_start(ap,fmt);
    vsprintf(__LCD_Printf_Buf,fmt,ap);
    va_end(ap);
	 
    while(*pStr != 0 )
	{
		switch(*pStr)
		{
			case '\n' :
				{
			
                    break;
				}

			default:
				{
					if( *pStr > 0xA0 & *(pStr+1) > 0xA0 )  //中文输出
                    {
                        Lcd_PutHZ( x , y , (*pStr - 0xA0)*0x0100 + *(pStr+1) - 0xA0 , c , bk_c , st);

                        pStr++;
                        i++;

                        x += 16;
                    }else               //英文输出
                    {
                        Lcd_PutASCII( x , y , *pStr , c , bk_c , st );

                        x += 8;

                    }

                    break;
				}
		}
		
		pStr++;
        i++;		

        if( i > 256 ) break;
	}
   
}
#endif

void Lcd_N35_Init(void)
{
    Lcd_Init();
	//mini2440所使用的LCD驱动板上没有背光调节硬件电路支持
	//LcdBkLtSet( 70 ) ;
	
	Lcd_PowerEnable(0, 1);
    Lcd_EnvidOnOff(1);		//turn on vedio

    Lcd_ClearScr( (0x00<<11) | (0x00<<5) | (0x00) );  
    
#if LCD_TYPE == LCD_TYPE_N35
	//2009-05-24 Huang added the following statement to disable iphone_pic     
	//Paint_Bmp(0, 0, 240, 320, iphone_pic);
#elif (LCD_TYPE == LCD_TYPE_A70)
	//Paint_Bmp(0, 0, 800, 480, osx_800x480);
#elif LCD_TYPE==LCD_TYPE_VGA1024x768
	//Paint_Bmp(0, 0, 1024, 768, VGA_1024x768_DEMO);
#endif	
}

