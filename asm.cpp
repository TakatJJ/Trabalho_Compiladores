#include "asm.hpp"



string ASM::generate_literals(string asm_code) {
    int lc_index = 0;

    for (auto const& x : symbols_table) {
        if (x.second.type == SYMBOL_LIT_STRING) {
            asm_code += "\t.globl	_" + x.first.substr(1, x.first.size()-2) + ":\n" + "\t.data\n\t.align 4\n_"+ x.first.substr(1, x.first.size()-2) +":\n\t.ascii \""+ x.second.text.substr(1, x.first.size()-2) +"\\0\"\n";
        }
        else if (x.second.type == SYMBOL_LIT_CHAR) {
            asm_code += "\t.globl	_" + x.first.substr(1, x.first.size()-2) + ":\n" + "\t.data\n\t.align 4\n_"+ x.first.substr(1, x.first.size()-2) +":\n\t.byte " + to_string(int(x.second.text.at(1))) + "\n";
        }
        else if (x.second.type == SYMBOL_LIT_INTEGER) {
            asm_code += "\t.globl	_" + x.first + ":\n" + "\t.data\n\t.align 4\n_"+ x.first +":\n\t.long "+ x.second.text.substr(1) +"\n";
        }
    }
    cout << asm_code << endl;
    return asm_code;
}

void ASM::generate_ASM(vector<TAC*> tacs) {
    string asm_code = "";
    asm_code += generate_literals(asm_code);
    // ofstream output_file("output.asm");
    for (TAC* tac : tacs) {
        // Generate assembly code for each TAC
        // ...
        switch(tac->type){
        case TAC_PRINT:
            asm_code += "movl	$_"+ tac->res->get_text() +", (%esp)\n\tcall	_printf";
            // cout << asm_code << endl;
            break;
        default:
            break;
        }
    }
}