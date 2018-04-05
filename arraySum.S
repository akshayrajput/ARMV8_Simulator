.global _start

_start:

ldr     X1, #0
mov     w0, #0
mov     w2, #3

loop:
	ldr w4, [X1]
	add w0, w0, w4
	add X1, X1, #4	
	sub w2, w2, #1
	cmp w2, #0
	b.NE loop
	
b       .            /* Infinite loop - value of W0 should be 6 */ 

arr:
  .word 1
  .word 2
  .word 3
	
	
	
	

	

	
	
	
	
