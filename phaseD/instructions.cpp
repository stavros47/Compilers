#include "instructions.h"
#include <algorithm>
#include <iterator>
unsigned currInstruction = 1;
unsigned totalStrings = 0;
unsigned totalNumConsts = 0;
unsigned totalLibFuncs = 0;
unsigned totalUserFuncs = 0;
std::vector<std::string> strConsts;
std::vector<double> numConsts;
std::vector<std::string> libFuncs;
std::vector<userfunc*> userFuncs;
instruction* instructions;
std::fstream instructionfile;

unsigned consts_newstring (std::string s){
    std::vector<std::string>::iterator it = std::find(strConsts.begin(), strConsts.end(), s);
    if(it == strConsts.end()){
    	strConsts.push_back(s);
    	return totalStrings++;
    }
    
    return it - strConsts.begin();
}
unsigned consts_newnumber (double n){
    numConsts.push_back(n);
    
    return totalNumConsts++;
}
unsigned libfuncs_newused (std::string s){
    libFuncs.push_back(s);

    return totalLibFuncs++;
}
unsigned userfuncs_newfunc (Symbol* sym){
    unsigned position = 0;
    for(userfunc *currFunc : userFuncs){
        if(currFunc->id == sym->name){
            return position;
        }
        position++;
    }

    userfunc *usrFunc = new userfunc();
    usrFunc->address = sym->function.iaddress;
    usrFunc->localSize = sym->function.totallocals;
    usrFunc->id = sym->name;
    userFuncs.push_back(usrFunc);
    
    return totalUserFuncs++;
}
template <typename T>
void vector_to_file(std::vector<T> constArray, std::string name){
    //instructionfile <<name<< std::endl;
    instructionfile<<constArray.size() << std::endl;
    for(int i=0;i<constArray.size();i++){
          instructionfile<<constArray[i]<<"\n";
    }
}

template <>
void vector_to_file<userfunc*>(std::vector<userfunc*> constArray, std::string name){
   // instructionfile <<name<< std::endl;
    instructionfile<<constArray.size() << std::endl;
    for(int i=0;i<constArray.size();i++){
          instructionfile<<constArray[i]->id<<" "<<constArray[i]->address<<" "<<constArray[i]->localSize<<"\n";
    }
}

void make_instructions(quad* quadsArray){
    instructions =(instruction*) malloc((nextquadlabel())*sizeof(instruction));

    for(int i = 1; i < nextquadlabel(); i++){
        generators[quadsArray[i].op](&quadsArray[i]);
    }

    generate_output();
}
void generate_output(){

    instructionfile.open("instructionfile.txt",std::ios::out);
    instructionfile << MAGIC_NUMBER << std::endl;
    //Write arrays
    vector_to_file(strConsts,"strConsts");
    vector_to_file(numConsts,"numConsts");
    vector_to_file(libFuncs,"libFuncs");
    vector_to_file(userFuncs,"userFuncs");
   
    instructionfile <<"\n"<<instr_to_String()<<std::endl;

    instructionfile.close();
}

unsigned nextinstructionlabel(){
    return currInstruction;
}

void emit_instruction(instruction t){
        instructions[currInstruction++] = t;
}


void make_operand(expr* e, vmarg* arg){
   // std::cout<<e->sym->name<<std::endl;    

        switch (e->type){
            case var_e :
            case tableitem_e:
            case arithexpr_e:
            case assignexpr_e:
            case boolexpr_e:
            case newtable_e: {

                assert(e->sym);
                arg->val= e->sym->offset;

                switch (e->sym->scopespace){
                    case programVar: arg->type=global_a; break;
                    case functionLocal: arg->type = local_a; break;
                    case formalArg: arg->type = formal_a; break;
                    default: assert(0);

                }
                break;
            }
            case constbool_e:{
                arg->val = e->boolConst;
                arg->type = bool_a; break;
            }
            case conststring_e:{
                arg->val = consts_newstring(e->strConst);
                arg->type = string_a; break;
            }
            case constnum_e:{
                arg->val = consts_newnumber(e->numConst);
                arg->type = number_a; break;
            }
            case nil_e:{
                arg->type = nil_a; break;
            }
            case programfunc_e:{
                arg->type = userfunc_a;
                //alternativly.. arg->val=e->sym->taddress;
                arg->val = userfuncs_newfunc(e->sym); break;
            }
            case libraryfunc_e:{
                arg->val = libfuncs_newused(e->sym->name);
                arg->type = libfunc_a; break;
            }
            default: std::cout<<e->type<<"dammee\n";assert(0);
        }
    
   

}


void make_numberoperand(vmarg* arg, double val){
    arg->val = consts_newnumber(val);
    arg->type = number_a;
}

