#include"loader.h"
#include"allstdlib.h"


Loader::Loader()
{
	ldfile = NULL;
}

Loader::Loader(char* s)
{
	ldfile = fopen(s,"r");
	if(ldfile == NULL) exit(1);
}

void Loader::setFile(char* s)
{
	if(ldfile != NULL)
		fclose(ldfile);
	
	ldfile = fopen(s,"r");

}

int Loader::loadmem(int start , mem m[],char endian)
{
	uint32_t x;uint32_t bigendian;
	char c,data[17];
	//TODO-get an instance of memory and load ldfile from start pos
	

	while((c = fgetc(ldfile)) != EOF)
	{
		ungetc(c,ldfile);
		REP(i,0,7)//TODO - take in 8 hex letters (1 hex letter 1 nibble- write instructions bitwise)
		{
			if(c = fgetc(ldfile))
				data[i] = c;
			else
				exit(3);

		}
		data[8] = '\0';

			//TODO - check big or little endian swap if necessary
	
		x =(uint32_t) strtoul(data,NULL,16);	 //TODO - convert string to uint64_t
		if(endian == 'L')
		 bigendian = __builtin_bswap32(x);
		else 
			bigendian = x;

		start = setDataW(m,bigendian,start);//TODO - write to mem 32 bit word 

		//start++;
	}//TODO - repeat from (a) until EOF
	return start;
}
