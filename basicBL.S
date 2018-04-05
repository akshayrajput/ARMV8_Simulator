.global _start

_start:

	bl target
	mov X1, #2

target:
	mov X0, #1 //check contents of X30 (should hold return address)
	RET
	
	
	
	
	
	
	

	

	
	
	
	