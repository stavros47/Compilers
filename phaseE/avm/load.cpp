#include "headers/avm.h"
#include <assert.h>
#include <fstream>

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

		while(!infile.eof()){
			infile>>output;

			std::cout<<output<<"\n";				
		}
	}

	infile.close();
	
	return 0;
}
