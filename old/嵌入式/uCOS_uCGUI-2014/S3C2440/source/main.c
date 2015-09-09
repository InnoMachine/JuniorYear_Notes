
#include "config.h"
#include <stdlib.h>
//=======================================
#include "app_cfg.h"
#include "Printf.h"
#include "ucos_ii.h"

#include "gui.h"
#include "math.h"
#include "GUI_Protected.h"
#include "GUIDEMO.H"
#include "WM.h"
#include "Dialog.h"
#include "LISTBOX.h"
#include "EDIT.h"
#include "SLIDER.h"
#include "FRAMEWIN.h" 
extern unsigned char iphone_pic[];

//=========================================
OS_STK  MainTaskStk[MainTaskStkLengh];
OS_STK	Task0Stk [Task0StkLengh];       // Define the Task0 stack  for ts
OS_STK	Task1Stk [Task1StkLengh];       // Define the Task1 stack 
OS_STK	Task2Stk [Task2StkLengh];       // Define the Task2 stack 
OS_STK	Task3Stk [Task3StkLengh];		//define the task3 stack
int rYear, rMonth,rDay,rDayOfWeek,rHour,rMinute,rSecond;

OS_EVENT *Semp;                         //Creat semp
U8 err;


/*******************************************************************
*
*      Structure containing information for drawing routine
*
*******************************************************************
*/

typedef struct {
  I16 *aY;
} PARAM;

/*******************************************************************
*
*                    Defines
*
********************************************************************
*/

#define YSIZE   (LCD_YSIZE - 100)
#define DEG2RAD (3.1415926f / 180)

#if LCD_BITSPERPIXEL == 1
  #define COLOR_GRAPH0 GUI_WHITE
  #define COLOR_GRAPH1 GUI_WHITE
#else
  #define COLOR_GRAPH0 GUI_GREEN
  #define COLOR_GRAPH1 GUI_YELLOW
#endif

/*******************************************************************
*
*                    Draws the graph area
*
********************************************************************
*/

static void Draw(void * p) {
  int i;
  PARAM * pParam = (PARAM *)p;
  GUI_SetBkColor(GUI_BLACK);
  GUI_SetColor(GUI_DARKGRAY);
  GUI_ClearRect(19, (LCD_YSIZE - 20) - YSIZE, (LCD_XSIZE - 2), (LCD_YSIZE - 21));
  for (i = 0; i < (YSIZE / 2); i += 20) {
    GUI_DrawHLine((LCD_YSIZE - 20) - (YSIZE / 2) + i, 19, (LCD_XSIZE - 2));
    if (i) {
      GUI_DrawHLine((LCD_YSIZE - 20) - (YSIZE / 2) - i, 19, (LCD_XSIZE - 2));
    }
  }
  for (i = 40; i < (LCD_XSIZE - 20); i += 40) {
    GUI_DrawVLine(18 + i, (LCD_YSIZE - 20) - YSIZE, (LCD_YSIZE - 21));
  }
  GUI_SetColor(COLOR_GRAPH0);
  GUI_DrawGraph(pParam->aY, (LCD_XSIZE - 20), 19, (LCD_YSIZE - 20) - YSIZE);
}

static void Draw2(void * p) {
  PARAM * pParam = (PARAM *)p;
  Draw(p);
  GUI_SetColor(COLOR_GRAPH1);
  GUI_DrawGraph(pParam->aY+15, (LCD_XSIZE - 20), 19, (LCD_YSIZE - 20) - YSIZE);
}
/*******************************************************************
*
*                    Labels the x & y-axis
*
********************************************************************
*/

static void Label(void) {
  int x, y;
  GUI_SetBkColor(GUI_RED);
  GUI_Clear();
  GUI_SetPenSize(1);
  GUI_ClearRect(0, (LCD_YSIZE - 21) - YSIZE, (LCD_XSIZE - 1), (LCD_YSIZE - 1));
  GUI_DrawRect(18, (LCD_YSIZE - 21) - YSIZE, (LCD_XSIZE - 1), (LCD_YSIZE - 20));
  GUI_SetFont(&GUI_Font6x8);
  for (x = 0; x < (LCD_XSIZE - 20); x += 40) {
    int xPos = x + 18;
    GUI_DrawVLine(xPos, (LCD_YSIZE - 20), (LCD_YSIZE - 14));
    GUI_DispDecAt(x / 40, xPos - 2, (LCD_YSIZE - 9), 1);
  }
  for (y = 0; y < YSIZE / 2; y += 20) {
    int yPos = (LCD_YSIZE - 20) - YSIZE / 2 + y;
    GUI_DrawHLine(yPos, 13, 18);
    if (y) {
      GUI_GotoXY(1, yPos - 4);
      GUI_DispSDec(-y / 20, 2);
      yPos = (LCD_YSIZE - 20) - YSIZE / 2 - y;
      GUI_DrawHLine(yPos, 13, 18);
      GUI_GotoXY(1, yPos - 4);
      GUI_DispSDec(y / 20, 2);
    } else {
      GUI_DispCharAt('0', 7, yPos - 4);
    }
  }
}

