#include"simulo.h"
#include"mem.h"
#include"loader.h"
#include"instructions.cpp"
void initMem(uint64_t start)
{
	REP(i,0,4095)
	{
		Memory[i].data = 0;
		Memory[i].access = false;
		Memory[i].addr = start;
		start+= 1 ;//each location is of size 64 bits - 8 bytes
		breakpt[i] = false;
	}

	REP(i,0,31)
	{
		R[i].setData(0);

	}
}

int addrToIndex(char* addr)
{
	//TODO - take the hex-address and put in long
	uint64_t x = strtoul(addr,NULL,16);
	//TODO - make the index equivalent using above

	int i = x - Memory[0].addr;

	return i;
}

void printMem(uint64_t addr,int off,char c)
{
	int startind = addr - Memory[0].addr;
	
	int endind = startind + off; 

	assert(c == 'x' || c == 'd');

	REP(i,startind,endind-1)
		if(c == 'd')
			printf("%d\n",Memory[i].getData());
		else if(c == 'x')
			printf("%x\n",Memory[i].getData());
}

void printRegMem(char* arg)
{
	//TODO - parse args
	while(*arg == ' ')arg++;
	
	char c = *arg;
	arg++ ;
	//TODO - if x or d then print register
	while(*arg == ' ') arg++ ;
		
	if(c == 'x' || c == 'd')
	{
		assert(*arg == 'R' || *arg == 'r');
		arg++;
		while(*arg == ' ') arg++ ;

		int regno = (int)strtol(arg,NULL,10);
		assert(regno >= 0 && regno <= 31);

		if(c == 'x')
			printf("0x%02lx\n",R[regno].getData());
		else if(c == 'd')
			printf("%ld\n",R[regno].getData());
	}
	//TODO- else print memory
	else
	{
		assert(isdigit(c));
		int n = c - '0';
		while(isdigit(*arg))
		 {
			 n = n*10 + (*arg - '0') ;
			 arg++;
		 }

		while(*arg == ' ')arg++;
		 assert(*arg == 'w' || *arg == 'b' || *arg == 'd' );
		
		int offset;
		if(*arg == 'w')
			offset = 4;
		else if(*arg == 'd')
			offset = 8;
		else if(*arg == 'b')
			offset = 1;
		
		arg++;
		while(*arg == ' ') arg++;

		assert(*arg == 'x' || *arg == 'd');
		c = *arg;

		arg++;

		while(*arg == ' ')arg++;

		uint64_t addr = strtoul(arg,NULL,16);
		printMem(addr,n * offset,c);
		
	}
}

void setBreak(char* arg)
{
	//TODO -set bp_flag at particular address
	while(*arg == ' ')arg++;
	int ind = addrToIndex(arg);
	breakpt[ind] = true;
}

void delBreak(char* arg)
{
	//TODO -set bp_flag at particular address
	while(*arg == ' ')arg++;
	int ind = addrToIndex(arg);
	breakpt[ind] = false;
}

void show_prompt()
{
	
	char inp[50],comm[20],arg[20],*split;

	while(1)
	{
		printf("DEBUG-PROMPT:>");
		fgets(inp,50,stdin);
		split = inp;
		while(*split != ' ' && *split != '\n' ) { split++;}

		*split = '\0';
		strcpy(comm,inp);
		split++;

		while(*split == ' ') split++ ;

		strcpy(arg, split);
		
		if(strcmp(comm,"p") == 0 || strcmp(comm,"print")== 0)
			printRegMem(arg);

		else if(strcmp(comm,"b")==0 || strcmp(comm,"break")==0 )
			setBreak(arg);

		else if(strcmp(comm,"d")==0 || strcmp(comm,"del")==0 )
			delBreak(arg);
	
		else if(strcmp(comm,"r")==0 || strcmp(comm,"run")==0 )
		{	
			debug_prompt = false;
			return;
		}

		else if(strcmp(comm,"q")==0 || strcmp(comm,"quit")==0 )
		{
			debug_prompt = false;
			printf("Exiting simulo...\n");
			exit(0);
			return;
		}

		else if(strcmp(comm,"n")==0 || strcmp(comm,"next")==0 )
		{
			return;
		}
		else
			printf("Please enter a valid command\n");
	}

}