void make_booloperand(vmarg* arg, unsigned val){
    arg->val = val;
    arg->type = bool_a;
}

void make_retvaloperand(vmarg* arg){
    arg->type= retval_a;
}

generator_func_t generators[] = {
    generate_ASSIGN ,
    generate_ADD ,
    generate_SUB ,
    generate_MUL ,
    generate_DIV ,
    generate_MOD ,
    generate_NOT ,
    generate_IF_EQ ,
    generate_IF_NOTEQ ,
    generate_IF_LESSEQ ,
    generate_IF_GREATEREQ,
    generate_IF_LESS ,
    generate_IF_GREATER ,
    generate_CALL ,
    generate_PARAM ,
    generate_RETURN ,
    generate_GETRETVAL ,
    generate_FUNCSTART , 
    generate_FUNCEND ,
    generate_NEWTABLE ,
    generate_TABLEGETELEM ,
    generate_TABLESETELEM ,
    generate_JUMP ,
    generate_NOP  
};

void generate (vmopcode op,quad* quad) {
	instruction *t = new instruction();
	t->opcode = op;
    if(quad->arg1){
        make_operand(quad->arg1, &(t->arg1));
    }else{
         t->arg1.type = nil_a;
    }
    if(quad->arg2){
        make_operand(quad->arg2, &(t->arg2));
    }else{
       t->arg2.type = nil_a;
    }
    if(quad->result){
        make_operand(quad->result, &(t->result));
    }else{
         t->result.type = nil_a;
    }
	
	
	
	quad->label = nextinstructionlabel(); //changed taddress to label
	emit_instruction(*t);
   
} 

void generate_ADD (quad* quad) { generate(add_v, quad); }
void generate_SUB (quad* quad) { generate(sub_v, quad); }
void generate_MUL (quad* quad) { generate(mul_v, quad); }
void generate_DIV (quad* quad) { generate(div_v, quad); }
void generate_MOD (quad* quad) { generate(mod_v, quad); }
void generate_NEWTABLE (quad* quad) { generate(newtable_v, quad); }
void generate_TABLEGETELEM (quad* quad) { generate(tablegetelem_v, quad); }
void generate_TABLESETELEM (quad* quad) { generate(tablesetelem_v, quad); }
void generate_ASSIGN (quad* quad) 	{ generate(assign_v, quad); }
void generate_NOT (quad* quad)	{ instruction t; t.opcode=nop_v; emit_instruction(t); } 
void generate_NOP (quad* quad)	{ instruction t; t.opcode=nop_v; emit_instruction(t); } 


void generate_relational (vmopcode op,quad* quad) { //not declared in .h ??
	instruction t;
	t.opcode = op;
    //std::cout << t.opcode <<std::endl;
    if(quad->arg1){
       make_operand(quad->arg1, &t.arg1);
    }else{
         t.arg1.type = nil_a;
    }
	if(quad->arg2){
      make_operand(quad->arg2, &t.arg2);
    }else{
         t.arg2.type = nil_a;
    }
	

	t.result.type = label_a;
    t.result.val = quad->label;
	
	quad->label = nextinstructionlabel(); //taddres t label
	emit_instruction(t);
}

void generate_JUMP (quad* quad)		{ generate_relational(jeq_v, quad); } //Note: jump to jeq_v
void generate_IF_EQ (quad* quad) 		{ generate_relational(jeq_v, quad); }
void generate_IF_NOTEQ(quad* quad) 	{ generate_relational(jne_v, quad); }
void generate_IF_GREATER (quad* quad) 	{ generate_relational(jgt_v, quad); }
void generate_IF_GREATEREQ(quad* quad) 	{ generate_relational(jge_v, quad); }
void generate_IF_LESS (quad* quad) 		{ generate_relational(jlt_v, quad); }
void generate_IF_LESSEQ (quad* quad) 	{ generate_relational(jle_v, quad); }

void generate_PARAM(quad* quad) {
	quad->label = nextinstructionlabel();
	instruction t;
	t.opcode = pusharg_v;
    if(quad->result){
        make_operand(quad->result, &t.result);
    }else{
        t.result.type = nil_a;
    }
	
    t.arg1.type = t.arg2.type = nil_a;
	emit_instruction(t);
}

void generate_CALL(quad* quad) {
	quad->label = nextinstructionlabel();
	instruction t;
	t.opcode = call_v;
	make_operand(quad->result, &t.result);
    t.arg1.type = t.arg2.type = nil_a;
	emit_instruction(t);
}

