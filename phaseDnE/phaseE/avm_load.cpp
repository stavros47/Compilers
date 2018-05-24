#include "headers/avm.h"
#include <iterator>
#include <stdlib.h>

std::vector<std::string> strConsts;
std::vector<double> numConsts;
std::vector<std::string> libFuncs;
std::vector<userfunc*> userFuncs;

int main(int argc, char* argv[]){ 
	if(argc<2) assert(false);

	read_binary(argv[1]);

	avm_initialize();
	while(!executionFinished){
		execute_cycle();
	}

	 return 0;
}

void read_binary(char* file){
	unsigned num,size,p;
	double d;
	char* str;
	FILE* fp;

	fp = fopen(file,"rb");

	fread(&num, sizeof(unsigned), 1, fp);
	if(num!=474747){
			std::cout<<"Not an abc file\n"<<num<<std::endl;
			return;		
	}

	fread(&num,sizeof(unsigned),1,fp);
	for(unsigned i=0;i<num;i++){
		fread(&size,sizeof(unsigned),1,fp);
		str = (char*)malloc(size * sizeof(char));
		fread(str, size * sizeof(char) , 1, fp);
		strConsts.push_back(str);
	}

	fread(&num,sizeof(unsigned),1,fp);
	for(unsigned i=0;i<num;i++){
		fread(&d,sizeof(double),1,fp);
		numConsts.push_back(d);
	}

	fread(&num,sizeof(unsigned),1,fp);
	for(unsigned i=0;i<num;i++){
		fread(&size,sizeof(unsigned),1,fp);
		str = (char*)malloc(size * sizeof(char));		
		fread(str, size * sizeof(char) , 1, fp);
		libFuncs.push_back(str);
	}

	fread(&num,sizeof(unsigned),1,fp);
	for(unsigned i=0;i<num;i++){
		userfunc* us = new userfunc();
		fread(&size,sizeof(unsigned),1,fp);

		str = (char*)malloc(size * sizeof(char));		
		fread(str, size * sizeof(char) , 1, fp);
		us->id=str;
		fread(&size,sizeof(unsigned),1,fp);		
		us->address = size;
		fread(&size,sizeof(unsigned),1,fp);				
		us->localSize = size;
		userFuncs.push_back(us);
	}

	while(!feof(fp)){
		if(totalInstr == codeSize++)
			expand_instr();
		instruction* p = code + currLine++;	
		fread(&num,sizeof(unsigned),1,fp);		
		p->srcLine = num;
		fread(&num,sizeof(unsigned),1,fp);		
		p->opcode =(vmopcode) num;
		fread(&num,sizeof(unsigned),1,fp);		
		p->result.type = (vmarg_t)num;
		fread(&num,sizeof(unsigned),1,fp);		
		p->result.val = num;
		test_global(p->result);		
		fread(&num,sizeof(unsigned),1,fp);		
		p->arg1.type = (vmarg_t)num;
		fread(&num,sizeof(unsigned),1,fp);		
		p->arg1.val = num;
		test_global(p->arg1);		
		fread(&num,sizeof(unsigned),1,fp);		
		p->arg2.type = (vmarg_t)num;
		fread(&num,sizeof(unsigned),1,fp);		
		p->arg2.val = num;
		test_global(p->arg2);
		
	}

}

void open_txt(std::string file){
	std::ifstream infile(file,std::fstream::in);
	std::string output,line;
	int size=0;

	std::getline(infile,line);
	if(line.compare(std::to_string(MAGICNUMBER))){
			std::cout<<"Not an abc file\n";
			return;		
	}

	std::string s;

	std::getline(infile,line);
	size= std::stoi(line);
	for(int i=0;i<size;i++){
		std::getline(infile,line);
		s.append(line);

		while(line[line.length()-1] != '\"'){
			s.append("\n");
			std::getline(infile,line);
			s.append(line);
		}

		s.erase(0,1);
		s.erase(s.length() -1);
		strConsts.push_back(s);
		s.clear();
	}

	std::getline(infile,line);
	size= std::stoi(line);
	for(int i=0;i<size;i++){
		std::getline(infile,line);		
		numConsts.push_back(std::stod(line));
	}

	std::getline(infile,line);
	size= std::stoi(line);
	for(int i=0;i<size;i++){
		s.clear();
		std::getline(infile,line);
		s.append(line);
		libFuncs.push_back(s);
	}

	std::getline(infile,line);
	size= std::stoi(line);
	for(int i=0;i<size;i++){
		std::getline(infile,line);
		s.append(line);
    	std::istringstream buf(s);
    	std::istream_iterator<std::string> beg(buf), end;
		std::vector<std::string> tokens(beg, end);

		userfunc* us = new userfunc();
		us->id=tokens[0];
		us->address = std::stoi(tokens[1]);
		us->localSize = std::stoi(tokens[2]);
		userFuncs.push_back(us);
		s.clear();
	}

	while(!infile.eof()){
		if(totalInstr == codeSize++)
			expand_instr();

		instruction* p = code + currLine++;
		infile>>output;
		p->srcLine = (unsigned)std::stoi(output);
		infile >> output;
		p->opcode = (vmopcode)std::stoi(output);
		infile >> output;
		p->result.type = (vmarg_t)std::stoi(output);
		infile >> output;
		p->result.val = (unsigned)std::stoi(output);
		infile >> output;
		test_global(p->result);
		p->arg1.type = (vmarg_t)std::stoi(output);
		infile >> output;
		p->arg1.val = (unsigned)std::stoi(output);
		infile >> output;
		test_global(p->arg1);
		p->arg2.type = (vmarg_t)std::stoi(output);
		infile >> output;
		p->arg2.val = (unsigned)std::stoi(output);
		test_global(p->arg2);
	}

	infile.close();

}