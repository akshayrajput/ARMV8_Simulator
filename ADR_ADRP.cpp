void ADR()
{
    int op = (IR.getLowerData() & 0x80000000) >> 31;
    int immlo = (IR.getLowerData() & 0x60000000) >> 29;
    int immhi = (IR.getLowerData() & 0x00ffffe0) >> 5;
    int rd = (IR.getLowerData() & 0x0000001f);
    uint64_t temp = ((uint64_t)immhi << 2) |((uint64_t)immlo);
    uint64_t base = BR.getData();
    bool page = (op == 1);
    uint64_t imm;
    if(page)
    {
        imm = signExtend(temp << 12,32);
        base = base & 0xfffff000;
    }
    
    else
    {
        imm = signExtend(temp,20);
    }
    
    uint64_t dat = base + imm;
    R[rd].setData(dat);
}
