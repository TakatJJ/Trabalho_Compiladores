#include "asm.hpp"



string ASM::generate_literals(string asm_code) { //literais char string e inteiros começam com _@
    for (auto const& x : symbols_table) {
        if (x.second.type == SYMBOL_LIT_STRING) {
            asm_code += "\t.globl	_@" + x.first.substr(1,x.first.size()-2) + ":\n" + "\t.data\n\t.align 4\n_@"+ x.first.substr(1,x.first.size()-2) +":\n\t.ascii \""+ x.second.text.substr(1, x.first.size()-2) +"\\0\"\n";
        }
        else if (x.second.type == SYMBOL_LIT_CHAR) {
            asm_code += "\t.globl	_@" +x.first.substr(1,x.first.size()-2) + ":\n" + "\t.data\n\t.align 4\n_@"+ x.first.substr(1,x.first.size()-2) +":\n\t.long " + to_string(int(x.second.text.at(1))) + "\n";
        }
        else if (x.second.type == SYMBOL_LIT_INTEGER) {
            asm_code += "\t.globl	_@" + x.first + ":\n" + "\t.data\n\t.align 4\n_@"+ x.first +":\n\t.long "+ x.second.text.substr(1) +"\n";
        }
    }
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
    asm_code += generate_literals(asm_code);
    asm_code += "\t.section .rdata,\"dr\"\nLC0:\n\t.ascii \"%d\\0\"\nLC1:\n\t.ascii \"%c\\0\"\n";
    // ofstream output_file("output.asm");
    for (TAC* tac : tacs) {
        // Generate assembly code for each TAC
        // ...
        switch(tac->type){
        case TAC_PRINT:{
            tac->res->text = resolveSymbol(tac->res);
            // cout << tac->res->text << endl;
            // cout << tac->res->data_type << endl;
            
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
    cout << asm_code << endl;
}