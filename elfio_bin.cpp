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
 		section* psec = reader.sections[i];
		const char* p = psec->get_data();
		if ( psec->get_type() == SHT_SYMTAB ) 
		{
			const symbol_section_accessor symbols( reader, psec );
			for ( unsigned int j = 0; j < symbols.get_symbols_num(); ++j ) {
				std::string
				 name;
				 Elf64_Addr
				  value;
				  Elf_Xword
				   size;
				   unsigned char bind;
				   unsigned char type;
				   Elf_Half
				    section_index;
				    unsigned char other;
			symbols.get_symbol( j, name, value, size, bind,type, section_index, other );
			if(name != "" && name!= "$x")
				fprintf(data_file,"%lu\n",value);	
			}
		}

		if( p != NULL && psec->get_name() == ".text")
		{
			int l=0;
		 	while(l < psec->get_size()) { fprintf(inst_file,"%.2x",(unsigned)(unsigned char)p[l]);  l++;} //note- cout<<hex could also be used 
		} 
	/*	else if( p != NULL && psec->get_name() == ".data")
		{
			int l=0;
		 	while(l < psec->get_size()) { fprintf(data_file,"%.2x",(unsigned)(unsigned char)p[l]);  l++;} //note- cout<<hex could also be used 
		}*/
	}

	fclose(data_file);
	fclose(inst_file);
	fclose(info_file);
 	return 0;
}
