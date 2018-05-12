#include "instructions.h"

void maike_operand(expr* e, vmarg* arg){
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
         case libfunc_a:{
            arg->val = libfuncs_newused(e->sym->name);
            arg->type = libfunc_a; break;
        }
        default: assert(0);
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

generate (vmopcode op,quad* quad) {
	instruction t;
	t.opcode = op;
	make_operand(quad->arg1, t.arg1);
	make_operand(quad->arg2, t.arg2);
	make_operand(quad->result, t.result);
	quad->taddress = nextinstructionlabel();
	emit_instruction(t);
} 

generate_ADD (quad* quad) { generate(add_v, quad); }
generate_SUB (quad* quad) { generate(sub_v, quad); }
generate_MUL (quad* quad) { generate(mul_v, quad); }
generate_DIV (quad* quad) { generate(div_v, quad); }
generate_MOD (quad* quad) { generate(mod_v, quad); }
generate_NEWTABLE (quad* quad) { generate(newtable_v, quad); }
generate_TABLEGETELM (quad* quad) { generate(tablegetelem_v, quad); }
generate_TABLESETELEM (quad* quad) { generate(tablesetelem_v, quad); }
generate_ASSIGN (quad* quad) 	{ generate(assign_v, quad); }
generate_NOP ()	{ instruction t; t.opcode=nop; emit_instruction(t); } 


generate_relational (vmopcode op,quad* quad) {
	instruction t;
	t.opcode = op;
	make_operand(quad->arg1, t.arg1);
	make_operand(quad->arg2, t.arg2);
 
	t.result.type = label_a;
	if quad->label jump target < currprocessedquad() then
		t.result.value = quads[quad->label]->taddress;
	else
		add_incomplete_jump(nextinstructionlabel(), quad->label);
	quad->taddress = nextinstructionlabel();
	emit_instruction(t);
}

generate_JUMP (quad* quad)		{ generate_relational(jump, quad); }
generate_IF_EQ (quad* quad) 		{ generate_relational(jeq, quad); }
generate_IF_NOTEQ(quad* quad) 	{ generate_relational(jne, quad); }
generate_IF_GREATER (quad* quad) 	{ generate_relational(jgt, quad); }
generate_IF_GREATEREQ(quad* quad) 	{ generate_relational(jge, quad); }
generate_IF_LESS (quad* quad) 		{ generate_relational(jlt, quad); }
generate_IF_LESSEQ (quad* quad) 	{ generate_relational(jle, quad); }

generate_PARAM(quad* quad) {
	quad*->taddress = nextinstructionlabel();
	instruction t;
	t.opcode = pusharg;
	make_operand(quad*->arg1, &t.arg1);
	emit(t);
}
 
generate_CALL(quad* quad) {
	quad->taddress = nextinstructionlabel();
	instruction t;
	t.opcode = callfunc;
	make_operand(quad->arg1, &t.arg1);
	emit(t);
}
 
generate_GETRETVAL(quad* quad) {
	quad->taddress = nextinstructionlabel();
	instruction t;
	t.opcode = assign;
	make_operand(quad->result, &t.result);
	make_retvaloperand(&t.arg1);
	emit(t);
}

/*extern void generate_FUNCSTART (quad* quad){
    Symbol* f = quad->result->sym;
    f->taddress = nextinstructionlabel();
    quad->taddress = nextinstructionlabel();

    userfunctions.add(f->name,f->function->taddress,f->function->totallocals);
    push(funcstack,f);

    instruction t;
    t.opcode = enterfunc;
    make_operand(quad->result,t.result);
    emit_instruction(t);
}
extern void generate_RETURN (quad* quad){
    quad->taddress = nextinstructionlabel();
    
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
}
extern void generate_FUNCEND (quad*){
    f = pop(funcstack);
    quad->taddress = nextinstructionlabel();
    instructions t;
    t.opcode = exitfunc;
    make_operand(quad->result,t.result);
    emit_instruction(t);
}*/
