;=========================================
; NAME: 2440INIT.S of mini2440 uCos-ii 2009-05-16
; DESC: C start up codes
;       Configure memory, ISR ,stacks
;	Initialize C-variables
; HISTORY:
; 2002.02.25:kwtark: ver 0.0
; 2002.03.20:purnnamu: Add some functions for testing STOP,Sleep mode
; 2003.03.14:DonGo: Modified for 2440.
;=========================================

	GET option.inc
	GET memcfg.inc
	GET 2440addr.inc

BIT_SELFREFRESH EQU	(1<<22)

;Pre-defined constants
USERMODE    EQU 	0x10
FIQMODE     EQU 	0x11
IRQMODE     EQU 	0x12
SVCMODE     EQU 	0x13
ABORTMODE   EQU 	0x17
UNDEFMODE   EQU 	0x1b
MODEMASK    EQU 	0x1f
NOINT       EQU 	0xc0

;The location of stacks
UserStack	EQU	(_STACK_BASEADDRESS-0x3800)	;0x33ff4800 ~
SVCStack	EQU	(_STACK_BASEADDRESS-0x2800)	;0x33ff5800 ~
UndefStack	EQU	(_STACK_BASEADDRESS-0x2400)	;0x33ff5c00 ~
AbortStack	EQU	(_STACK_BASEADDRESS-0x2000)	;0x33ff6000 ~
IRQStack	EQU	(_STACK_BASEADDRESS-0x1000)	;0x33ff7000 ~
FIQStack	EQU	(_STACK_BASEADDRESS-0x0)	;0x33ff8000 ~


; :::::::::::::::::::::::::::::::::::::::::::::
;           BEGIN: Power Management 
; - - - - - - - - - - - - - - - - - - - - - - -
Mode_USR            EQU     0x10
Mode_FIQ            EQU     0x11
Mode_IRQ            EQU     0x12
Mode_SVC            EQU     0x13
Mode_ABT            EQU     0x17
Mode_UND            EQU     0x1B
Mode_SYS            EQU     0x1F

I_Bit               EQU     0x80
F_Bit               EQU     0x40
; - - - - - - - - - - - - - - - - - - - - - - -
;Check if tasm.exe(armasm -16 ...@ADS 1.0) is used.
	GBLL    THUMBCODE
	[ {CONFIG} = 16
THUMBCODE SETL  {TRUE}
	    CODE32
 		|
THUMBCODE SETL  {FALSE}
    ]

 		MACRO
	MOV_PC_LR
 		[ THUMBCODE
	    bx lr
 		|
	    mov	pc,lr
 		]
	MEND

 		MACRO
	MOVEQ_PC_LR
 		[ THUMBCODE
        bxeq lr
 		|
	    moveq pc,lr
 		]
	MEND

 		MACRO
$HandlerLabel HANDLER $HandleLabel

