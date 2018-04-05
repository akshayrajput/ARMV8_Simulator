mov w1,#6
mov w2,#5
and w3,w1,w2
mov w1,#3

b _lab
mov w1,#2
add w2,w1,#4
_lab:add w2,w1,#3