void fetch()
{
	uint64_t addr = PC.getData();
	int i = addr - Memory[0].addr; 
	printf("[log]-fetching instruction\n");
	if(debug_prompt)
	{
		printf("DEBUG-mode enabled\n");
		show_prompt();
	}

	if(breakpt[i])
	{
		printf("Break point at address - %lx\n",addr);
		show_prompt();
	}
		//TODO - read the memory
	uint64_t w = Memory[i].getData()<<24; i++;
	uint64_t x = Memory[i].getData()<<16; i++;
	uint64_t y = Memory[i].getData()<<8; i++;
	uint64_t z = Memory[i].getData(); i++;


	//TODO - take data to IR

	IR.setData(w|x|y|z);

	PC.setData(addr + 4 );
	printf("[log]-done fetching instruction\n");

}

void decode()
{
    int sf = (IR.getLowerData() & SF_MASK)>>31;
    int type_inst = (IR.getLowerData() & TYPE_MASK) >>27;//instruction group
    int sw = 0;
    
    if(type_inst == 2)  //operand data processing immediate
    {
	sw = 0;
	
        int inst = (IR.getData() & INST_IMM_TYPE) >> 23;

        if(inst == 0 || inst == 1) // PC relative addressing
        {
            printf("[log] - PC relative\n");
        }
        else if(inst == 2 || inst == 3) // Add or subtract
        {
		int opc = (IR.getLowerData() & 0x60000000)>>29;//op + S
		int op1 = IR.getLowerData() & 0x0000001f ;//Rd
		int op2 = (IR.getLowerData() & 0x000003e0) >> 5 ;//Rn
		int op3 = (IR.getLowerData() & 0x003ffc00)>>10;//imm10
		if(opc == 0)
		{
			// TODO - add
			ADD(sf,sw,op1,op2,op3);
		}
		else if(opc == 1)
		{
			//TODO - adds
		}
		else if(opc == 2)
		{
			//TODO - sub
			SUB(sf,sw,op1,op2,op3);
			
		}
		else if(opc == 3)
		{
			//TODO - subs
		}
        }
        
        else if(inst == 4)  //Logical 
        {
       		//only AND 
		int op1 = IR.getLowerData() & 0x0000001f ;//Rd
		int op2 = (IR.getLowerData() & 0x000003e0) >> 5 ;//Rn
		int op3 = (IR.getLowerData() & 0x04000000) >> 22;//N
		int op4 = (IR.getLowerData() & 0x0000fc00 ) >> 10 ;//imms
		int op5 = (IR.getLowerData() & 0x003f0000)>>16;//immr

		AND(sf,sw,op1,op2,0,op3,op4,op5);
        }
        
        else if(inst == 5)  //Move wide
        {
		printf("[log] - move instruction\n");
		int op1 = IR.getLowerData() & 0x0000001f ;//Rd
		int op2 = (IR.getLowerData() & 0x001fffe0 )>> 5; //imm16
		MOV(sf, sw,op1,op2);
       		 
        }
        
        else if(inst == 6)  //Bit field
        {

		printf("[log] - lsr|lsl|asr instruction\n");
		int opc = (IR.getLowerData() & 0x60000000)>>29;//op + S
		int op1 = IR.getLowerData() & 0x0000001f ;//Rd
		int op2 = (IR.getLowerData() & 0x000003e0) >> 5 ;//Rn
		int op3 = (IR.getLowerData() & 0x04000000) >> 22;//N
		int op4 = (IR.getLowerData() & 0x0000fc00 ) >> 10 ;//imms
		int op5 = (IR.getLowerData() & 0x003f0000)>>16;//immr

		if(opc == 0)
		{
			ASR(sf,sw,op1,op2,op5);
		}

		else if(opc == 2)
		{
			if(op4  == 31 || op4 == 63 )
			{
				printf("[log] - lsr instruction\n");
			 	LSR(sf,sw,op1,op2,op5);

			}

			else
			{
			 	printf("[log] - lsl instruction");
				LSL(sf,sw,op1,op2,op5);

			} 
		}
        }
        
        else if (inst == 7) //Extract
        {
        
        }
        
    }
    
    else if (type_inst == 1 || type_inst == 3)  //operand data processing register
    {
	 sw = 1;
        int inst = (IR.getLowerData() & INST_REG_TYPE)>>21;

        if(inst >= 80 && inst <=87)
        {
	   int opc = (IR.getLowerData() & 0x60000000)>>29;//opc
	   int op1 = IR.getLowerData() & 0x0000001f ;//Rd
	   int op2 = (IR.getLowerData() & 0x000003e0) >> 5 ;//Rn
	   int op3 = (IR.getLowerData() & 0x001f0000)>>16; //Rm
	   int op4 = (IR.getLowerData() & 0x0000fc00)>>10;//imm6


            printf("[log] - Logical shifted register instruction\n");

	    if(opc == 0)
	    {
		    printf("[log]- AND instruction\n");
		    AND(sf,sw,op1,op2,op3,0,0,0);
	    }
	    else if(opc == 1)
	    {
		    printf("[log]- MOV instruction\n");
		    MOV(sf, sw,op1,op3);

	    }


        }
        
        else if(inst == 88 || inst == 90 || inst == 92 || inst == 94)
        {
            printf("[log] - Add/ sub shifted register instruction\n");
		int opc = (IR.getLowerData() & 0x60000000)>>29;//op + S
		int op1 = IR.getLowerData() & 0x0000001f ;//Rd
		int op2 = (IR.getLowerData() & 0x000003e0) >> 5 ;//Rn
		int op3 = (IR.getLowerData() & 0x001f0000)>>16; //Rm
		int op4 = (IR.getLowerData() & 0x0000fc00)>>10;//imm6
		if(opc == 0)
		{
			// TODO - add
			ADD(sf,sw,op1,op2,op3);

		}
		else if(opc == 1)
		{
			//TODO - adds
		}
		else if(opc == 2)
		{
			//TODO - sub
			SUB(sf,sw,op1,op2,op3);
		}
		else if(opc == 3)
		{
			//TODO - subs
		}

        }
        
        else if(inst == 89 || inst == 91 || inst == 93 || inst == 95)
        {
            printf("[log] - Add/ sub extended register instruction\n");
        }
        
        else if(inst == 208)
        {
            printf("[log ] - Add/ sub with instruction\n");
        }
        
        else if(inst == 210)
        {
            printf("[log ] - condition compare register or immediate instruction\n");
        }
        
        else if(inst == 212)
        {
            printf("[log] - condition select instruction\n");
        }
        
          
    }
    
   
}

int main(int argc, char* argv[])
{

	int start_ind = 0;
	uint64_t start_addr ;
	char endian;
	debug_prompt = false;
	if(argc > 1)
		if(strcmp(argv[1],"debug") == 0)
	 		debug_prompt = true;
	FILE* info = fopen("info.txt","r");
	fscanf(info,"%lx %c",&start_addr,&endian);
	fclose(info);

	initMem(start_addr);
	printf("[log]- Memory initialised ");
	Loader loader("inst.txt");
	
	int x = loader.loadmem(start_ind,Memory,endian);
	printf("[log]-Hex file loaded\n");
	//init memory and breakpoints
	PC.setData(Memory[start_ind].addr);

	int i = start_ind;
	while(i < x)
	{
		
		fetch();
		decode();
		i += 4;
	}

	printf("[log]-Execution completed!\n");			
	return 0;
}
