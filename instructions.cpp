void ADD(int sf, int sw,int RD,int RN,int immRM)
{
	
	//ADD stub
	printf("[log] - add instructions\n");

	assert(RD >= 0 && RD <= 31);
	assert(RN >= 0 && RN <= 31);
	
	//TODO - Add shifted operands also
	if(sf == 1 && sw == 0)
	{
		printf("[log] - adding 64 bit immediate\n");
		uint64_t result = R[RN].getData() + immRM ;
		
		if(result < R[RN].getData() )
		{
			printf("Addition overflow!!\n");
			return;
		}

		R[RD].setData(result);

	}
	else if(sf == 0 && sw == 0)
	{
		printf("[log] - adding 32 bit immediate\n");
		uint32_t result = R[RN].getLowerData() + immRM ;
		
		if(result < R[RN].getLowerData() )
		{
			printf("Addition overflow!!\n");
			return;
		}

		R[RD].setLowerData(result);

	}
	else if(sf == 1 && sw == 1)
	{
		printf("[log] - adding 64 bit register\n");
		assert(immRM >= 0 && immRM <= 31);
		uint64_t result = R[RN].getData() + R[immRM].getData() ;
		
		if(result < R[RN].getData() )
		{
			printf("Addition overflow!!\n");
			return;
		}

		R[RD].setData(result);

	}
	else if(sf == 0 && sw == 1)
	{
		printf("[log] - adding 32 bit register\n");
		assert(immRM >= 0 && immRM <= 31);
		uint32_t result = R[RN].getLowerData() + R[immRM].getData() ;
		
		if(result < R[RN].getLowerData() )
		{
			printf("Addition overflow!!\n");
			return;
		}

		R[RD].setLowerData(result);

	}
}

void ASR(int sf, int sw, int op1, int op2, int  op3 )
{
    if(sf)
    {
        if(sw == 0) //immediate
        {
	   printf("[log] - ASR 64 bit immediate\n");
            uint64_t op2_data = R[op2].getData();
            uint64_t dat;
            if(op2_data < 0)
            {
                dat = op2_data >> op3 | ~(0xffffffffffffffff >> op3);
                R[op1].setData(dat);
            }
            else
            {
                dat = op2_data >> op3;
                R[op1].setData(dat);
            }
            
        }
        
        else //register
        {
            uint64_t op2_data = R[op2].getData();
            uint64_t op3_data = R[op3].getData();
            uint64_t dat;
            if(op2_data < 0)
            {
                dat = op2_data >> op3_data | ~(0xffffffffffffffff >> op3_data);
                R[op1].setData(dat);
            }
            else
            {
                dat = op2_data >> op3_data;
                R[op1].setData(dat);
            }
        }
    }
    
    else    //32 bit registers
    {
        if(sw == 0) //immediate
        {
	    printf("[log] - ASR instruction - 32 bit \n");
            int op2_data = R[op2].getLowerData();
            int dat;
            if(op2_data < 0)
            {
                dat = op2_data >> op3 | ~(0xffffffff >> op3);
                R[op1].setLowerData(dat);
            }
            else
            {
                dat = op2_data >> op3;
                R[op1].setLowerData(dat);
            }
        }
        
        else    //register
        {
            int op2_data = R[op2].getLowerData();
            int op3_data = R[op3].getLowerData();
            int dat;
            if(op2_data < 0)
            {
                dat = op2_data >> op3_data | ~(0xffffffff >> op3_data);
                R[op1].setLowerData(dat);
            }
            else
            {
                dat = op2_data >> op3_data;
                R[op1].setLowerData(dat);
            }
        }
    }
}

void LSL(int sf, int sw,int op1, int op2, int  op3 )
{
	//op1 = RD
	//op2 = RN
	//op3 = immRM
    if(sf)  //64 bit registers
    {
        if(sw == 0) //immediate
        {
   	    printf("[log] - LSL 64 bit immediate\n");
            uint64_t op2_data = R[op2].getData();
            uint64_t dat;
            dat = op2_data << (op3 % 64);
            R[op1].setData(dat);
        }
        
        else    //register
        {
	    printf("[log] - LSL 64 bit register\n");
            uint64_t op2_data = R[op2].getData();
            uint64_t op3_data = R[op3].getData();
            uint64_t dat;
            dat = op2_data << (op3_data % 64);
            R[op1].setData(dat);
        }
    }
    
    else    //32 bit registers
    {
        if(sw == 0) //immediate
        {
	    printf("[log] - LSL 32 bit immediate\n");
            int op2_data = R[op2].getLowerData();
            int dat = op2_data << (op3 % 32);
            R[op1].setLowerData(dat);
        }
        
        else    //register
        {
        	printf("[log] - LSL 32 bit register\n");
            int op2_data = R[op2].getLowerData();
            int op3_data = R[op3].getLowerData();
            int dat = op2_data << (op3_data % 32);
            R[op1].setLowerData(dat);
        }
    }
}

