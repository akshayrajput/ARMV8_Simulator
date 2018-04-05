mov w1, #10
mov x2, #32
str w1, [x2], #1
mov x4, #32
ldr w3,[x4],#1
cmp w1,w3
nop
