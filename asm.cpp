#include "asm.hpp"


string ASM::generate_temp(string asm_code) {
    for (auto const& x : symbols_table) {
        if (x.second.text.find("__temp") != string::npos) {
            asm_code += "\t.globl\t_" + x.first + "\n" + "\t.data\n\t.align 4\n_" + x.first + ":\n\t.long\t0\n";
        }
    }
    return asm_code;
}

string ASM::generate_literals(string asm_code) { //literais char string e inteiros começam com _@
    for (auto const& x : symbols_table) {
        if (x.second.type == SYMBOL_LIT_STRING) {
            asm_code += "\t.globl\t_@" + x.first.substr(1,x.first.size()-2) + ":\n" + "\t.data\n\t.align 4\n_@"+ x.first.substr(1,x.first.size()-2) +":\n\t.ascii\t\""+ x.second.text.substr(1, x.first.size()-2) +"\\0\"\n";
        }
        else if (x.second.type == SYMBOL_LIT_CHAR) {
            asm_code += "\t.globl\t_@" +x.first.substr(1,x.first.size()-2) + ":\n" + "\t.data\n\t.align 4\n_@"+ x.first.substr(1,x.first.size()-2) +":\n\t.long\t" + to_string(int(x.second.text.at(1))) + "\n";
        }
        else if (x.second.type == SYMBOL_LIT_INTEGER) {
            asm_code += "\t.globl\t_@" + x.first + ":\n" + "\t.data\n\t.align 4\n_@"+ x.first +":\n\t.long\t"+ x.second.text.substr(1) +"\n";
        }
    }
    return asm_code;
}

string ASM::create_asm_variable(TAC* tac) {
    if (tac->res->data_type == DATA_TYPE_INT)
        return "\tglobl\t_" + tac->res->text + "\n\t.data\n\t.align 4\n_" + tac->res->text + ":\n\t.long\t"+ tac->op1->text.substr(1) +"\n";
    else if (tac->res->data_type == DATA_TYPE_CHAR)
        return "\tglobl\t_" + tac->res->text + "\n\t.data\n\t.align 4\n_" + tac->res->text + ":\n\t.long\t" + to_string(int(tac->op1->text.at(1))) + "\n";
}

string ASM::create_asm_vector(TAC* tac, bool vec_has_init) {
    string code = "";
    if (!vec_has_init)
        code = "\tglobl\t_" + tac->res->text + "\n\t.data\n\t.align 4\n_" + tac->res->text + ":\n";
    if (tac->op1->data_type == DATA_TYPE_INT)
        code += "\t.long\t"+tac->op1->text.substr(1) + "\n";
    else if (tac->op1->data_type == DATA_TYPE_CHAR)
        code += "\t.long\t"+to_string(int(tac->op1->text.at(1))) + "\n";
    return code;
}

string ASM::generate_variables(string asm_code, vector<TAC*> tacs){
    bool found_vec = false;
    for (TAC* tac : tacs) {
        if (tac->type == TAC_DEC)
        {
            if (tac->res->type == SYMBOL_VAR)
            {
                found_vec = false;
                asm_code += create_asm_variable(tac);
            }
            else if (tac->res->type == SYMBOL_VEC)
            {
                if (!found_vec)
                {
                    asm_code += create_asm_vector(tac, found_vec);
                    found_vec = true;
                }
                else {
                    asm_code += create_asm_vector(tac, found_vec);
                }
            }
        }
    }
    cout << asm_code << endl;
    return asm_code;
}

string ASM::resolveSymbol(Symbol* symbol) {
    if (symbol->type == SYMBOL_LIT_STRING || symbol->type == SYMBOL_LIT_CHAR) {
        return "@" + symbol->text.substr(1, symbol->text.size()-2);
    }
    else if (symbol->type == SYMBOL_LIT_INTEGER) {
        return "@" + symbol->text;
    }
    else {
        return symbol->text;
    }
}

void ASM::generate_ASM(vector<TAC*> tacs) {
    string asm_code = "";

    asm_code = generate_temp(asm_code);
    asm_code = generate_literals(asm_code);
    asm_code = generate_variables(asm_code, tacs);

    asm_code += "\t.section .rdata,\"dr\"\nLC0:\n\t.ascii \"%d\\0\"\nLC1:\n\t.ascii \"%c\\0\"\n";
    // ofstream output_file("output.asm");
    for (TAC* tac : tacs) {
        // Generate assembly code for each TAC
        // ...
        switch(tac->type){
        case TAC_PRINT:{
            tac->res->text = resolveSymbol(tac->res);
            
            if (tac->res->data_type == DATA_TYPE_CHAR)
                asm_code+= "\tmovzbl	_"+tac->res->get_text()+", %eax\n\tmovsbl	%al, %eax\n\tmovl	%eax, (%esp)\n\tcall	_putchar\n";
            else if (tac->res->data_type == DATA_TYPE_STRING)
                asm_code += "\tmovl	_"+ tac->res->get_text() +", (%esp)\n\tcall	_printf\n";
            else if (tac->res->data_type == DATA_TYPE_INT)
                asm_code += "\tmovl	_"+tac->res->get_text()+", %eax\n\tmovl	%eax, 4(%esp)\n\tmovl	$LC0, (%esp)\n\tcall	_printf\n";
            break;
        }
        default:
            break;
        }
    }
    // cout << asm_code << endl;
}