#include "headers/avm.h"
#include <assert.h>
#include <fstream>

std::vector<std::string> strConsts;
std::vector<double> numConsts;
std::vector<std::string> libFuncs;
std::vector<userfunc*> userFuncs;
instruction* instr;

void test_global(vmarg r){
	if(r.type == global_a){
		if(r.val>max_global_offset)
			max_global_offset=r.val;
	}
}

void prints();

int main(int argc, char* argv[]){ // or char** argv 
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
		
		infile>>output;
    	codeSize = std::stoi(output);
		code=(instruction*)malloc(codeSize*sizeof(instruction));
		
		while(!infile.eof()){
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

				//std::cout<<output<<"\n";
		}
	}
	infile.close();

	//prints();

	avm_initialize();
	while(!executionFinished){
		execute_cycle();	
	}

	// for(int i=AVM_STACKSIZE-1;i>=0;i--){
	// 	if(stack[i].type != undef_m)
	// 		std::cout<<avm_tostring(&stack[i])<<std::endl;
	// }

	 return 0;
}

void prints(){
	for(std::string i : strConsts)
		std::cout<<i<<std::endl;
	for(double i : numConsts)
		std::cout<<i<<std::endl;
	for(std::string i : libFuncs)
		std::cout<<i<<std::endl;
	for(userfunc* i : userFuncs)
		std::cout<<i->id<<"\t"<<i->address<<"\t"<<i->localSize<<std::endl;
	for(int i=0;i<codeSize;i++){
		printf("%d:", code[i].srcLine);
		printf("\t%d", code[i].opcode);
		printf("\t%d:", code[i].result.type);
		printf("%d", code[i].result.val);
		printf("\t%d:", code[i].arg1.type);
		printf("%d", code[i].arg1.val);
		printf("\t%d:", code[i].arg2.type);
		printf("%d\n", code[i].arg2.val);
	}

	std::cout<<"MAX_GLOBAL_OFFSET:"<<max_global_offset<<"\n";

}