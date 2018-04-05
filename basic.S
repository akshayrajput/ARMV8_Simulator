.global _start

_start:

	//Testing ADD/ADDS shifted register mode
	mov X0, #1
	mov X1, #2
	add w3, w1, w0, LSL 1 	//L shift w0 by 1, w3 = 4,
	add X3, X1, X0, LSR 63  //R shift w0 by 63, w3 = 2
	mov X0, #-2
	mov X1, #1
	add X3, X1, X0, ASR 1   //AR shift w0 by 1, w3 = 0
	//check CPSR register value
	adds X3, X1, X0, ASR 1   //AR shift w0 by 1, w3 = 0
	//check CPSR register [Emulator shows cpsr=0x60..] [Z should be set]

	//Testing ADD/ADDS extended register mode
	mov W0, #1	//Lower 32 bits must be 0x1
	add X3, X1, W0, SXTX //Sign extend W0 to 64 bits, X3 = 2

	adr X4, _start //X4=4194516
	ADRP X4, _start //X4=4194304

	
	
	
	
	
	

	

	
	
	
	