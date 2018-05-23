#include "headers/avm.h"
#include <iterator>

#define MAGICNUMBER "474747"

std::vector<std::string> strConsts;
std::vector<double> numConsts;
std::vector<std::string> libFuncs;
std::vector<userfunc*> userFuncs;

int main(int argc, char* argv[]){ 
	if(argc<2) assert(false);

	std::ifstream infile(argv[1],std::fstream::in);
	std::string output,line;
	int size=0;

	std::getline(infile,line);
	if(line.compare(MAGICNUMBER)){
			std::cout<<"Not an abc file\n";
			return -1;		
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

	avm_initialize();
	while(!executionFinished){
		//std::cout<<"PC:"<<pc<<std::endl;
		execute_cycle();
	}

	 return 0;
}



