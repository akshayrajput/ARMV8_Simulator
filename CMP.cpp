void CMP()
{
    printf("[log] - CMP instruction\n");
    int sf = IR.getLowerData() & 0x80000000;
    int op = IR.getLowerData() & 0x40000000;
    int S = IR.getLowerData() & 0x20000000;
    int shift = (IR.getLowerData()  & 0x00c00000) >> 22;
    int imm12 = (IR.getLowerData()  & 0x003ffc00) >> 10;
    int mod = (IR.getLowerData()  & 0x1f000000) >> 24;
    int rn = (IR.getLowerData()  & 0x000003e0) >> 5;
    int rd = IR.getLowerData()  & 0x0000001f;

    if(mod == 17)   //immediate
    {
	printf("[log] - CMP instruction immediate\n");
        uint64_t imm = imm12;
        if(shift == 1)
        {
            imm = imm12 << 12;
        }
        
        if(sf)
        {
            uint64_t dat = R[rn].getData();
            if((dat > 0 && imm < 0 && (dat-imm) < 0) || (dat < 0 && imm > 0 && (dat - imm) > 0))
                OFLAG = true;
            if(OFLAG)
		    printf("Overflow flag set\n");
            CFLAG = (dat <imm);
            if(CFLAG)
		    printf("Carry flag set\n");
            NFLAG = (dat < imm);
            if(NFLAG)
		    printf("Negative flag set\n");
            ZFLAG = (dat == imm);
            if(ZFLAG)
		    printf("Zero flag set\n");
        }
        
        else
        {
            int imm32 = (int)imm;
            int dat = R[rn].getLowerData();
            if((dat > 0 && imm32 < 0 && (dat-imm32) < 0) || (dat < 0 && imm32 > 0 && (dat - imm32) > 0))
                OFLAG = true;
            if(OFLAG)
		    printf("Overflow flag set\n");
            CFLAG = (dat < imm32);
            if(CFLAG)
		    	printf("Carry flag set\n");
		    	
            NFLAG = (dat < imm32);
            
            if(NFLAG)
		    	printf("Negative flag set\n");
		    	
            ZFLAG = (dat == imm32);
            if(ZFLAG)
		    	printf("Zero flag set\n");
        }
    }
    else if(mod == 11)  //extended or register
    {
	printf("[log] - CMP extended/register\n");
        int inst_t = IR.getLowerData() & 0x00200000;
        if(inst_t) //register
        {
            int rm = (IR.getLowerData() & 0x001f0000) >> 16;
            int imm6 = (IR.getLowerData() & 0x0000fc00) >> 10;
            if(sf)  //64 bit registers
            {
                if(shift == 0) //LSL
                {
                    uint64_t rn_data = R[rn].getData();
                    uint64_t rm_data = R[rm].getData();
                    rm_data = rm_data << imm6;
                    
                    if((rn_data > 0 && rm_data < 0 && (rn_data-rm_data) < 0) || (rn_data < 0 && rm_data > 0 && (rn_data - rm_data) > 0))
                OFLAG = true;
        if(OFLAG)
		    printf("Overflow flag set\n");
		    
            CFLAG = (rn_data < rm_data);
	    if(CFLAG)
		    printf("Carry flag set\n");
		    
            NFLAG = (rn_data < rm_data);
	    if(NFLAG)
		    printf("Negative flag set\n");
		    
            ZFLAG = (rn_data == rm_data);
        if(ZFLAG)
		    printf("Zero flag set\n");
        
                }
                
                else if(shift == 1 or shift == 2) // LSR or ASR(in c both are same)
                {
                    uint64_t rn_data = R[rn].getData();
                    uint64_t rm_data = R[rm].getData();
                    rm_data = rm_data >> imm6;
                    
                    if((rn_data > 0 && rm_data < 0 && (rn_data-rm_data) < 0) || (rn_data < 0 && rm_data > 0 && (rn_data - rm_data) > 0))
                OFLAG = true;
            if(OFLAG)
		    printf("Overflow flag set\n");
            CFLAG = (rn_data < rm_data);
		if(CFLAG)
		    printf("Carry flag set\n");

            NFLAG = (rn_data < rm_data);
		if(NFLAG)
		    printf("Negative flag set\n");

            ZFLAG = (rn_data == rm_data);
		if(ZFLAG)
		    printf("Zero flag set\n");

                }
            }
            
            else    //32 bit registers
            {
                if(shift == 0) //LSL
                {
                    uint32_t rn_data = R[rn].getLowerData();
                    uint32_t rm_data = R[rm].getLowerData();
                    rm_data = rm_data << imm6;
                    
                    if((rn_data > 0 && rm_data < 0 && (rn_data-rm_data) < 0) || (rn_data < 0 && rm_data > 0 && (rn_data - rm_data) > 0))
                OFLAG = true;
            
            CFLAG = (rn_data < rm_data);
            NFLAG = (rn_data < rm_data);
            ZFLAG = (rn_data == rm_data);
            if(NFLAG)
		    printf("Negative flag set\n");
		    if(CFLAG)
		    printf("Carry flag set\n");
		    if(ZFLAG)
		    printf("Zero flag set\n");
		    if(OFLAG)
		    printf("Overflow flag set\n");
                }
                
                else if(shift == 1 or shift == 2) // LSR or ASR(in c both are same)
                {
                    uint32_t rn_data = R[rn].getLowerData();
                    uint32_t rm_data = R[rm].getLowerData();
                    rm_data = rm_data >> imm6;
                    
                    if((rn_data > 0 && rm_data < 0 && (rn_data-rm_data) < 0) || (rn_data < 0 && rm_data > 0 && (rn_data - rm_data) > 0))
                OFLAG = true;
            
            CFLAG = (rn_data < rm_data);
            NFLAG = (rn_data < rm_data);
            ZFLAG = (rn_data == rm_data);
            
            if(CFLAG)
		    printf("Carry flag set\n");
		    if(NFLAG)
		    printf("Negative flag set\n");
		    if(ZFLAG)
		    printf("Zero flag set\n");
		    if(OFLAG)
		    printf("Overflow flag set\n");
                }
            }
        }
    }
}