$HandlerLabel
	sub	sp,sp,#4	;decrement sp(to store jump address)
	stmfd	sp!,{r0}	;PUSH the work register to stack(lr does''t push because it return to original address)
	ldr     r0,=$HandleLabel;load the address of HandleXXX to r0
	ldr     r0,[r0]	 ;load the contents(service routine start address) of HandleXXX
	str     r0,[sp,#4]      ;store the contents(ISR) of HandleXXX to stack
	ldmfd   sp!,{r0,pc}     ;POP the work register and pc(jump to ISR)
	MEND


	IMPORT  |Image$$RO$$Limit|  ; End of ROM code (=start of ROM data)
	IMPORT  |Image$$RW$$Base|   ; Base of RAM to initialise
	IMPORT  |Image$$ZI$$Base|   ; Base and limit of area
	IMPORT  |Image$$ZI$$Limit|  ; to zero initialise

	IMPORT	MMU_SetAsyncBusMode

	IMPORT  Main    ; The main entry of mon program
	IMPORT  OS_CPU_IRQ_ISR ;uCOS_II IrqISR
	EXPORT  HandleEINT0	 ;for os_cpu_a.s
	
	
	EXPORT  __ENTRY

	AREA    Init,CODE,READONLY

	ENTRY
__ENTRY

	;1)The code, which converts to Big-endian, should be in little endian code.
	;2)The following little endian code will be compiled in Big-Endian mode.
	;  The code byte order should be changed as the memory bus width.
	;3)The pseudo instruction,DCD can not be used here because the linker generates error.
	ASSERT	:DEF:ENDIAN_CHANGE
	[ ENDIAN_CHANGE
	    ASSERT  :DEF:ENTRY_BUS_WIDTH
	    [ ENTRY_BUS_WIDTH=32
		b	ChangeBigEndian	    ;DCD 0xea000007
	    ]

	    [ ENTRY_BUS_WIDTH=16
		andeq	r14,r7,r0,lsl #20   ;DCD 0x0007ea00
	    ]

	    [ ENTRY_BUS_WIDTH=8
		streq	r0,[r0,-r10,ror #1] ;DCD 0x070000ea
	    ]
	|
	    b	ResetHandler
    ]
	b	HandlerUndef	;handler for Undefined mode
	b	HandlerSWI	    ;handler for SWI interrupt
	b	HandlerPabort	;handler for PAbort
	b	HandlerDabort	;handler for DAbort
	b	.		        ;reserved
	b	HandlerIRQ	;handler for IRQ interrupt
	b	HandlerFIQ	;handler for FIQ interrupt

;@0x20
	b	EnterPWDN	; Must be @0x20.
ChangeBigEndian
;@0x24
	[ ENTRY_BUS_WIDTH=32
	    DCD	0xee110f10	;0xee110f10 => mrc p15,0,r0,c1,c0,0
	    DCD	0xe3800080	;0xe3800080 => orr r0,r0,#0x80;  //Big-endian
	    DCD	0xee010f10	;0xee010f10 => mcr p15,0,r0,c1,c0,0
	]
	[ ENTRY_BUS_WIDTH=16
	    DCD 0x0f10ee11
	    DCD 0x0080e380
	    DCD 0x0f10ee01
	]
	[ ENTRY_BUS_WIDTH=8
	    DCD 0x100f11ee
	    DCD 0x800080e3
	    DCD 0x100f01ee
    ]
	DCD 0xffffffff  ;swinv 0xffffff is similar with NOP and run well in both endian mode.
	DCD 0xffffffff
	DCD 0xffffffff
	DCD 0xffffffff
	DCD 0xffffffff
	b ResetHandler

;Function for entering power down mode
; 1. SDRAM should be in self-refresh mode.
; 2. All interrupt should be maksked for SDRAM/DRAM self-refresh.
; 3. LCD controller should be disabled for SDRAM/DRAM self-refresh.
; 4. The I-cache may have to be turned on.
; 5. The location of the following code may have not to be changed.

;void EnterPWDN(int CLKCON);
EnterPWDN
	mov r2,r0		;r2=rCLKCON
	tst r0,#0x8		;SLEEP mode?
	bne ENTER_SLEEP

ENTER_STOP
	ldr r0,=REFRESH
	ldr r3,[r0]		;r3=rREFRESH
	mov r1, r3
	orr r1, r1, #BIT_SELFREFRESH
	str r1, [r0]		;Enable SDRAM self-refresh

	mov r1,#16			;wait until self-refresh is issued. may not be needed.
0	subs r1,r1,#1
	bne %B0

	ldr r0,=CLKCON		;enter STOP mode.
	str r2,[r0]

	mov r1,#32
0	subs r1,r1,#1	;1) wait until the STOP mode is in effect.
	bne %B0		;2) Or wait here until the CPU&Peripherals will be turned-off
			;   Entering SLEEP mode, only the reset by wake-up is available.

	ldr r0,=REFRESH ;exit from SDRAM self refresh mode.
	str r3,[r0]

	MOV_PC_LR

ENTER_SLEEP
	;NOTE.
	;1) rGSTATUS3 should have the return address after wake-up from SLEEP mode.

	ldr r0,=REFRESH
	ldr r1,[r0]		;r1=rREFRESH
	orr r1, r1, #BIT_SELFREFRESH
	str r1, [r0]		;Enable SDRAM self-refresh

	mov r1,#16			;Wait until self-refresh is issued,which may not be needed.
0	subs r1,r1,#1
	bne %B0

	ldr	r1,=MISCCR
	ldr	r0,[r1]
	orr	r0,r0,#(7<<17)  ;Set SCLK0=0, SCLK1=0, SCKE=0.
	str	r0,[r1]

	ldr r0,=CLKCON		; Enter sleep mode
	str r2,[r0]

	b .			;CPU will die here.


