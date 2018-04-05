void LDP()
{
    int inst_type = (IR.getLowerData() & 0x01800000) >> 23;
    int opc = (IR.getLowerData() & 0xc0000000) >> 30;
    int L = (IR.getLowerData() & 0x00400000) >> 22;
    int imm7 = (IR.getLowerData() & 0x003f8000) >> 15;
    int rt2 = (IR.getLowerData() & 0x00007c00) >> 10;
    int rn = (IR.getLowerData() & 0x000003e0) >> 5;
    int rt = (IR.getLowerData() & 0x0000001f);
    if(L == 1)  //LOAD LDP
    {
	    printf("[log]-LDP instruction\n");
        if(inst_type == 1)  //post index
        {
          printf("[log]-LDP post index\n");
            if(!opc)    //32 bit registers
            {
                printf("[log]-LDP post index 32\n");
                int imm = imm7 * 4;
                uint64_t addr = R[rn].getData();
                addr -= Memory[0].addr;
                
                int dat = Memory[addr].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 1].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 2].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 3].getData();
                
                int data1 = (int)dat;
                
                dat = 0;
                
                dat = Memory[addr + 4].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 5].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 6].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 7].getData();
                
                int data2 = (int)dat;
                
                R[rt].setLowerData(data1);
                R[rt2].setLowerData(data2);
                
                addr = addr + imm;
                R[rn].setData(addr);
                
            }  
            
            else    //64 bit registers
            {
                printf("[log]-LDP post index 64\n");
                int imm = imm7 * 8;
                uint64_t addr = R[rn].getData();
                addr -= Memory[0].addr;
                
                uint64_t dat = Memory[addr].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 1].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 2].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 3].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 4].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 5].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 6].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 7].getData();
                
                uint64_t data1 = dat;
                
                dat = 0;
                dat =  Memory[addr + 8].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 9].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 10].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 11].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 12].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 13].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 14].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 15].getData();
                
                uint64_t data2 = (int)dat;
                
                R[rt].setData(data1);
                R[rt2].setData(data2);
                
                addr = addr + imm;
                R[rn].setData(addr);
            }         
        }
        
        else if(inst_type == 3) //pre index
        {
            printf("[log]-LDP pre index \n");
            if(!opc)    //32 bit registers
            {
            	printf("[log]-LDP pre index 32\n");
                int imm = imm7 * 4;
                uint64_t addr = R[rn].getData();
                addr = addr + imm;
                R[rn].setData(addr);
                
                addr -= Memory[0].addr;
                
                int dat = Memory[addr].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 1].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 2].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 3].getData();
                
                int data1 = (int)dat;
                
                dat = 0;
                
                dat = Memory[addr + 4].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 5].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 6].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 7].getData();
                
                int data2 = (int)dat;
                
                R[rt].setLowerData(data1);
                R[rt2].setLowerData(data2);
                
            }  
            
            else   //64 bit registers
            {
                printf("[log]-LDP pre index 64\n");
                int imm = imm7 * 8;
                uint64_t addr = R[rn].getData();
                addr = addr + imm;
                R[rn].setData(addr);
                addr -= Memory[0].addr;
                
                uint64_t dat = Memory[addr].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 1].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 2].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 3].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 4].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 5].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 6].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 7].getData();
                
                uint64_t data1 = dat;
                
                dat = 0;
                dat =  Memory[addr + 8].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 9].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 10].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 11].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 12].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 13].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 14].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 15].getData();
                
                uint64_t data2 = dat;
                
                R[rt].setData(data1);
                R[rt2].setData(data2);
            } 
        }
        
        else if(inst_type == 2) //signed offset
        {
          printf("[log]-LDP signed offset\n");
            if(!opc)    //32 bit registers
            {
                printf("[log]-LDP signed offset 32\n");
                uint64_t addr = R[rn].getData();
                int imm = imm7 * 4;
                addr += imm;
                addr -= Memory[0].addr;
                
                int dat = Memory[addr].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 1].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 2].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 3].getData();
                
                int data1 = (int)dat;
                
                dat = 0;
                
                dat = Memory[addr + 4].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 5].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 6].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 7].getData();
                
                int data2 = (int)dat;
                
                R[rt].setLowerData(data1);
                R[rt2].setLowerData(data2);
                
            }
            
            else    //64 bit registers
            {
                printf("[log]-LDP signed offset 64\n");
                uint64_t addr = R[rn].getData();
                int imm = imm7 * 8;
                addr += imm;
                addr -= Memory[0].addr;
                
                uint64_t dat = Memory[addr].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 1].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 2].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 3].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 4].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 5].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 6].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 7].getData();
                
                uint64_t data1 = dat;
                
                dat = 0;
                dat =  Memory[addr + 8].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 9].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 10].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 11].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 12].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 13].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 14].getData();
                dat = dat << 8;
                dat = dat | Memory[addr + 15].getData();
                
                uint64_t data2 = dat;
                
                R[rt].setData(data1);
                R[rt2].setData(data2);
            }
        }
    }
    
    else    //STORE STP
    {
       printf("[log]-STP instruction\n");
        if(inst_type == 1)  //post index
        {
            printf("[log]-STP post index \n");
            if(!opc)    //32 bit registers
            {
                printf("[log]-STP post index 32\n");
                int imm = imm7 * 4;
                uint64_t addr = R[rn].getData();
                addr -= Memory[0].addr;
                int data1 = R[rt].getLowerData();
                int data2 = R[rt2].getLowerData();
                
                int dat = (data1 & 0xff000000)>>24;
                Memory[addr].setData((uint8_t)dat);
                dat = (data1 & 0x00ff0000)>>16;
                Memory[addr + 1].setData((uint8_t)dat);
                dat = (data1 & 0x0000ff00)>>8;
                Memory[addr + 2].setData((uint8_t)dat);
                dat = (data1 & 0x000000ff);
                Memory[addr + 3].setData((uint8_t)dat);
               
                dat = (data2 & 0xff000000)>>24;
                Memory[addr + 4].setData((uint8_t)dat);
                dat = (data2 & 0x00ff0000)>>16;
                Memory[addr + 5].setData((uint8_t)dat);
                dat = (data2 & 0x0000ff00)>>8;
                Memory[addr + 6].setData((uint8_t)dat);
                dat = (data2 & 0x000000ff);
                Memory[addr + 7].setData((uint8_t)dat);
                
                addr += imm;
                R[rn].setData(addr);
                
            }  
            
            else    //64 bit registers
            {
                printf("[log]-STP post index 64\n");
                uint64_t imm = imm7 * 8;
                uint64_t addr = R[rn].getData();
                addr -= Memory[0].addr;
                uint64_t data1 = R[rt].getData();
                uint64_t data2 = R[rt2].getData();
                
                uint64_t dat = (data1 & 0xff00000000000000)>>56;
                Memory[addr].setData((uint8_t)dat);
                dat = (data1 & 0x00ff000000000000)>>48;
                Memory[addr + 1].setData((uint8_t)dat);
                dat = (data1 & 0x0000ff0000000000)>>40;
                Memory[addr + 2].setData((uint8_t)dat);
                dat = (data1 & 0x000000ff00000000)>>32;
                Memory[addr + 3].setData((uint8_t)dat);
                dat = (data1 & 0x00000000ff000000)>>24;
                Memory[addr + 4].setData((uint8_t)dat);
                dat = (data1 & 0x0000000000ff0000)>>16;
                Memory[addr + 5].setData((uint8_t)dat);
                dat = (data1 & 0x000000000000ff00)>>8;
                Memory[addr + 6].setData((uint8_t)dat);
                dat = (data1 & 0x00000000000000ff);
                Memory[addr + 7].setData((uint8_t)dat);
               
                dat = (data2 & 0xff00000000000000)>>56;
                Memory[addr + 8].setData((uint8_t)dat);
                data2 = data2 >> 8;
                dat = (data2 & 0x00ff000000000000)>>48;
                Memory[addr + 9].setData((uint8_t)dat);
                data2 = data2 >> 8;
                dat = (data2 & 0x0000ff0000000000)>>40;
                Memory[addr + 10].setData((uint8_t)dat);
                data2 = data2 >> 8;
                dat = (data2 & 0x000000ff00000000)>>32;
                Memory[addr + 11].setData((uint8_t)dat);
                data2 = data2 >> 8;
                dat = (data2 & 0x00000000ff000000)>>24;
                Memory[addr + 12].setData((uint8_t)dat);
                data2 = data2 >> 8;
                dat = (data2 & 0x0000000000ff0000)>>16;
                Memory[addr + 13].setData((uint8_t)dat);
                data2 = data2 >> 8;
                dat = (data2 & 0x000000000000ff00)>>8;
                Memory[addr + 14].setData((uint8_t)dat);
                data2 = data2 >> 8;
                dat = (data2 & 0x00000000000000ff);
                Memory[addr + 15].setData((uint8_t)dat);
                
                
                addr += imm;
                R[rn].setData(addr);
                
            }         
        }
        
        else if(inst_type == 3) //pre index
        {
            printf("[log]-STP pre index\n");
            if(!opc)    //32 bit registers
            {
            printf("[log]-STP pre index 32\n");
                int imm = imm7 * 4;
		int data1 = R[rt].getLowerData();
		int data2 = R[rt2].getLowerData(); 
                uint64_t addr = R[rn].getData();
                
                addr += imm;
                R[rn].setData(addr);
                
                addr -= Memory[0].addr;
                
              int dat = (data1 & 0xff000000)>>24;
                Memory[addr].setData((uint8_t)dat);
                dat = (data1 & 0x00ff0000)>>16;
                Memory[addr + 1].setData((uint8_t)dat);
                dat = (data1 & 0x0000ff00)>>8;
                Memory[addr + 2].setData((uint8_t)dat);
                dat = (data1 & 0x000000ff);
                Memory[addr + 3].setData((uint8_t)dat);
               
                dat = (data2 & 0xff000000)>>24;
                Memory[addr + 4].setData((uint8_t)dat);
                dat = (data2 & 0x00ff0000)>>16;
                Memory[addr + 5].setData((uint8_t)dat);
                dat = (data2 & 0x0000ff00)>>8;
                Memory[addr + 6].setData((uint8_t)dat);
                dat = (data2 & 0x000000ff);
                Memory[addr + 7].setData((uint8_t)dat);
                
                
            }  
            
            else   //64 bit registers
            {
                printf("[log]-STP pre index 64\n");
                int imm = imm7 * 8;
                uint64_t addr = R[rn].getData();
                addr = addr + imm;
                R[rn].setData(addr);
                addr -= Memory[0].addr;
                addr += imm;
               	uint64_t data1 = R[rt].getData();
		        uint64_t data2 = R[rt2].getData();
		 
                R[rn].setData(addr);
                 uint64_t dat = (data1 & 0xff00000000000000)>>56;
                Memory[addr].setData((uint8_t)dat);
                dat = (data1 & 0x00ff000000000000)>>48;
                Memory[addr + 1].setData((uint8_t)dat);
                dat = (data1 & 0x0000ff0000000000)>>40;
                Memory[addr + 2].setData((uint8_t)dat);
                dat = (data1 & 0x000000ff00000000)>>32;
                Memory[addr + 3].setData((uint8_t)dat);
                dat = (data1 & 0x00000000ff000000)>>24;
                Memory[addr + 4].setData((uint8_t)dat);
                dat = (data1 & 0x0000000000ff0000)>>16;
                Memory[addr + 5].setData((uint8_t)dat);
                dat = (data1 & 0x000000000000ff00)>>8;
                Memory[addr + 6].setData((uint8_t)dat);
                dat = (data1 & 0x00000000000000ff);
                Memory[addr + 7].setData((uint8_t)dat);
               
                dat = (data2 & 0xff00000000000000)>>56;
                Memory[addr + 8].setData((uint8_t)dat);
                data2 = data2 >> 8;
                dat = (data2 & 0x00ff000000000000)>>48;
                Memory[addr + 9].setData((uint8_t)dat);
                data2 = data2 >> 8;
                dat = (data2 & 0x0000ff0000000000)>>40;
                Memory[addr + 10].setData((uint8_t)dat);
                data2 = data2 >> 8;
                dat = (data2 & 0x000000ff00000000)>>32;
                Memory[addr + 11].setData((uint8_t)dat);
                data2 = data2 >> 8;
                dat = (data2 & 0x00000000ff000000)>>24;
                Memory[addr + 12].setData((uint8_t)dat);
                data2 = data2 >> 8;
                dat = (data2 & 0x0000000000ff0000)>>16;
                Memory[addr + 13].setData((uint8_t)dat);
                data2 = data2 >> 8;
                dat = (data2 & 0x000000000000ff00)>>8;
                Memory[addr + 14].setData((uint8_t)dat);
                data2 = data2 >> 8;
                dat = (data2 & 0x00000000000000ff);
                Memory[addr + 15].setData((uint8_t)dat);
                
            } 
        }
        
        else if(inst_type == 2) //signed offset
        {
	        printf("[log]-STP signed offset\n");
            if(!opc)    //32 bit registers
            {
                printf("[log]-STP signed offset 32\n");
                uint64_t addr = R[rn].getData();
                int imm = imm7 * 4;
                addr += imm;
                addr -= Memory[0].addr;
                int data1 = R[rt].getLowerData();
	        	int data2 = R[rt2].getLowerData(); 
                int dat = (data1 & 0xff000000)>>24;
                Memory[addr].setData((uint8_t)dat);
                dat = (data1 & 0x00ff0000)>>16;
                Memory[addr + 1].setData((uint8_t)dat);
                dat = (data1 & 0x0000ff00)>>8;
                Memory[addr + 2].setData((uint8_t)dat);
                dat = (data1 & 0x000000ff);
                Memory[addr + 3].setData((uint8_t)dat);
               
                dat = (data2 & 0xff000000)>>24;
                Memory[addr + 4].setData((uint8_t)dat);
                dat = (data2 & 0x00ff0000)>>16;
                Memory[addr + 5].setData((uint8_t)dat);
                dat = (data2 & 0x0000ff00)>>8;
                Memory[addr + 6].setData((uint8_t)dat);
                dat = (data2 & 0x000000ff);
                Memory[addr + 7].setData((uint8_t)dat);
                
            }
            
            else    //64 bit registers
            {
            	printf("[log]-STP signed offset 64\n");
                uint64_t addr = R[rn].getData();
                int imm = imm7 * 8;
                addr += imm;
                addr -= Memory[0].addr;
               	uint64_t data1 = R[rt].getData();
		uint64_t data2 = R[rt2].getData(); 
                R[rn].setData(addr);
                 uint64_t dat = (data1 & 0xff00000000000000)>>56;
                Memory[addr].setData((uint8_t)dat);
                dat = (data1 & 0x00ff000000000000)>>48;
                Memory[addr + 1].setData((uint8_t)dat);
                dat = (data1 & 0x0000ff0000000000)>>40;
                Memory[addr + 2].setData((uint8_t)dat);
                dat = (data1 & 0x000000ff00000000)>>32;
                Memory[addr + 3].setData((uint8_t)dat);
                dat = (data1 & 0x00000000000000ff)>>24;
                Memory[addr + 4].setData((uint8_t)dat);
                dat = (data1 & 0x0000000000ff0000)>>16;
                Memory[addr + 5].setData((uint8_t)dat);
                dat = (data1 & 0x000000000000ff00)>>8;
                Memory[addr + 6].setData((uint8_t)dat);
                dat = (data1 & 0x00000000000000ff);
                Memory[addr + 7].setData((uint8_t)dat);
               
                dat = (data2 & 0xff00000000000000)>>56;
                Memory[addr + 8].setData((uint8_t)dat);
                data2 = data2 >> 8;
                dat = (data2 & 0x00ff000000000000)>>48;
                Memory[addr + 9].setData((uint8_t)dat);
                data2 = data2 >> 8;
                dat = (data2 & 0x0000ff0000000000)>>40;
                Memory[addr + 10].setData((uint8_t)dat);
                data2 = data2 >> 8;
                dat = (data2 & 0x000000ff00000000)>>32;
                Memory[addr + 11].setData((uint8_t)dat);
                data2 = data2 >> 8;
                dat = (data2 & 0x00000000ff000000)>>24;
                Memory[addr + 12].setData((uint8_t)dat);
                data2 = data2 >> 8;
                dat = (data2 & 0x0000000000ff0000)>>16;
                Memory[addr + 13].setData((uint8_t)dat);
                data2 = data2 >> 8;
                dat = (data2 & 0x000000000000ff00)>>8;
                Memory[addr + 14].setData((uint8_t)dat);
                data2 = data2 >> 8;
                dat = (data2 & 0x00000000000000ff);
                Memory[addr + 15].setData((uint8_t)dat);
            }
        }
    }
}