/*******************************************************************
*
*               Draws random data
*
********************************************************************
*/

static void GetRandomData(I16 * paY, int Time, int n) {
  int aDiff, i;
  
  if (Time > 5000)
    Time -= 5000;
  if (Time > 2500)
    Time = 5000 - Time;
  Time /= 200;
  aDiff = Time * Time + 1;
  for (i = 0; i < n; i++) {
    if (!i) {
      paY[i] = rand() % YSIZE;
    } else {
      I16 yNew;
      int yD = aDiff - (rand() % aDiff);
      if (rand() & 1) {
        yNew = paY[i-1] + yD;
      } else {
        yNew = paY[i-1] - yD;
      }
      if (yNew > YSIZE) {
        yNew -= yD;
      } else { if (yNew < 0)
        yNew += yD;
      }
      paY[i] = yNew;
    }
  }
}

static void DemoRandomGraph(void) {
  PARAM Param;
  int tDiff, t0; 
  GUI_RECT Rect = {19, (LCD_YSIZE - 20) - YSIZE, (LCD_XSIZE - 2), (LCD_YSIZE - 21)};
  GUI_HMEM hMem = GUI_ALLOC_Alloc((LCD_XSIZE - 20) * sizeof(I16));
  
  OSPrintf("Enter DemoRandomGraph:\n");
  
  GUI_SetColor(GUI_WHITE);
  GUI_SetBkColor(GUI_RED);
  GUI_ClearRect(0, 0, LCD_XSIZE, 60);
  GUI_SetFont(&GUI_FontHZ12);
  GUI_DispStringAt("任意波形", 10, 20);
  Param.aY = GUI_ALLOC_h2p(hMem);
  GUI_SetFont(&GUI_Font6x8);
  t0 = GUI_GetTime();
  while((tDiff = (GUI_GetTime() - t0)) < 10000) {
    int t1, tDiff2;
    GetRandomData(Param.aY, tDiff, (LCD_XSIZE - 20));
    t1 = GUI_GetTime();
    GUI_MEMDEV_Draw(&Rect, Draw, &Param, 0, 0);
    tDiff2 = GUI_GetTime() - t1;
    if (tDiff2 < 100) {
      GUI_Delay(100 - tDiff2);
    }
  }
  GUI_ALLOC_Free(hMem);
}

/*******************************************************************
*
*               Draws a sine wave
*
********************************************************************
*/

static void GetSineData(I16 * paY, int n) {
  int i;
  for (i = 0; i < n; i++) {
    float s = sin(i * DEG2RAD * 4);
    paY[i] = s * YSIZE / 2 + YSIZE / 2;
  }
}

static void DemoSineWave(void) {
  PARAM Param;
  I16 * pStart;
  int t0, Cnt = 0;
  GUI_RECT Rect = {19, (LCD_YSIZE - 20) - YSIZE, (LCD_XSIZE - 2), (LCD_YSIZE - 21)};
  GUI_HMEM hMem = GUI_ALLOC_Alloc(405 * sizeof(I16));
  
  OSPrintf("Enter DemoSineWave!\n");
  
  GUI_SetColor(GUI_WHITE);
  GUI_SetBkColor(GUI_RED);
  GUI_ClearRect(0, 0, LCD_XSIZE, 60);
  GUI_SetFont(&GUI_FontHZ12);
  GUI_DispStringAt("正弦波", 10, 20);
  pStart = GUI_ALLOC_h2p(hMem);
  GetSineData(pStart, 405);
  GUI_SetFont(&GUI_Font6x8);
  t0 = GUI_GetTime();
  while((GUI_GetTime() - t0) < 10000) {
    int t1, tDiff2;
    if (Cnt++ % 90) {
      Param.aY++;
    } else {
      Param.aY = pStart;
    }
    t1 = GUI_GetTime();
    GUI_MEMDEV_Draw(&Rect, Draw2, &Param, 0, 0);
    tDiff2 = GUI_GetTime() - t1;
    if (tDiff2 < 100) {
      GUI_Delay(100 - tDiff2);
    }
  }
  GUI_ALLOC_Free(hMem);
}