void generate_GETRETVAL(quad* quad) {
	//quad->label = nextinstructionlabel();
	instruction t;
	t.opcode = assign_v;
    if(quad->result){
      	make_operand(quad->result, &t.result);
    }else{
         t.result.type = nil_a;
    }
	make_retvaloperand(&t.arg1);
    t.arg2.type = nil_a; 

	emit_instruction(t);
}

void generate_FUNCSTART (quad* quad){
    // Symbol* f = quad->result->sym;
    // f->label = nextinstructionlabel();
    // quad->label = nextinstructionlabel();

    // userfunctions.add(f->name,f->function->taddress,f->function->totallocals);
    // push(label,f);

    instruction t;
    t.opcode = funcenter_v;
    make_operand(quad->result,&t.result);
    t.arg1.type = t.arg2.type = nil_a;
    emit_instruction(t);
}
void generate_RETURN (quad* quad){
    //quad->taddress = nextinstructionlabel();
    
    instruction t;
    t.opcode = assign_v;
    make_retvaloperand(&t.result);
    if(quad->result){
      make_operand(quad->result,&t.arg1);
    }else{
        t.arg1.type = nil_a;
    }
    t.arg2.type = nil_a;   
    
     //t.arg1.type = t.arg2.type = nil_a;
    emit_instruction(t); 

}
void generate_FUNCEND (quad* quad){
    instruction t;
    t.opcode = funcexit_v;
    make_operand(quad->result,&t.result);
    t.arg1.type = t.arg2.type = nil_a;
    emit_instruction(t);
}

std::string vmopcode_toString(vmopcode type){
	switch(type){
		case 0:	return "assign_v";
		case 1: return "add_v";
		case 2:	return "sub_v";
		case 3:	return "mul_v";
		case 4:	return "Div_v";
		case 5:	return "mod_v";
		case 6:	return "Not_v";
		case 7:	return "jeg_v";
		case 8:	return "jne_v";
		case 9:	return "jle_v";
		case 10:	return "jge_v";
		case 11:	return "jlt_v";
		case 12:	return "jgt_v";
		case 13:	return "call_v";
		case 14:	return "pusharg_v";
		case 15:	return "funcenter_v";
		case 16:	return "funcexit_v";
		case 17:	return "newtable_v";
		case 18:	return "tablegetelem_v";
		case 19:	return "tablesetelem_v";
	
		default:	assert(0);
	}
}

std::string vmarg_toString(vmarg temp){
    std::string out;
    out = std::to_string(temp.type) + " ";
	switch(temp.type){
        case label_a:
        case bool_a:
        case global_a:
        case formal_a:
        case local_a :  out += std::to_string(temp.val);
                        return out;
        case retval_a: return "retVal"; //??
		case number_a:  out += std::to_string(temp.val) + ":";
                        out += std::to_string(numConsts[temp.val]);
                        return out; 
		case userfunc_a: out += std::to_string(temp.val) + ":";
                         out += userFuncs[temp.val]->id;
                         return out;
		case libfunc_a: return libFuncs[temp.val]; 
		case string_a:	out += std::to_string(temp.val) + ":";
                        out += strConsts[temp.val];
                        return out;
        case nil_a: return "nil_a";

		default: return "INVALID";
	}
}

std::string instr_to_String(){
	std::ostringstream buffer;
	int width = 15;
	// buffer<<"---------------------------------------------------------------------------------\n";
	// buffer<<"#Instr"<<std::setw(width)<<"OpCode"<<std::setw(width)<<"result"<<std::setw(width)<<"arg1"<<std::setw(width)<<"arg2"/*<<std::setw(width)<<"label"*/<<std::endl;
	// buffer<<"---------------------------------------------------------------------------------\n";
	
	for(int i=1;i < nextinstructionlabel();i++){
		buffer<<std::setw((i > 9) ? 1 : 2)<<std::to_string(i)<<": ";

		int labelWidth = 60;
		buffer<<std::setw(width)<<vmopcode_toString(instructions[i].opcode);

		//if(instructions[i].result){
			buffer<<std::setw(15)<<vmarg_toString(instructions[i].result);
			labelWidth -= 15;
		//}
		//if(instructions[i].arg1){
			buffer<<std::setw(15)<<vmarg_toString(instructions[i].arg1);
			labelWidth -= 15;
	//	}
	//	if(instructions[i].arg2){
			buffer<<std::setw(15)<<vmarg_toString(instructions[i].arg2);
			labelWidth -= 15;
	//	}
		// if(quads[i].label != 0){
		// 	buffer<<std::setw(labelWidth)<<quads[i].label;
		// }

		buffer<<std::endl;

	}
	//buffer<<"--------------------------------------------------------------------------------\n";

	return buffer.str();
}
