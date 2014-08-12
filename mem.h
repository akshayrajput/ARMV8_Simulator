#ifndef MEM_H
#define MEM_H
#define MASK 0x00000000ffffffff
#define MASKDW 0xff00000000000000

#include<stdint.h>

class mem{

    public:
     uint64_t addr;
     uint8_t data;
     bool access;
    

    mem();
    bool setData(uint8_t dat);
    uint8_t getData();

};

int setDataW(mem M[],uint32_t dat,int start);
int setDataDW(mem M[],uint64_t dat,int start);

class reg{
     uint64_t data;
    
    public:

    uint64_t getData(); 
    uint32_t getLowerData();
    bool setData( uint64_t dat);
    bool setLowerData( uint32_t dat);

}; //register is inbuilt type
#endif
