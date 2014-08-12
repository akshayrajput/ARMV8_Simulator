#ifndef _LOADERH_
#define _LOADERH_
#include<cstdio>
#include"mem.h"
class Loader
{

private:
	FILE* ldfile;
public:
	Loader();//default constructor
	Loader(char* s);//constructor taking a file parameter
	void setFile(char* s); //set the file loaded
	int loadmem(int start,mem m[],char c);//loads the memory starting from start
};

#endif