void LSR(int sf, int sw,int op1, int op2, int  op3 )
{
	//op1 - RD , op2 - RN, op3 - immr
    if(sf)  //64 bit registers
    {
        if(sw == 0) //immediate
        {
            uint64_t op2_data = R[op2].getData();
            uint64_t dat;
            dat = op2_data >> (op3 % 64);
            R[op1].setData(dat);
        }
        
        else    //register
        {
            uint64_t op2_data = R[op2].getData();
            uint64_t op3_data = R[op3].getData();
            uint64_t dat;
            dat = op2_data >> (op3_data % 64);
            R[op1].setData(dat);
        }
    }
    
    else    //32 bit registers
    {
        if(sw == 0) //immediate
        {
            int op2_data = R[op2].getLowerData();
            int dat = op2_data >> (op3 % 32);
            R[op1].setLowerData(dat);
        }
        
        else    //register
        {
            int op2_data = R[op2].getLowerData();
            int op3_data = R[op3].getLowerData();
            int dat = op2_data >> (op3_data % 32);
            R[op1].setLowerData(dat);
        }
    }
}

void SUB(int sf, int sw,int op1, int op2, int op3 )
{
	//op1 - RD , op2 - RN , op3 - immRM
    if(sf) //use 64 bit register
    {
        if(sw == 0) //immediate
        {
            printf("[log] - subracting immediate 64 bit\n");
            uint64_t dat;
            dat = R[op2].getData() - op3; 
            R[op1].setData(dat);
        }
        
        if (sw == 1)    //register
        {
            printf("[log] - subracting register 64 bit\n");
            uint64_t dat;
            dat = R[op2].getData() - R[op3].getData();
            R[op1].setData(dat);
        }
    }
    
    else    //use 32 bit register
    {
         if(sw == 0) //immediate
        {
            printf("[log] - subracting immediate 32 bit\n");
            uint64_t dat;
            dat = R[op2].getLowerData() - op3; 
            R[op1].setLowerData(dat);
        }
        
        if (sw == 1)    //register
        {
            printf("[log] - subracting register 32 bit\n");
            int dat;
            dat = R[op2].getLowerData() - R[op3].getLowerData();
            R[op1].setLowerData(dat);
        }
    }
}

void MOV(int sf, int _switch,int op1, int op2 )
{
    if(sf)  //64 bit registers
    {
	
        if(_switch == 0) //immediate
        {
            printf("[log] - mov immediate 64 bit\n");
            R[op1].setData(op2);
        }
        
        else    //register
        {
            printf("[log] - mov register 64 bit\n");
            R[op1].setData(R[op2].getData());
        }
    }
    
    else
    {
        if(_switch == 0) //immediate
        {
			printf("[log] - mov immediate 32 bit\n");
            R[op1].setLowerData(op2);
        }
        
        else    //register
        {
			printf("[log] - mov immediate 32 bit\n");
            R[op1].setLowerData(R[op2].getLowerData());
        }
    }
}

static uint64_t DecodeBitMask(int N, int imms, int immr, int size){
        int len, levels, S, R, diff, esize;

        uint64_t welem = 0;

        /* Finding the highest set bit in N:imms */
        if(N){
                len = 6;
        }
        else{
                imms = ~imms;
                for(int i=5; i>=0; i--){
                        if(imms & (1<<i)){
                                len = i;
                                break;
                        }
                }
                imms = ~imms;
        }
        if(len < 1){
                cout << "Invalid Instruction found" << endl;
        }

        /* caluclating levels value */
        levels = 0;
        for(int i=0; i<len; i++){
                levels = levels << 1;
                levels = (levels | 1) ;
        }

        if((levels & imms) == levels){
                cout << "Invalid Instruction found" << endl;
        }
        S = levels & imms;
        R = levels & immr;
        diff = S - R;
        esize = (1 << len);
        for(int i=0; i<(S+1); i++){
                welem = welem << 1;
                welem = (welem | 1) ;
        }

        for(int i=0; i<R; i++){
                uint64_t lbit = welem & 1;
                welem = welem >> 1;
                if(size == 32){
                        welem = welem & 0xffffffff7fffffff;
                        welem = (welem | (int)((lbit) << 31));
                }
                else{
                        welem = welem & 0x7fffffffffffffff;
                        welem = (welem |(uint64_t) ((lbit) << 63));
                }
        }
        return welem;

}

void AND(int sf, int sw, int op1, int op2, int op3, int N, int imms, int immr)
{
	//op1 - RD,op2 - RN, op3 - RM
    if(sf)
    {
		if(sw == 0)
		{
		    uint64_t imm = DecodeBitMask( N,  imms, immr, 64);
		    uint64_t dat = R[op2].getData() & imm;
		    R[op1].setData(dat);
		}
		
		else
		{
			uint64_t dat = R[op2].getData() & R[op3].getData();
			R[op1].setData(dat);
		}
    }
    else
    {
        if(sw == 0)
        {
      		uint32_t imm = DecodeBitMask(N, imms, immr, 32);
       	 	uint32_t dat = R[op2].getLowerData() & imm;
       	 	R[op1].setLowerData(dat);
       	 }
       	 else
       	 {
       	 	uint32_t dat = R[op2].getLowerData() & R[op3].getLowerData();
       	 	R[op1].setLowerData(dat);
       	 }
    }
}