WAKEUP_SLEEP
	;Release SCLKn after wake-up from the SLEEP mode.
	ldr	r1,=MISCCR
	ldr	r0,[r1]
	bic	r0,r0,#(7<<17)  ;SCLK0:0->SCLK, SCLK1:0->SCLK, SCKE:0->=SCKE.
	str	r0,[r1]

	;Set memory control registers
 	ldr	r0,=SMRDATA
	ldr	r1,=BWSCON	;BWSCON Address
	add	r2, r0, #52	;End address of SMRDATA
0
	ldr	r3, [r0], #4
	str	r3, [r1], #4
	cmp	r2, r0
	bne	%B0

	mov r1,#256
0	subs r1,r1,#1	;1) wait until the SelfRefresh is released.
	bne %B0

	ldr r1,=GSTATUS3 	;GSTATUS3 has the start address just after SLEEP wake-up
	ldr r0,[r1]

	mov pc,r0

	LTORG
HandlerFIQ      HANDLER HandleFIQ
HandlerIRQ      HANDLER HandleIRQ
HandlerUndef    HANDLER HandleUndef
HandlerSWI      HANDLER HandleSWI
HandlerDabort   HANDLER HandleDabort
HandlerPabort   HANDLER HandlePabort

IsrIRQ
	sub	sp,sp,#4       ;reserved for PC
	stmfd	sp!,{r8-r9}

	ldr	r9,=INTOFFSET
	ldr	r9,[r9]
	ldr	r8,=HandleEINT0
	add	r8,r8,r9,lsl #2
	ldr	r8,[r8]
	str	r8,[sp,#8]
	ldmfd	sp!,{r8-r9,pc}

;=======
; ENTRY
;=======
ResetHandler
	ldr	r0,=WTCON       ;watch dog disable
	ldr	r1,=0x0
	str	r1,[r0]

	ldr	r0,=INTMSK
	ldr	r1,=0xffffffff  ;all interrupt disable
	str	r1,[r0]

	ldr	r0,=INTSUBMSK
	ldr	r1,=0x7fff		;all sub interrupt disable
	str	r1,[r0]

	[ {TRUE}
	; GPBDAT = (rGPFDAT & ~(0xf<<4)) | ((~data & 0xf)<<4);
	; Led_Display
	ldr	r0,=GPBCON
	ldr	r1,=0x00555555
	str	r1,[r0]
	ldr	r0,=GPBDAT
	ldr	r1,=0x07fe
	str	r1,[r0]
	]
	
	

	;To reduce PLL lock time, adjust the LOCKTIME register.
	ldr	r0,=LOCKTIME
	ldr	r1,=0xffffff
	str	r1,[r0]

    [ PLL_ON_START
	; Added for confirm clock divide. for 2440.
	; Setting value Fclk:Hclk:Pclk
	ldr	r0,=CLKDIVN
	ldr	r1,=CLKDIV_VAL		; 0=1:1:1, 1=1:1:2, 2=1:2:2, 3=1:2:4, 4=1:4:4, 5=1:4:8, 6=1:3:3, 7=1:3:6.
	str	r1,[r0]
	
	;[ CLKDIV_VAL>1 		; means Fclk:Hclk is not 1:1.
	;bl MMU_SetAsyncBusMode
	;|
	;bl MMU_SetFastBusMode	; default value.
	;]
	
	;Configure UPLL
	ldr	r0,=UPLLCON
	ldr	r1,=((U_MDIV<<12)+(U_PDIV<<4)+U_SDIV)  
	str	r1,[r0]
	nop	; Caution: After UPLL setting, at least 7-clocks delay must be inserted for setting hardware be completed.
	nop
	nop
	nop
	nop
	nop
	nop
	;Configure MPLL
	ldr	r0,=MPLLCON
	ldr	r1,=((M_MDIV<<12)+(M_PDIV<<4)+M_SDIV)  ;Fin=16.9344MHz
	str	r1,[r0]
    ]

	;Check if the boot is caused by the wake-up from SLEEP mode.
	ldr	r1,=GSTATUS2
	ldr	r0,[r1]
	tst	r0,#0x2
	;In case of the wake-up from SLEEP mode, go to SLEEP_WAKEUP handler.
	bne	WAKEUP_SLEEP
	
	

	EXPORT StartPointAfterSleepWakeUp
StartPointAfterSleepWakeUp

	
	;Set memory control registers
 	adr	r0,SMRDATA
	ldr	r1,=BWSCON	;BWSCON Address
	add	r2, r0, #52	;End address of SMRDATA

	
0
	ldr	r3, [r0], #4
	str	r3, [r1], #4
	cmp	r2, r0
	bne	%B0
	
	


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;       When EINT0 is pressed,  Clear SDRAM 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; check if EIN0 button is pressed

    ldr	r0,=GPFCON
	ldr	r1,=0x0
	str	r1,[r0]
	ldr	r0,=GPFUP
	ldr	r1,=0xff
	str	r1,[r0]

	ldr	r1,=GPFDAT
	ldr	r0,[r1]
       bic	r0,r0,#(0x1e<<1)  ; bit clear
	tst	r0,#0x1
	bne %F1
	
	

; Clear SDRAM Start
  
	ldr	r0,=GPFCON
	ldr	r1,=0x55aa
	str	r1,[r0]
;	ldr	r0,=GPFUP
;	ldr	r1,=0xff
;	str	r1,[r0]
	ldr	r0,=GPFDAT
	ldr	r1,=0x0
	str	r1,[r0]	;LED=****

	mov r1,#0
	mov r2,#0
	mov r3,#0
	mov r4,#0
	mov r5,#0
	mov r6,#0
	mov r7,#0
	mov r8,#0
	
	ldr	r9,=0x4000000   ;64MB
	ldr	r0,=0x30000000
0	
	stmia	r0!,{r1-r8}
	subs	r9,r9,#32 
	bne	%B0

;Clear SDRAM End

1

 		;Initialize stacks
	bl	InitStacks


  	; Setup IRQ handler
	ldr	r0,=HandleIRQ       ;This routine is needed
	;ldr	r1,=IsrIRQ	  ;if there isn''t 'subs pc,lr,#4' at 0x18, 0x1c
	ldr	r1, =OS_CPU_IRQ_ISR ;modify by txf, for ucos 
	str	r1,[r0]
	
   	
	
	
;Check boot mode
	
    ldr	r0, =BWSCON
	ldr	r0, [r0]
	bic r0,r0, # 0xfffffffc
	cmp	r0, #0		         ;OM[1:0] != 0, NOR FLash boot
	bne	on_the_ram		;don''t read nand flash
;===========================================================
copy_myself				;boot from nand flash
	mov	r5, #NFCONF
	ldr	r0,	=(1<<12)|(4<<8)|(1<<4)|(0<<0)
	str	r0,	[r5]
	
	ldr	r0,	=(0<<13)|(0<<12)|(0<<10)|(0<<9)|(0<<8)|(1<<6)|(1<<5)|(1<<4)|(1<<1)|(1<<0);
	str	r0,	[r5,#0x04]
	
	
	bl	ReadNandID
	mov	r6, #0
	ldr	r0, =0xec73
	cmp	r5,	r0
	beq	%F1
	ldr	r0, =0xec75
	cmp	r5, r0
	beq	%F1
	mov	r6, #1
1	
	bl	ReadNandStatus
	
	mov	r8, #0
	ldr	r9, =__ENTRY
2	
	ands	r0, r8, #0x1f
	bne		%F3
	mov		r0, r8
	bl		CheckBadBlk
	cmp		r0, #0
	addne	r8, r8, #32
	bne		%F4
3	
	mov	r0, r8
	mov	r1, r9
	bl	ReadNandPage
	add	r9, r9, #512
	add	r8, r8, #1
4	
	cmp	r8, #5120 ;copy to sdram 
	bcc	%B2
	
	mov	r5, #NFCONF			;DsNandFlash
	ldr	r0, [r5,#0x04]
	orr	r0, r0, #0x01
	str	r0, [r5,#0x04]
	
	ldr	pc, =on_the_ram     ;jump to the sdram
	

on_the_ram
	;Copy and paste RW data/zero initialized data
	ldr	r0, =|Image$$RO$$Limit| ; Get pointer to ROM data
	ldr	r1, =|Image$$RW$$Base|  ; and RAM copy
	ldr	r3, =|Image$$ZI$$Base|

	;Zero init base => top of initialised data
	cmp	r0, r1      ; Check that they are different
	beq	%F2
1
	cmp	r1, r3      ; Copy init data
	ldrcc	r2, [r0], #4    ;--> LDRCC r2, [r0] + ADD r0, r0, #4
	strcc	r2, [r1], #4    ;--> STRCC r2, [r1] + ADD r1, r1, #4
	bcc	%B1
2
	ldr	r1, =|Image$$ZI$$Limit| ; Top of zero init segment
	mov	r2, #0
3
	cmp	r3, r1      ; Zero init
	strcc	r2, [r3], #4
	bcc	%B3


    [ :LNOT:THUMBCODE
 		bl	Main	;Don''t use main() because ......
 		b	.
    ]

    [ THUMBCODE	 ;for start-up code for Thumb mode
 		orr	lr,pc,#1
 		bx	lr
 		CODE16
 		bl	Main	;Don''t use main() because ......
 		b	.
		CODE32
    ]



SMRDATA DATA
; Memory configuration should be optimized for best performance
; The following parameter is not optimized.
; Memory access cycle parameter strategy
; 1) The memory settings is  safe parameters even at HCLK=75Mhz.
; 2) SDRAM refresh period is for HCLK<=75Mhz.

	DCD (0+(B1_BWSCON<<4)+(B2_BWSCON<<8)+(B3_BWSCON<<12)+(B4_BWSCON<<16)+(B5_BWSCON<<20)+(B6_BWSCON<<24)+(B7_BWSCON<<28))
	DCD ((B0_Tacs<<13)+(B0_Tcos<<11)+(B0_Tacc<<8)+(B0_Tcoh<<6)+(B0_Tah<<4)+(B0_Tacp<<2)+(B0_PMC))   ;GCS0
	DCD ((B1_Tacs<<13)+(B1_Tcos<<11)+(B1_Tacc<<8)+(B1_Tcoh<<6)+(B1_Tah<<4)+(B1_Tacp<<2)+(B1_PMC))   ;GCS1
	DCD ((B2_Tacs<<13)+(B2_Tcos<<11)+(B2_Tacc<<8)+(B2_Tcoh<<6)+(B2_Tah<<4)+(B2_Tacp<<2)+(B2_PMC))   ;GCS2
	DCD ((B3_Tacs<<13)+(B3_Tcos<<11)+(B3_Tacc<<8)+(B3_Tcoh<<6)+(B3_Tah<<4)+(B3_Tacp<<2)+(B3_PMC))   ;GCS3
	DCD ((B4_Tacs<<13)+(B4_Tcos<<11)+(B4_Tacc<<8)+(B4_Tcoh<<6)+(B4_Tah<<4)+(B4_Tacp<<2)+(B4_PMC))   ;GCS4
	DCD ((B5_Tacs<<13)+(B5_Tcos<<11)+(B5_Tacc<<8)+(B5_Tcoh<<6)+(B5_Tah<<4)+(B5_Tacp<<2)+(B5_PMC))   ;GCS5
	DCD ((B6_MT<<15)+(B6_Trcd<<2)+(B6_SCAN))    ;GCS6
	DCD ((B7_MT<<15)+(B7_Trcd<<2)+(B7_SCAN))    ;GCS7
	DCD ((REFEN<<23)+(TREFMD<<22)+(Trp<<20)+(Trc<<18)+(Tchr<<16)+REFCNT)

	DCD 0x32	    ;SCLK power saving mode, BANKSIZE 128M/128M

	DCD 0x30	    ;MRSR6 CL=3clk
	DCD 0x30	    ;MRSR7 CL=3clk

;function initializing stacks
InitStacks
	;Don''t use DRAM,such as stmfd,ldmfd......
	;SVCstack is initialized before
	;Under toolkit ver 2.5, 'msr cpsr,r1' can be used instead of 'msr cpsr_cxsf,r1'
	mrs	r0,cpsr
	bic	r0,r0,#MODEMASK
	orr	r1,r0,#UNDEFMODE|NOINT
	msr	cpsr_cxsf,r1		;UndefMode
	ldr	sp,=UndefStack		; UndefStack=0x33FF_5C00

	orr	r1,r0,#ABORTMODE|NOINT
	msr	cpsr_cxsf,r1		;AbortMode
	ldr	sp,=AbortStack		; AbortStack=0x33FF_6000

	orr	r1,r0,#IRQMODE|NOINT
	msr	cpsr_cxsf,r1		;IRQMode
	ldr	sp,=IRQStack		; IRQStack=0x33FF_7000

	orr	r1,r0,#FIQMODE|NOINT
	msr	cpsr_cxsf,r1		;FIQMode
	ldr	sp,=FIQStack		; FIQStack=0x33FF_8000

	bic	r0,r0,#MODEMASK|NOINT
	orr	r1,r0,#SVCMODE
	msr	cpsr_cxsf,r1		;SVCMode
	ldr	sp,=SVCStack		; SVCStack=0x33FF_5800

	;USER mode has not be initialized.

	mov	pc,lr
	;The LR register won''t be valid if the current mode is not SVC mode.
	

;=============================================================
;Nand Flash
;
;=============================================================
ReadNandID
	mov		 r7,#NFCONF	
	ldr      r0,[r7,#4]		;NFChipEn();
	bic      r0,r0,#0x02
	str      r0,[r7,#4]	
	
	mov      r0,#0x90		;WrNFCmd(RdIDCMD);
	strb     r0,[r7,#8]	    ;NFCMD
	mov      r4,#0			;WrNFAddr(0);
	strb     r4,[r7,#0x0c]	;NFADDR
1							;while(NFIsBusy());
	ldr      r0,[r7,#0x20]	;NFSTAT
	tst      r0,#1
	beq      %B1
	ldrb     r0,[r7,#0x10]	;NFDATA id  = RdNFDat()<<8;
	mov      r0,r0,lsl #8	
	ldrb     r1,[r7,#0x10]	;id |= RdNFDat();
	orr      r5,r1,r0
		
	ldr      r0,[r7,#4]		;NFChipDs();
	orr      r0,r0,#0x02
	str      r0,[r7,#4]	
	mov		 pc,lr	
	
ReadNandStatus
	mov		 r7,#NFCONF
	ldr      r0,[r7,#4]		;NFChipEn();
	bic      r0,r0,#0x02
	str      r0,[r7,#4]
	
	mov      r0,#0x70		;WrNFCmd(QUERYCMD);
	strb     r0,[r7,#8]	    ;NFCMD
	ldrb     r1,[r7,#0x10]	;r1 = RdNFDat();
	
	ldr      r0,[r7,#4]		;NFChipDs();
	orr      r0,r0,#0x02
	str      r0,[r7,#4]
	mov		 pc,lr

WaitNandBusy
	mov      r0,#0x70		;WrNFCmd(QUERYCMD);
	mov      r1,#NFCONF
	strb     r0,[r1,#8]     ;NFCMD
1							;while(!(RdNFDat()&0x40));	
	ldrb     r0,[r1,#0x10]  ;NFDATA
	tst      r0,#0x40
	beq		 %B1
	mov      r0,#0			;WrNFCmd(READCMD0);
	strb     r0,[r1,#8]
	mov      pc,lr

CheckBadBlk
	mov		r7, lr
	mov		r5, #NFCONF
	
	bic		r0, r0, #0x1f	;addr &= ~0x1f;
	ldr      r1,[r5,#4]		;NFChipEn()
	bic      r1,r1,#0x02
	str      r1,[r5,#4]	

	mov      r1,#0x50		;WrNFCmd(READCMD2)
	strb     r1,[r5,#8]	    ;NFCMD
	mov		 r1, #6
	strb     r1,[r5,#0x0c]		;WrNFAddr(6)
	strb     r0,[r5,#0x0c]		;WrNFAddr(addr)
	mov      r1,r0,lsr #8	;WrNFAddr(addr>>8)
	strb     r1,[r5,#0x0c]	
	cmp      r6,#0			;if(NandAddr)		
	movne    r0,r0,lsr #16	;WrNFAddr(addr>>16)
	strneb   r0,[r5,#0x0c]
	
	bl		WaitNandBusy	;WaitNFBusy()

	ldrb	r0, [r5,#0x10]	;RdNFDat()
	sub		r0, r0, #0xff
	
	mov      r1,#0			;WrNFCmd(READCMD0)
	strb     r1,[r5,#8]	
	
	ldr      r1,[r5,#4]		;NFChipDs()
	orr      r1,r1,#0x02
	str      r1,[r5,#4]
	
	mov		pc, r7
	
ReadNandPage
	mov		 r7,lr
	mov      r4,r1
	mov      r5,#NFCONF

	ldr      r1,[r5,#4]		;NFChipEn()
	bic      r1,r1,#0x02  
	str      r1,[r5,#4]	

	mov      r1,#0			;WrNFCmd(READCMD0)
	strb     r1,[r5,#8]	
	strb     r1,[r5,#0x0c]		;WrNFAddr(0)
	strb     r0,[r5,#0x0c]		;WrNFAddr(addr)
	mov      r1,r0,lsr #8	;WrNFAddr(addr>>8)
	strb     r1,[r5,#0x0c]	
	cmp      r6,#0			;if(NandAddr)		
	movne    r0,r0,lsr #16	;WrNFAddr(addr>>16)
	strneb   r0,[r5,#0x0c]
	
	ldr      r0,[r5,#0]		;InitEcc()
	orr      r0,r0,#0x0010
	str      r0,[r5,#0]	
	
	bl       WaitNandBusy	;WaitNFBusy()
	
	mov      r0,#0			;for(i=0; i<512; i++)
1
	ldrb     r1,[r5,#0x10]	;buf[i] = RdNFDat()
	strb     r1,[r4,r0]
	add      r0,r0,#1
	bic      r0,r0,#0x10000
	cmp      r0,#0x200
	bcc      %B1
	
	ldr      r0,[r5,#4]		;NFChipDs()
	orr      r0,r0,#0x02
	str      r0,[r5,#4]
		
	mov		 pc,r7	
;=====================================================================
; Clock division test
; Assemble code, because VSYNC time is very short
;=====================================================================
	EXPORT CLKDIV124
	EXPORT CLKDIV144
	
CLKDIV124
	
	ldr     r0, = CLKDIVN
	ldr     r1, = 0x3		; 0x3 = 1:2:4
	str     r1, [r0]
;	wait until clock is stable
	nop
	nop
	nop
	nop
	nop

	ldr     r0, = REFRESH
	ldr     r1, [r0]
	bic		r1, r1, #0xff
	bic		r1, r1, #(0x7<<8)
	orr		r1, r1, #0x470	; REFCNT135
	str     r1, [r0]
	nop
	nop
	nop
	nop
	nop
	mov     pc, lr

CLKDIV144
	ldr     r0, = CLKDIVN
	ldr     r1, = 0x4		; 0x4 = 1:4:4
	str     r1, [r0]
;	wait until clock is stable
	nop
	nop
	nop
	nop
	nop

	ldr     r0, = REFRESH
	ldr     r1, [r0]
	bic		r1, r1, #0xff
	bic		r1, r1, #(0x7<<8)
	orr		r1, r1, #0x630	; REFCNT675 - 1520
	str     r1, [r0]
	nop
	nop
	nop
	nop
	nop
	mov     pc, lr


	LTORG




	ALIGN

	AREA RamData, DATA, READWRITE

	^   _ISR_STARTADDRESS		; _ISR_STARTADDRESS=0x33FF_FF00
HandleReset 	#   4
HandleUndef 	#   4
HandleSWI		#   4
HandlePabort    #   4
HandleDabort    #   4
HandleReserved  #   4
HandleIRQ		#   4
HandleFIQ		#   4

;Don''t use the label 'IntVectorTable',
;The value of IntVectorTable is different with the address you think it may be.
;IntVectorTable
;@0x33FF_FF20
HandleEINT0		#   4
HandleEINT1		#   4
HandleEINT2		#   4
HandleEINT3		#   4
HandleEINT4_7	#   4
HandleEINT8_23	#   4
HandleCAM		#   4		; Added for 2440.
HandleBATFLT	#   4
HandleTICK		#   4
HandleWDT		#   4
HandleTIMER0 	#   4
HandleTIMER1 	#   4
HandleTIMER2 	#   4
HandleTIMER3 	#   4
HandleTIMER4 	#   4
HandleUART2  	#   4
;@0x33FF_FF60
HandleLCD 		#   4
HandleDMA0		#   4
HandleDMA1		#   4
HandleDMA2		#   4
HandleDMA3		#   4
HandleMMC		#   4
HandleSPI0		#   4
HandleUART1		#   4
HandleNFCON		#   4		; Added for 2440.
HandleUSBD		#   4
HandleUSBH		#   4
HandleIIC		#   4
HandleUART0 	#   4
HandleSPI1 		#   4
HandleRTC 		#   4
HandleADC 		#   4
;@0x33FF_FFA0
	END
