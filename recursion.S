.global _start

_start:

	bl f1
	mov x1, #2	//if you get to this instruction then give the team a cookie

f1:
	sub sp, sp, #-8	
	str X30, [SP] //save return address onto stack

	bl f2
	ldr X30, [SP]
	add sp, sp, #8
	RET

f2:	
	mov x0, #1 //check contents of stack for saved return address of (pointing to mov x1, #2)
	RET
	
	
	
	
	

	

	
	
	
	
