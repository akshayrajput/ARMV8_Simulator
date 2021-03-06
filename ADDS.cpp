void ADDS()
{
    int sf = IR.getLowerData() & 0x80000000;
    int op = IR.getLowerData() & 0x40000000;
    int S =  IR.getLowerData() & 0x20000000;
    int mod = (IR.getLowerData() & 0x1f000000) >> 24;
    int shift = (IR.getLowerData() & 0x00c00000) >> 22;
    int imm12 = (IR.getLowerData() & 0x003ffc00) >>10;
    int imm6 = (IR.getLowerData() & 0x0000fc00) >>10;
    int rm = (IR.getLowerData() & 0x001f0000) >> 16;
    int rn = (IR.getLowerData() & 0x000003e0) >> 5;
    int rd = (IR.getLowerData() & 0x0000001f);
    bool sub_op = false;
    int64_t imm;
    int amount = imm6;
    
    if(op)  sub_op = true;

    if(rd == 31 && sub_op)
    {
 	    CMP();
	    return;
    }
    if(shift == 0)
    {
        if (sf)
        {
            imm = (uint64_t)imm12;
        }
        else
        {
            imm = imm12;
        }
    }
    
    else if(shift == 1)
    {
        if(sf)
        {
            imm = (uint64_t)imm12;
            imm = imm << 12;
        }
        else
        {
            imm = imm12;
            imm = imm << 12;
        }
    }
    bool setFlag = false;
    if(S == 1) setFlag = true;
    if(mod == 17) // ADDS immediate
    {
        if(sf)  //64 bit
        {
            int carry = 0;
            if(sub_op)
            {
                imm = -imm;
                carry = 0;   
            }
            uint64_t rn_data = R[rn].getData();
            uint64_t dat = rn_data + imm + carry;
            
            
         	if(rn_data > 0 && imm > 0 && dat < 0)
		{
            		OFLAG = true;
		    	printf("[log] - Overflow flag\n");
         	}
        	if(rn_data < 0 && imm < 0 && dat > 0)
		{
        	    OFLAG = true;
			    printf("[log] - Zero flag set\n");
        	}

                ZFLAG = (dat == 0);
                
		if(ZFLAG)
			printf("[log] - Zero flag set\n");
	
                NFLAG = (dat < 0);
		if(NFLAG)
			printf("[log] - Negative flag set\n");
                
                if(!sub_op)
		{	
			CFLAG = rn_data > (0xffffffffffffffff - (imm + carry));
        	}
		else
		{
			CFLAG = rn_data < (-imm);
		}
		if(CFLAG)
			printf("[log] - Carry flag set\n");

            if(rd == 31 && !S)
                R[31].setData(dat);
            else
                R[rd].setData(dat);
        }
        
        else//32 bit
        {
            int carry = 0;
            if(sub_op)
            {
                imm = -imm;
                carry = 0;   
            }
            
            int rn_data = R[rn].getLowerData();
            int dat = rn_data + imm + carry;
            
            
            if(R[rn].getLowerData() > 0 && imm > 0 && dat < 0)
             {
                OFLAG = true;
                printf("[log] - Overflow flag set\n");
             }
            
            if(dat == 0)
            {
                ZFLAG = true;
                printf("[log] - Zero flag set\n");
            }
            if(dat < 0)
            {
                NFLAG = true;
                printf("[log] - Negative flag set\n");
            }
            if(!sub_op)
	      CFLAG = rn_data > (0xffffffff - (imm + carry));
            else
		{
			CFLAG = rn_data < (-imm);
		}


            if(CFLAG)
            	printf("[log] - Carry flag set.\n");
            
            if(rd == 31 && !S)
                R[31].setData(dat);
            else
                R[rd].setData(dat);
        }
    }
    
    if(mod == 11)   //shifted register
    {
	printf("[log] - ADDS register\n");
        if(sf)      //64 bit registers
        {
            uint64_t op1 = R[rn].getData();
            
            uint64_t op2 = R[rm].getData();
            if(shift == 0)
                op2 = op2 << (amount%64);
            else if(shift == 1 && shift == 2)
                op2 = op2 >> (amount%64);
            uint64_t carry = 0;
            if(sub_op)
            {
                op2 = -op2;
                carry = 0;
            }
            
            uint64_t dat = op1 + op2 + carry;
            if(rd == 31 && !S)
                R[31].setData(dat);
            else
                R[rd].setData(dat);
           
            if(op1 > 0 && op2 > 0 && dat < 0)
	    	{
			printf("[log] - Overflow flag set\n");
                OFLAG = true;
            }
            if(dat == 0)
	    	{
			printf("[log] - Zero flag set \n");
                ZFLAG = true;
            }
            if(dat < 0)
	    {
		printf("[log]- Negative flag set\n");
                NFLAG = true;
            }
		if(!sub_op)
            		CFLAG = op1 > (0xffffffffffffffff - (op2 + carry));
		else
		{
			CFLAG = op1 < (-op2);
		}

	    if(CFLAG)
	    {
		printf("[log] -Carry flag set \n");
	    }
        }
       
        else     //32 bit registers
        {
            int op1 = R[rn].getLowerData();
            
            int op2 = R[rm].getLowerData();
            if(shift == 0)
                op2 = op2 << (amount%32);
            else if(shift == 1 && shift == 2)
                op2 = op2 >> (amount%32);
            int carry = 0;
            if(sub_op)
            {
                op2 = ~op2;
                carry = 1;
            }
            
            int dat = op1 + op2 + carry;
            if(rd == 31 && !S)
                R[31].setLowerData(dat);
            else
                R[rd].setLowerData(dat);
           
            if(op1 > 0 && op2 > 0 && dat < 0)
	    {
                OFLAG = true;
		printf("[log] -Overflow flag set \n");

	    }
            if(dat == 0)
	    {
                ZFLAG = true;
		printf("[log] -Zero flag set \n");
	    }

            if(dat < 0)
	    {
                NFLAG = true; 
		printf("[log] -Negative flag set \n");
            }   
	    if(!sub_op)
            	CFLAG = op1 > (0xffffffff - op2);
	    else
	    {
	    	CFLAG = op1<(-op2);
	    }

	    if(CFLAG)
		    printf("[log] - carry flag set");
           
        }
       
    }
    
}
