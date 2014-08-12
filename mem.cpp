#include"mem.h"


mem::mem()
{
	    data =0;
	    access =false;
	    addr = 0;
}

bool mem::setData(uint8_t dat)
{
        this->data = dat;
        this->access = true;
        return true;
}

uint8_t mem::getData()
{
        return this->data;
}

uint64_t reg::getData()
{
        return this->data;
}

uint32_t reg::getLowerData()
{
         uint32_t dat = (uint32_t)(this->data & MASK);
         return dat;
}

bool reg::setData( uint64_t dat)
{
        this->data = dat;
        return true;
}

bool reg::setLowerData( uint32_t dat)
{
        this->data = dat & MASK;
        return true;
}

int setDataW(mem M[],uint32_t dat,int start)
{
	uint8_t w = (dat &0xff000000)>>24;
  	uint8_t x = (dat &0x00ff0000)>>16;
	uint8_t y = (dat &0x0000ff00)>>8;
	
	uint8_t z = (dat &0x000000ff);

	M[start].setData(w);
	start++;
	M[start].setData(x);
	start++;
	M[start].setData(y);
	start++;
	M[start].setData(z);
	start++;	

	return start;
}

int setDataDW(mem M[],uint64_t dat,int start)
{
	uint64_t a = dat;
	uint8_t b = (a & 0xff00000000000000)>>56;
	uint8_t c = (a & 0x00ff000000000000)>>48;
	uint8_t d = (a & 0x0000ff0000000000)>>40;
	uint8_t e = (a & 0x000000ff00000000)>>32;
	uint8_t f = (a & 0x00000000ff000000)>>24;
	uint8_t g = (a & 0x0000000000ff0000)>>16;
	uint8_t h = (a & 0xff0000000000ff00)>>8;
	uint8_t i = (a & 0xff000000000000ff);


	M[start].setData(b);
	start++;
	M[start].setData(c);
	start++;
	M[start].setData(d);
	start++;
	M[start].setData(e);
	start++;
	M[start].setData(f);
	start++;
	M[start].setData(g);
	start++;
	M[start].setData(h);
	start++;
	M[start].setData(i);
	start++;	

	return start;
}
