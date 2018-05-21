#include "headers/avm.h"
#include <assert.h>
#include <fstream>

#define I_EXPAND_SIZE 128
#define I_CURR_SIZE (totalInstr*sizeof(instruction))
#define I_NEW_SIZE (I_EXPAND_SIZE*sizeof(instruction) + I_CURR_SIZE)

unsigned totalInstr=0;

std::vector<std::string> strConsts;
std::vector<double> numConsts;
std::vector<std::string> libFuncs;
std::vector<userfunc*> userFuncs;

void test_global(vmarg r){
	if(r.type == global_a){
		if(r.val>max_global_offset)
			max_global_offset=r.val;
	}
}

void expand(void){
	instruction* p = (instruction*)malloc(I_NEW_SIZE);
	if(code){
		std::memcpy(p,code,I_CURR_SIZE);
		free(code);
	}
	code = p;
	totalInstr+=I_EXPAND_SIZE;
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
		//codeSize = currLine;

	}
	infile.close();

	//prints();


	avm_initialize();
	int cnt =1 ;
	while(!executionFinished){
		//std::cout<<cnt++<<"\tpc:"<<pc<<std::endl;
		execute_cycle();	
	}

	// for(int i=AVM_STACKSIZE-1;i>=0;i--){
	// 	if(stack[i].type != undef_m)
	// 		std::cout<<avm_tostring(&stack[i])<<std::endl;
	// }

	 return 0;
}

void prints(){
	std::cout<<"string consts\n";
	for(std::string i : strConsts)
		std::cout<<i<<std::endl;
	std::cout<<"num consts\n";
	for(double i : numConsts)
		std::cout<<i<<std::endl;
	std::cout<<"lib funcs\n";
	for(std::string i : libFuncs)
		std::cout<<i<<std::endl;
	std::cout<<"userfuncs\n";
	for(userfunc* i : userFuncs)
		std::cout<<i->id<<"\t"<<i->address<<"\t"<<i->localSize<<std::endl;
	for(int i=1;i<codeSize;i++){
		printf("%d:", code[i].srcLine);
		printf("\t%d", code[i].opcode);
		printf("\t%d:", code[i].result.type);
		printf("%d", code[i].result.val);
		printf("\t%d:", code[i].arg1.type);
		printf("%d", code[i].arg1.val);
		printf("\t%d:", code[i].arg2.type);
		printf("%d\n", code[i].arg2.val);
	}
}