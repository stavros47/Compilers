#include "headers/avm.h"

std::vector<std::string> strConsts;
std::vector<double> numConsts;
std::vector<std::string> libFuncs;
std::vector<userfunc*> userFuncs;

unsigned totalInstr=0;

int main(int argc, char* argv[]){ 
	if(argc<2) assert(false);

	std::ifstream infile(argv[1],std::fstream::in);
	std::string output;

	if(infile.is_open()){
		infile>>output;		
		if(output.compare("474747")){
			std::cout<<"Not an abc file\n";
			return -1;
		}
		int size=0;

		infile>>output;
		size = std::stoi(output);
		for(int i=0;i<size;i++){
			infile>>output;
			strConsts.push_back(output);
		}

		infile>>output;
		size = std::stoi(output);
		for(int i=0;i<size;i++){
			infile>>output;
			numConsts.push_back(std::stod(output));
		}

		infile>>output;
		size = std::stoi(output);
		for(int i=0;i<size;i++){
			infile>>output;
			libFuncs.push_back(output);
		}

		infile>>output;
		size = std::stoi(output);
		for(int i=0;i<size;i++){
			userfunc* us = new userfunc();
			infile>>output;
			us->id=output;
			infile>>output;
			us->address = std::stoi(output);
			infile>>output;
			us->localSize = std::stoi(output);
			userFuncs.push_back(us);
		}
		
		while(!infile.eof()){
				if(totalInstr == codeSize++)
					expand();
				infile>>output;
				instruction* p = code + currLine++;
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
	}

	infile.close();

	avm_initialize();
	while(!executionFinished){
		//std::cout<<"PC:"<<pc<<std::endl;
		execute_cycle();
	}

	 return 0;
}



