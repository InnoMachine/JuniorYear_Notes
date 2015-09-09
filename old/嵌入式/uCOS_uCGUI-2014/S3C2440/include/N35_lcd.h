/**************************************************************
The initial and control for 240°¡320 16Bpp TFT LCD----LtS350Q1
**************************************************************/

void Lcd_N35_Init(void);
unsigned int GetPixel(int x, int y);

extern unsigned char iphone_pic[];
extern unsigned char osx_800x480[];
extern unsigned char VGA_1024x768_DEMO[];

//#define LCD_TYPE_N35			1	//NEC3.5¥ÁLCD
#define LCD_TYPE_A70	2	//7¥Á’Ê≤ 
//#define LCD_TYPE_VGA1024x768 3

#define LCD_TYPE LCD_TYPE_N35

void Lcd_EnvidOnOff(int onoff);
void Lcd_ClearScr( U16 c);
void PutPixel(U32 x,U32 y, U16 c );
void GUI_Point(U32 x,U32 y, U16 c );
//void PutPixel(unsigned int x , unsigned int y , unsigned int c);
void Glib_Rectangle(int x1,int y1,int x2,int y2,int color);
//void Glib_Rectangle(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int color);
void Glib_FilledRectangle(int x1,int y1,int x2,int y2,int color);
//void Glib_FilledRectangle(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int color);
void Glib_Line(int x1,int y1,int x2,int y2,int color);
//void Glib_Line(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int color);
void Paint_Bmp(int x0,int y0,int h,int l,unsigned char bmp[]);

//================================
// ◊÷ÃÂ ‰≥ˆ
//================================
void Lcd_PutASCII(unsigned int x,unsigned int y,unsigned char ch,unsigned int c,unsigned int bk_c,unsigned int st); 
void Lcd_PutHZ(unsigned int x,unsigned int y,unsigned short int QW,unsigned int c,unsigned int bk_c,unsigned int st);  
void Lcd_printf(unsigned int x,unsigned int y,unsigned int c,unsigned int bk_c,unsigned int st,char *fmt,...); 



