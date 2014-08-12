#include<iostream>
#include<elfio/elfio.hpp>
#include<cassert>
#include<cstdio>

using namespace ELFIO;
using namespace std;
#define REP(i,a,b) \
	for(int i = a; i <= b; i++)

const char* DATAFILE = "data.txt";
const char* INSTFILE = "inst.txt";
const char* INFOFILE = "info.txt";

int main(int argc, char** argv )
{
	elfio reader;
	FILE *data_file,*inst_file,*info_file;

	data_file = fopen(DATAFILE,"w");
	inst_file = fopen(INSTFILE,"w");
	info_file = fopen(INFOFILE,"w");
	
	if (argc != 2)
	{
		cout<<"give me a file name !!\n";
		return 1;
	}
	
	if( !reader.load( argv[1] ))
	{
		cout<<"error processing file-"<<argv[1]<<"\n";
		return 2;
	}
	
/*
	cout<<"ELF File Class:\n";

	if( reader.get_class() == ELFCLASS32)
		cout<<"ELF 32\n";
	else
		cout<<"ELF 64\n";
*/

	fprintf(info_file,"0x%lx\n",reader.get_entry());
	
//	cout<<"ELF Encoding:\n";	
	if( reader.get_encoding() == ELFDATA2LSB)
		fprintf(info_file,"L\n");
	else
		fprintf(info_file,"B\n");


//ELF section info

	Elf_Half sec_num = reader.sections.size();
	REP(i,0,sec_num-1)
	{
 		const section* psec = reader.sections[i];
		const char* p = psec->get_data();

		if( p != NULL && psec->get_name() == ".text")
		{
			int l=0;
		 	while(l < psec->get_size()) { fprintf(inst_file,"%.2x",(unsigned)(unsigned char)p[l]);  l++;} //note- cout<<hex could also be used 
		} 
		else if( p != NULL && psec->get_name() == ".data")
		{
			int l=0;
		 	while(l < psec->get_size()) { fprintf(data_file,"%.2x",(unsigned)(unsigned char)p[l]);  l++;} //note- cout<<hex could also be used 
		}
	}

	fclose(data_file);
	fclose(inst_file);
	fclose(info_file);
 	return 0;
}
