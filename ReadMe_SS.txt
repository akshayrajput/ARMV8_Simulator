Simulo - armv8 simulator
================================================
BUILD
----------------
run build.sh to build the simulator.

RUN
----------------

ARM binary should be in the same folder of the folder of simulo.
Run  run.sh <binary-file>
We can run in two mode
1. simulo
To run the simulator write in terminal './simulo' it will run the loaded binary.

2. simulo debug
To run in debug mode -  './simulo debug'

debug mode supports the following command.
1. print or p : to print the registers
2. next or n: to run next line
3. break or b:to set breakpoint of memory address
4. quit or q: it exits the program.
5. run or r: it run the program until next breakpoint hit or the program exits.
6. help or h :it shows the help menu
7. del : delete breakpoint

INSTRUCTIONS IMPLEMENTED
-------------------------------
MOV
ADD
ADDS
SUB
SUBS
ADR
ADRP
B
BL
B.{cond}
LDR
LDP
STR
STP
NOP
CBZ
CBNZ
CMP
ASR
LSL
LSR
AND
RET

CREDITS
---------
Akshay Rajput

