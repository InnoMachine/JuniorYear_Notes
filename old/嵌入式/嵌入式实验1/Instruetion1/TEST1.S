COUNT	EQU 0x30001010 ;定义一个变量，地址在0x30001010

	AREA Example1,CODE,READONLY ;声明代码段Example1

	ENTRY ;标识程序入口

	CODE32 ;声明31 位ARM 指令
	
rGPFCON EQU 0x56000050
rGPFDAT EQU 0x56000054
rGPFUP  EQU 0x56000058

START	LDR R1,=COUNT;	R1<=COUNT

		MOV R0,#0;		R0<=0 

		STR R0,[R1];	[R1]<=R0,即设置COUNT 为0
		

		
		ldr	r0,=rGPFCON;
		ldr	r1,=0x5500;
		str	r1,[r0];
	
		ldr	r0,=rGPFDAT;
		ldr	r1,=0x10;
		str	r1,[r0];
		
		ldr R2,=0x1ffffff;
	
		
LOOP
		ldr	r0,=rGPFDAT;
		ldr	r1,=0x20;
		str	r1,[r0];
		SUBS R2,R2,#1;
		BNE LOOP		
		ldr R2,=0x1ffffff;
LOOP1
		ldr	r0,=rGPFDAT;
		ldr	r1,=0x40;
		str	r1,[r0];
		SUBS R2,R2,#1;
		BNE LOOP1
		ldr R2,=0x1ffffff;
		B LOOP			
		
		END
		
//		LDR r0, =num
//	LDR r1, [r0]
		
		
//AREA  data, DATA
//num	DCD 0xffffffff 

//LOOP	LDR R1,=COUNT;

//		LDR R0,[R1];	R0<=[R1]

//		ADD R0,R0,#1;	R0<=R0+1

//		CMP R0,#10;		R0 与10 比较，影响条件码标志

//		MOVHS R0,#0;	若R0>=10，则此指令执行　R0<=0

//		STR R0,[R1];	[R1]<=R0，即保存COUNT

//		B LOOP