/*******************************************************************
*
*               Adds several waves
*
********************************************************************
*/

static void DrawOrData(GUI_COLOR Color, I16 * paY) {
  GUI_SetColor(Color);
  GUI_DrawGraph(paY, (LCD_XSIZE - 20), 19, (LCD_YSIZE - 20) - YSIZE);
}

static void DemoOrData(void) {
  int i;
  PARAM Param;
  GUI_RECT Rect = {19, (LCD_YSIZE - 20) - YSIZE, (LCD_XSIZE - 2), (LCD_YSIZE - 21)};
  GUI_HMEM hMem = GUI_ALLOC_Alloc(405 * sizeof(I16));
  
  OSPrintf("Enter DemoOrData!\n");
  
  GUI_SetColor(GUI_WHITE);
  GUI_SetBkColor(GUI_RED);
  GUI_ClearRect(0, 0, LCD_XSIZE, 60);
  GUI_SetFont(&GUI_FontHZ12);
  GUI_DispStringAt("连续波...",0,20);
  Param.aY = GUI_ALLOC_h2p(hMem);
  GetSineData(Param.aY, 405);
  GUI_MEMDEV_Draw(&Rect, Draw, &Param, 0, 0);
  for (i = 0; (i < 90); i++) {
    DrawOrData(GUI_GREEN, ++Param.aY);
    GUI_Delay(10);
  }
  GUI_ALLOC_Free(hMem);
}

int num=0;

int Main(void)
{	
	//初始化目标板
	TargetInit(); 
	
	//初始化uC/OS   
   	OSInit ();	 
   	
   	//初始化系统时基
   	OSTimeSet(0);
   	
   	//创建系统初始任务
   	OSTaskCreate (MainTask,(void *)0, &MainTaskStk[MainTaskStkLengh - 1], MainTaskPrio);	
   																										

	OSStart ();
	
	return 0;
}

void MainTask(void *pdata) //Main Task create taks0 and task1
{
   
#if OS_CRITICAL_METHOD == 3                                // Allocate storage for CPU status register 
	OS_CPU_SR  cpu_sr;
#endif

	OS_ENTER_CRITICAL();
	Timer0Init();//initial timer0 for ucos time tick
	ISRInit();   //initial interrupt prio or enable or disable
	OS_EXIT_CRITICAL();
	
	OSPrintfInit();//use task to print massage to Uart 
	OSStatInit();
	
	GUI_Init();
    //GUI_MEMDEV_Load();
   // Label();
    OSPrintf("Enter MainTask:\n");
	//DemoRandomGraph();
	//DemoSineWave();	
	//DemoOrData();
	
	OSTaskCreate (Task1,(void *)0, &Task1Stk[Task1StkLengh - 1], Task1Prio);	
	//OSTaskCreate (Task2,(void *)0, &Task2Stk[Task2StkLengh - 1], Task2Prio);
	//OSTaskCreate (Task3,(void *)0, &Task3Stk[Task3StkLengh - 1], Task3Prio);
	while(1)
	 { 
	   OSCtxSwCtr = 0;                                     // Clear the context switch counter         
       OSTaskDel( MainTaskPrio );	  
	 }
	
}



void Task1	(void *pdata) //task for test
{
	OSPrintf("Enter Task1\n");
	if(num<1)
	{
		GUI_Init();
	    GUI_MEMDEV_Load();
	    Label();
	    num=1;
    }
	DemoRandomGraph();
	while(1)
	{  	
	   OSCtxSwCtr = 0;                                     // Clear the context switch counter
	   OSTaskCreate (Task2,(void *)0, &Task2Stk[Task2StkLengh - 1], Task2Prio);         
       OSTaskDel( Task1Prio );	
    	
	}
}

void Task2(void *pdata)
{	
	OSPrintf("Enter Task2\n");
	//GUI_Init();
    //GUI_MEMDEV_Load();
    //Label();
    DemoSineWave();
	while(1)
	{
		OSCtxSwCtr = 0;                                     // Clear the context switch counter 
		OSTaskCreate (Task3,(void *)0, &Task3Stk[Task3StkLengh - 1], Task3Prio);        
       OSTaskDel( Task2Prio );	
	}
}

void Task3(void *pdata)
{
	OSPrintf("Enter Task3\n");
	//GUI_Init();
    //GUI_MEMDEV_Load();
    //Label();
    DemoOrData();
	while(1)
	{	
	   OSCtxSwCtr = 0;                                     // Clear the context switch counter
	   OSTaskCreate (Task1,(void *)0, &Task1Stk[Task1StkLengh - 1], Task1Prio);         
       OSTaskDel( Task3Prio );	
		
	}
}




