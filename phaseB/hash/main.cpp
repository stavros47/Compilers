#include "symtable.h"


int main(){
	Symbol* s0 = new Symbol("0",2,12,3,false);
	Symbol* s1 = new Symbol("1",2,12,0,false);
	Symbol* s2 = new Symbol("2",0,9,0,false);
	Symbol* s3 = new Symbol("3",1,8,2,true);
	Symbol* s4 = new Symbol("4",2,12,1,false);
	Symbol* s5 = new Symbol("5",2,12,1,false);
	Symbol* s6 = new Symbol("6",2,12,1,false);
	Symbol* s7 = new Symbol("7",2,12,1,false);
	Symbol* s8 = new Symbol("8",2,12,2,false);
	Symbol* s9 = new Symbol("9",2,12,2,false);
	Symbol* s10= new Symbol("10",2,12,0,false);
	Symbol* s11= new Symbol("11",2,12,0,false);
	Symbol* s12= new Symbol("12",2,12,1,false);
	Symbol* s13= new Symbol("13",2,12,1,false);
	Symbol* s14= new Symbol("14",2,12,2,false);
	Symbol* s15= new Symbol("15",2,12,3,false);
	Symbol* s16= new Symbol("16",2,12,2,false);
	Symbol* s17= new Symbol("17",2,12,1,false);
	Symbol* s18= new Symbol("18",2,12,1,false);
	Symbol* s19= new Symbol("19",2,12,1,false);
	Symbol* s20= new Symbol("20",2,12,1,false);
	HashTable SymTable;

	SymTable.insert(s0);SymTable.insert(s1);
	SymTable.insert(s2);SymTable.insert(s3);
	SymTable.insert(s4);SymTable.insert(s5);
	SymTable.insert(s7);SymTable.insert(s8);
	SymTable.insert(s9);SymTable.insert(s10);
	SymTable.insert(s11);SymTable.insert(s12);
	SymTable.insert(s13);SymTable.insert(s14);
	SymTable.insert(s15);SymTable.insert(s16);
	SymTable.insert(s17);SymTable.insert(s18);
	SymTable.insert(s19);SymTable.insert(s20);
	SymTable.insert(s6);

	std::cout<<SymTable.toString()<<std::endl;
	std::cout<<SymTable.allscopestoString()<<std::endl;

	s20 = SymTable.lookup("10");
	if(s20){
		std::cout<<"done\n"<<s20->toString()<<std::endl;
	}else{
		std::cout<<"not found\n";
	}

	s20 = SymTable.lookup("100");
	if(s20){
		std::cout<<"done\n"<<s20->toString()<<std::endl;
	}else{
		std::cout<<"not found\n";
	}
	s20 = SymTable.lookup("11",1);
	if(s20){
		std::cout<<"done\n"<<s20->toString()<<std::endl;
	}else{
		std::cout<<"not found\n";
	}

	s20 = SymTable.lookup("18",2);
	if(s20){
		std::cout<<"done\n"<<s20->toString()<<std::endl;
	}else{
		std::cout<<"not found\n";
	}


return 0;
}
