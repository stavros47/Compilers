#include "instructions.h"

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

unsigned consts_newstring (std::string s){
    strConsts.push_back(s);

    return totalStrings++;
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
    userfunc *usrFunc = new userfunc();
    usrFunc->address = sym->function.iaddress;
    usrFunc->localSize = sym->function.totallocals;
    usrFunc->id = sym->name;
    userFuncs.push_back(usrFunc);
    
    return totalUserFuncs++;
}

void make_instructions(quad* quadsArray){
    instructions =(instruction*) malloc((nextquadlabel()-1)*sizeof(instruction));

    for(int i = 1; i < nextquadlabel(); i++){
        generators[quadsArray[i].op](&quadsArray[i]);
    }
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
            default: assert(0);
        }
    
   

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

void generate (vmopcode op,quad* quad) {
	instruction t;
	t.opcode = op;
   // std::cout<<expr_toString(qua)<<std::endl; 
	make_operand(quad->arg1, &t.arg1);
	make_operand(quad->arg2, &t.arg2);
	make_operand(quad->result, &t.result);
	quad->label = nextinstructionlabel(); //changed taddress to label
	emit_instruction(t);
   
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


void generate_relational (vmopcode op,quad* quad) {
	instruction t;
	t.opcode = op;
	make_operand(quad->arg1, &t.arg1);
	make_operand(quad->arg2, &t.arg2);

	t.result.type = label_a;
	// if quad->label jump target < currprocessedquad() {
    //     t.result.value = quads[quad->label]->taddress;   
    // }else{
    //     add_incomplete_jump(nextinstructionlabel(), quad->label);
    // }
		
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
	make_operand(quad->arg1, &t.arg1);
	emit_instruction(t);
}

void generate_CALL(quad* quad) {
	quad->label = nextinstructionlabel();
	instruction t;
	t.opcode = call_v;
	make_operand(quad->arg1, &t.arg1);
	emit_instruction(t);
}

void generate_GETRETVAL(quad* quad) {
	quad->label = nextinstructionlabel();
	instruction t;
	t.opcode = assign_v;
	make_operand(quad->result, &t.result);
	make_retvaloperand(&t.arg1);
	emit_instruction(t);
}

void generate_FUNCSTART (quad* quad){
/*    Symbol* f = quad->result->sym;
    f->taddress = nextinstructionlabel();
    quad->taddress = nextinstructionlabel();

    userfunctions.add(f->name,f->function->taddress,f->function->totallocals);
    push(funcstack,f);

    instruction t;
    t.opcode = enterfunc;
    make_operand(quad->result,t.result);
    emit_instruction(t);
*/}
void generate_RETURN (quad* quad){
  /*  quad->taddress = nextinstructionlabel();
    
    instruction t;
    t.opcode = assign;
    make_retvaloperand(t.result);
    make_operand(quad->arg1,t.arg1);

    emit_instruction(t); 

    f = top(funcstack);
    append(f->returnList,nextinstructionlabel());

    t.opcode = jump;
    reset_operand(t.arg1);
    reset_operand(t.arg2);
    t.result.type = label_a;
    emit_instruction(t);  
*/}
void generate_FUNCEND (quad*){
  /*  f = pop(funcstack);
    quad->taddress = nextinstructionlabel();
    instructions t;
    t.opcode = exitfunc;
    make_operand(quad->result,t.result);
    emit_instruction(t);
*/}

std::string vmopcode_toString(vmopcode type){
	switch(type){
		case 0:	return "assign";
		case 1: return "add";
		case 2:	return "sub";
		case 3:	return "mul";
		case 4:	return "Div";
		case 5:	return "mod";
		case 6:	return "Not";
		case 7:	return "if_eq";
		case 8:	return "if_noteq";
		case 9:	return "if_lesseq";
		case 10:	return "if_greatereq";
		case 11:	return "if_less";
		case 12:	return "if_greater";
		case 13:	return "call";
		case 14:	return "param";
		case 15:	return "funcstart";
		case 16:	return "funcend";
		case 17:	return "tablecreate";
		case 18:	return "tablegetelem";
		case 19:	return "tablesetelem";
	
		default:	assert(0);
	}
}

std::string vmarg_toString(vmarg temp){
	switch(temp.type){
	
		case number_a: return std::to_string(numConsts[temp.val]); 
		case userfunc_a:return userFuncs[temp.val]->id; 
		case libfunc_a: return libFuncs[temp.val]; 
		case string_a:	return strConsts[temp.val];

		default: return "INVALID";
	}

}

std::string instr_to_String(){
	std::ostringstream buffer;
	int width = 15;
	buffer<<"---------------------------------------------------------------------------------\n";
	buffer<<"#Quad"<<std::setw(width)<<"OpCode"<<std::setw(width)<<"result"<<std::setw(width)<<"arg1"<<std::setw(width)<<"arg2"<<std::setw(width)<<"label"<<std::endl;
	buffer<<"---------------------------------------------------------------------------------\n";
	
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
	buffer<<"--------------------------------------------------------------------------------\n";

	return buffer.str();
}
