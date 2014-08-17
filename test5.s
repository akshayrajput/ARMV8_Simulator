mov w1,#2
mov w3,#3
bl _subr
add w2,w1,w3
_subr:add w3,w1,#3
ret
