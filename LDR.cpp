#include<stdint.h>
void LDR()
{
    int bit_see = (IR.getLowerData() & 0x01000000);    //24th bit to check post index, pre index, unsigned offset
    int instr_type = (IR.getLowerData() & 0x00400000) >> 22; //22nd bit to check for load/ store
    if(instr_type)      //load LDR immediate
    {
    	printf("[log] - LDR immediate\n");
        if(!bit_see)    //post-index or pre-index
        {
        	
            int size = (IR.getLowerData() & 0xc0000000) >> 30;
            int opc = (IR.getLowerData() & 0x00c00000) >> 22;
            int imm9 = (IR.getLowerData() & 0x001ff000) >> 12;
            int rn = (IR.getLowerData() & 0x000003e0) >> 5;
            int rt = (IR.getLowerData() & 0x0000001f);
            int eleventh_bit = (IR.getLowerData() & 0x00000800);
            
            if(!eleventh_bit)   //post index
            {
                printf("[log] - LDR immediate post index\n");
                if(size == 2)   //32 bit variant
                {
                	printf("[log] - LDR immediate post index 32\n");
                    int addr = R[rn].getLowerData();
                    int imm;
                    //signed extention
                    imm = signExtend(imm9,8);
                    
                    
                    int dat = (int)Memory[addr].getData();
                    dat = dat << 8;
                    dat = dat | (int)Memory[addr + 1].getData();
                    dat = dat << 8;
                    dat = dat | (int)Memory[addr + 2].getData();
                    dat = dat << 8;
                    dat = dat | (int)Memory[addr + 3].getData();
                    
                    R[rt].setLowerData(dat);
                    
                    addr = addr + imm;
                    R[rn].setLowerData(addr);
                }
                
                else            //64 bit variant
                {
                	printf("[log] - LDR immediate post index 64\n");
                    uint64_t addr = R[rn].getData();
                    uint64_t imm;
                    //int bit = (imm9 & 0x00000100) >> 8;
                    //signed extention

                     imm = signExtend(imm9,8);
                    uint64_t dat = (int)Memory[addr].getData();
                    dat = dat << 8;
                    dat = dat | (int)Memory[addr + 1].getData();
                    dat = dat << 8;
                    dat = dat | (int)Memory[addr + 2].getData();
                    dat = dat << 8;
                    dat = dat | (int)Memory[addr + 3].getData();
                    dat = dat << 8;
                    dat = dat | (int)Memory[addr + 4].getData();
                    dat = dat << 8;
                    dat = dat | (int)Memory[addr + 5].getData();
                    dat = dat << 8;
                    dat = dat | (int)Memory[addr + 6].getData();
                    dat = dat << 8;
                    dat = dat | (int)Memory[addr + 7].getData();
                    
                    R[rt].setData(dat);
                    
                    addr = addr + (uint64_t)imm;
                    R[rn].setData(addr);
                }
            }
            
            else                //preindex
            {
            	printf(" [log] - LDR immediate pre index\n");
                if(size == 2)   //32 bit registers
                {
                	printf("[log] - LDR immediate pre index 32\n");
                    int addr = R[rn].getLowerData();
                    int imm;
                    //signed extention
                    
                    imm = signExtend(imm9,8);
                    addr = addr + imm;
                    R[rn].setLowerData(addr);
                    int dat = (int)Memory[addr].getData();
                    dat = dat << 8;
                    dat = dat | (int)Memory[addr + 1].getData();
                    dat = dat << 8;
                    dat = dat | (int)Memory[addr + 2].getData();
                    dat = dat << 8;
                    dat = dat | (int)Memory[addr + 3].getData();
                    
                    R[rt].setLowerData(dat);
  
                    
                }
                
                else        //64 bit registers
                {
                	printf("[log] - LDR immediate pre index 64\n");
                    uint64_t addr = R[rn].getData();
                    uint64_t imm;
                    //signed extention
                    imm = signExtend(imm9,8);
                    addr = addr + imm;
                    R[rn].setData(addr);
                    uint64_t dat = (int)Memory[addr].getData();
                    dat = dat << 8;
                    dat = dat | (int)Memory[addr + 1].getData();
                    dat = dat << 8;
                    dat = dat | (int)Memory[addr + 2].getData();
                    dat = dat << 8;
                    dat = dat | (int)Memory[addr + 3].getData();
                    dat = dat << 8;
                    dat = dat | (int)Memory[addr + 4].getData();
                    dat = dat << 8;
                    dat = dat | (int)Memory[addr + 5].getData();
                    dat = dat << 8;
                    dat = dat | (int)Memory[addr + 6].getData();
                    dat = dat << 8;
                    dat = dat | (int)Memory[addr + 7].getData();
                    
                    R[rt].setData(dat);
                    
                   
                }
            }
        }
        
        else    // unsigned offset
        {
        	printf("[log] - LDR immediate unsigned offset\n");
            int size = (IR.getLowerData() & 0xc0000000) >> 30;
            int opc = (IR.getLowerData() & 0x00c00000) >> 22;
            int imm12 = (IR.getLowerData() & 0x003ffc00) >> 10;
            int rn = (IR.getLowerData() & 0x000003e0) >> 5;
            int rt = (IR.getLowerData() & 0x0000001f);
            if(size == 2)   //32 bit variant
            {
            	printf("LDR immediate unsigned offset 32\n");
                int pimm = imm12 * 4;
                uint64_t addr = R[rn].getData();
                addr += (uint64_t)pimm;
                int dat = (int)Memory[addr].getData();
                dat = dat << 8;
                dat = dat | (int)Memory[addr + 1].getData();
                dat = dat << 8;
                dat = dat | (int)Memory[addr + 2].getData();
                dat = dat << 8;
                dat = dat | (int)Memory[addr + 3].getData();
                
                R[rt].setLowerData(dat);
            }
            
            else    //64 bit variant
            {
            	printf("[log] - LDR immediate unsigned offset 64\n");
                int pimm = imm12 * 8;
                uint64_t addr = R[rn].getData();
                addr += (uint64_t)pimm;
                uint64_t dat = (uint64_t)Memory[addr].getData();
                dat = dat << 8;
                dat = dat | (uint64_t)Memory[addr + 1].getData();
                dat = dat << 8;
                dat = dat | (uint64_t)Memory[addr + 2].getData();
                dat = dat << 8;
                dat = dat | (uint64_t)Memory[addr + 3].getData();
                 dat = dat << 8;
                dat = dat | (uint64_t)Memory[addr + 4].getData();
                 dat = dat << 8;
                dat = dat | (uint64_t)Memory[addr + 5].getData();
                 dat = dat << 8;
                dat = dat | (uint64_t)Memory[addr + 6].getData();
                 dat = dat << 8;
                dat = dat | (uint64_t)Memory[addr + 7].getData();
                
                R[rt].setData(dat);
            }
        }
    }
    
    else    //store STR immediate
    {
    	printf("[log] -STR immediate\n");
        if(!bit_see)    // post or pre index
        {
            int eleventh_bit = (IR.getLowerData() & 0x00000800) >> 11;
            if(!eleventh_bit)   //post index
            {
            	printf("[log] - STR immediate post index\n");
                int size = (IR.getLowerData() & 0xc0000000) >> 30;
                int opc = (IR.getLowerData() & 0x00c00000) >> 22;
                int imm9 = (IR.getLowerData() & 0x001ff000) >> 12;
                int rn = (IR.getLowerData() & 0x000003e0) >> 5;
                
                int rt = (IR.getLowerData() & 0x0000001f);
                uint64_t offset = signExtend(imm9,8);
                uint64_t addr = R[rn].getData();
                addr -= Memory[0].addr;
                if(size == 2)   //32 bit registers
                {
                	printf(" [log] - STR immediate post index 32\n");
                    int data = R[rt].getLowerData();
                    uint8_t dat = (data & 0xff000000)>>24;
                    Memory[addr].setData(dat);
                    dat = (data & 0x00ff0000)>>16;
                    Memory[addr + 1].setData(dat);
                    dat = (data & 0x0000ff00)>>8;
                    Memory[addr + 2].setData(dat);
                    dat = data & 0xff0000ff;
                    Memory[addr + 3].setData(dat);
                }
                
                else  //64 bit registers
                {
                	printf("[log] - STR immediate post index 64\n");
                    uint64_t data = R[rt].getData();
                    uint8_t dat;
                    dat = (data & 0xff00000000000000)>>56;
                    Memory[addr].setData(dat);
                    dat = (data & 0x00ff000000000000)>>48;
                    Memory[addr + 1].setData(dat);
                    dat = (data & 0x0000ff0000000000)>>40;
                    Memory[addr + 2].setData(dat);
                    dat = (data & 0x000000ff00000000)>>32;
                    Memory[addr + 3].setData(dat);
                    dat = (data & 0x00000000ff000000)>>24;
                    Memory[addr + 4].setData(dat);
                    dat = (data & 0xff00000000ff0000)>>16;
                    Memory[addr + 5].setData(dat);
                    dat = (data & 0x000000000000ff00)>>8;
                    Memory[addr + 6].setData(dat);
                    dat = data & 0x00000000000000ff;
                    Memory[addr + 7].setData(dat);
                }
                
                addr = addr + offset;
                R[rn].setData(addr);
            }
            
            else        //pre index
            {
            	printf("[log] - STR immediate pre index\n");
                int size = (IR.getLowerData() & 0xc0000000) >> 30;
                int opc = (IR.getLowerData() & 0x00c00000) >> 22;
                int imm9 = (IR.getLowerData() & 0x001ff000) >> 12;
                int rn = (IR.getLowerData() & 0x000003e0) >> 5;
                
                int rt = (IR.getLowerData() & 0x0000001f);
                uint64_t offset = signExtend(imm9,8);
                uint8_t addr = R[rn].getData();
                
                addr = addr + offset;
                addr -= Memory[0].addr;
                R[rn].setData(addr);
                if(size == 2)   //32 bit registers
                {
                	printf("[log] - STR immediate pre index 32\n");
                    int data = R[rt].getLowerData();
                    uint8_t dat = (data & 0xff000000)>>24;
                    Memory[addr].setData(dat);
                    dat = (data & 0x00ff0000)>>16;
                    Memory[addr + 1].setData(dat);
                    dat = (data & 0x0000ff00)>>8;
                    Memory[addr + 2].setData(dat);
                    dat = data & 0xff0000ff;
                    Memory[addr + 3].setData(dat);
                }
                
                else  //64 bit registers
                {
                	printf("[log] - STR immediate pre index 64\n");
                    uint64_t data = R[rt].getData();
                    uint8_t dat;
                    dat = (data & 0xff00000000000000)>>56;
                    Memory[addr].setData(dat);
                    dat = (data & 0x00ff000000000000)>>48;
                    Memory[addr + 1].setData(dat);
                    dat = (data & 0x0000ff0000000000)>>40;
                    Memory[addr + 2].setData(dat);
                    dat = (data & 0x000000ff00000000)>>32;
                    Memory[addr + 3].setData(dat);
                    dat = (data & 0x00000000ff000000)>>24;
                    Memory[addr + 4].setData(dat);
                    dat = (data & 0xff00000000ff0000)>>16;
                    Memory[addr + 5].setData(dat);
                    dat = (data & 0x000000000000ff00)>>8;
                    Memory[addr + 6].setData(dat);
                    dat = data & 0x00000000000000ff;
                    Memory[addr + 7].setData(dat);
                }
                
               
            }
        }
        
        else    //unsigned offset
        {
        	printf("[log] - STR immediate unsigned offset\n");
            int size = (IR.getLowerData() & 0xc0000000) >> 30;
            int opc = (IR.getLowerData() & 0x00c00000) >> 22;
            int imm12 = (IR.getLowerData() & 0x003ffc00) >> 10;
            int rn = (IR.getLowerData() & 0x000003e0) >> 5;
            int rt = (IR.getLowerData() & 0x0000001f);
            
            uint64_t addr = R[rn].getData();
            uint64_t offset = (0x0000000000000fff) & (uint64_t)imm12;
            addr += offset;
            addr -= Memory[0].addr;
            
            if(size == 2)   //32 bit registers
            {
            	printf("[log] - STR immediate unsigned offset 32\n");
                int data = R[rt].getLowerData();
                uint8_t dat = (data & 0xff000000)>>24;
                    Memory[addr].setData(dat);
                    dat = (data & 0x00ff0000)>>16;
                    Memory[addr + 1].setData(dat);
                    dat = (data & 0x0000ff00)>>8;
                    Memory[addr + 2].setData(dat);
                    dat = data & 0xff0000ff;
                    Memory[addr + 3].setData(dat);
            
                
            }
            
            else        //64 bit registers
            {
            	printf("[log] - STR immediate unsigned offset 64\n");
                uint64_t data = R[rt].getData();
                uint8_t dat;
                    dat = (data & 0xff00000000000000)>>56;
                    Memory[addr].setData(dat);
                    dat = (data & 0x00ff000000000000)>>48;
                    Memory[addr + 1].setData(dat);
                    dat = (data & 0x0000ff0000000000)>>40;
                    Memory[addr + 2].setData(dat);
                    dat = (data & 0x000000ff00000000)>>32;
                    Memory[addr + 3].setData(dat);
                    dat = (data & 0x00000000ff000000)>>24;
                    Memory[addr + 4].setData(dat);
                    dat = (data & 0xff00000000ff0000)>>16;
                    Memory[addr + 5].setData(dat);
                    dat = (data & 0x000000000000ff00)>>8;
                    Memory[addr + 6].setData(dat);
                    dat = data & 0x00000000000000ff;
                    Memory[addr + 7].setData(dat);
            }
            
        }
    }
    
}
