#include "asm.hpp"


string ASM::generate_temp(string asm_code) {
    for (auto const& x : symbols_table) {
        if (x.second.text.find("__temp") != string::npos) {
            asm_code += "\t.globl\t_" + x.first + "\n" + "\t.data\n\t.align\t4\n_" + x.first + ":\n\t.long\t0\n";
        }
    }
    return asm_code;
}

string ASM::generate_literals(string asm_code) { //literais char string e inteiros começam com __
    for (auto const& x : symbols_table) {
        if (x.second.type == SYMBOL_LIT_STRING) {
            asm_code += "\t.globl\t__" + x.first.substr(1,x.first.size()-2) + "\n" + "\t.data\n\t.align\t4\n__"+ x.first.substr(1,x.first.size()-2) +":\n\t.ascii\t\""+ x.second.text.substr(1, x.first.size()-2) +"\\0\"\n";
        }
        else if (x.second.type == SYMBOL_LIT_CHAR) {
            asm_code += "\t.globl\t__" +x.first.substr(1,x.first.size()-2) + "\n" + "\t.data\n\t.align\t4\n__"+ x.first.substr(1,x.first.size()-2) +":\n\t.long\t" + to_string(int(x.second.text.at(1))) + "\n";
        }
        else if (x.second.type == SYMBOL_LIT_INTEGER) {
            asm_code += "\t.globl\t__" + x.first.substr(1) + "\n" + "\t.data\n\t.align\t4\n__"+ x.first.substr(1) +":\n\t.long\t"+ x.second.text.substr(1) +"\n";
        }
    }
    return asm_code;
}

string ASM::create_asm_variable(TAC* tac) {
    if (tac->res->data_type == DATA_TYPE_INT)
        return "\t.globl\t_" + tac->res->text + "\n\t.data\n\t.align\t4\n_" + tac->res->text + ":\n\t.long\t"+ tac->op1->text.substr(1) +"\n";
    else if (tac->res->data_type == DATA_TYPE_CHAR)
        return "\t.globl\t_" + tac->res->text + "\n\t.data\n\t.align\t4\n_" + tac->res->text + ":\n\t.long\t" + to_string(int(tac->op1->text.at(1))) + "\n";
}

string ASM::create_asm_vector_empty(TAC* tac) {
    string code = "\t.globl\t_" + tac->res->text + "\n\t.data\n\t.align\t4\n_" + tac->res->text + ":\n";
    for (int i=0 ; i<tac->res->vector_size; i++)
    {
        code += "\t.long\t0\n";
    }
    return code;
}

string ASM::create_asm_vector(TAC* tac) {
    string code = "";
    if (tac->op2->get_text() == "#0")
        code = "\t.globl\t_" + tac->res->text + "\n\t.data\n\t.align\t4\n_" + tac->res->text + ":\n";
    if (tac->op1->data_type == DATA_TYPE_INT)
        code += "\t.long\t"+tac->op1->text.substr(1) + "\n";
    else if (tac->op1->data_type == DATA_TYPE_CHAR)
        code += "\t.long\t"+to_string(int(tac->op1->text.at(1))) + "\n";
    return code;
}

string ASM::generate_variables(string asm_code, vector<TAC*> tacs){
    for (TAC* tac : tacs) {
        switch(tac->type){
        case TAC_DEC:
            {
                if (tac->res->type == SYMBOL_VAR)
                {
                    asm_code += create_asm_variable(tac);
                }
                else if (tac->res->type == SYMBOL_VEC)
                {
                    if (!tac->op2)
                        asm_code += create_asm_vector_empty(tac);
                    else
                        asm_code += create_asm_vector(tac);
                }
            }
            break;
        case TAC_PARAM:
            asm_code += create_asm_variable(tac);
            break;
        default:
            break;
        }
    }
    // cout << asm_code << endl;
    return asm_code;
}

string ASM::resolveSymbol(Symbol* symbol) {
    if (symbol->type == SYMBOL_LIT_STRING || symbol->type == SYMBOL_LIT_CHAR) {
        if (symbol->text.at(0) == '_')
            return symbol->text;
        return "_" + symbol->text.substr(1, symbol->text.size()-2);
    }
    else if (symbol->type == SYMBOL_LIT_INTEGER) {
        if (symbol->text.at(0) == '_')
            return symbol->text;
        return "_" + symbol->text.substr(1);
    }
    else {
        return symbol->text;
    }
}

string ASM::cleanVectorIndex(string text) {
    if(text.at(0) == '_')
        text = text.substr(1);
    if(text.at(0) == '#')
        text = text.substr(1);
    return text;
}

void ASM::generate_ASM(vector<TAC*> tacs) {
    string asm_code = "";
    int Lindex = 0;
    vector<string> argList = {};
    int param_num = 0;
    vector<string> params = {};

    asm_code = generate_temp(asm_code);
    asm_code = generate_literals(asm_code);
    asm_code = generate_variables(asm_code, tacs);

    asm_code += "\t.section\t.rdata,\"dr\"\nLC0:\n\t.ascii\t\"%d\\0\"\nLC1:\n\t.ascii\t\"%c\\0\"\n";
    ofstream output_file("assembly.s");
    for (TAC* tac : tacs) {
        
        switch(tac->type){
        
        case TAC_BEGINFUNC:
            param_num = tac->res->param_count;
            if (tac->res->get_text() == "main")
                asm_code+="\t.def\t___main;\t.scl\t2;\t.type	32;\t.endef\n";
            asm_code += "\t.text\n\t.globl\t_"+tac->res->get_text()+"\n\t.def\t_"+tac->res->get_text()+";\t.scl\t2;\t.type\t32;\t.endef\n_"+tac->res->get_text()+":\n\tpushl\t%ebp\n\tmovl\t%esp,\t%ebp\n\tpushl\t%edi\n";
            if (tac->res->get_text() == "main")
                asm_code += "\tandl\t$-16,\t%esp\n\tcall\t___main\n";

            break;
        case TAC_PRINT:{
            cout << tac->res->get_text() << " " << tac->res->data_type << endl;
            tac->res->text = resolveSymbol(tac->res);
            if (tac->res->data_type == DATA_TYPE_CHAR)
                asm_code+= "\tmovzbl\t_"+tac->res->get_text()+",\t%eax\n\tmovsbl\t%al,\t%eax\n\tmovl\t%eax,\t(%esp)\n\tcall\t_putchar\n";
            else if (tac->res->data_type == DATA_TYPE_STRING)
                asm_code += "\tmovl\t$_"+ tac->res->get_text() +",\t(%esp)\n\tcall\t_printf\n";
            else if (tac->res->data_type == DATA_TYPE_INT)
                asm_code += "\tmovl\t_"+tac->res->get_text()+",\t%eax\n\tmovl\t%eax,\t4(%esp)\n\tmovl\t$LC0,\t(%esp)\n\tcall\t_printf\n";
            break;
        }
        case TAC_VEC:{
            string index = resolveVecIndex(tac->op2);
            if (tac->op2->get_type() == SYMBOL_VAR)
                asm_code+= "\tmovl\t_"+tac->op2->get_text()+",\t%eax\n";
            
            asm_code += "\tmovl\t_"+tac->op1->get_text()+index+", %eax\n\tmovl\t%eax,\t_"+ tac->res->get_text() + "\n";
            break;
        }
        case TAC_MOVE:
            tac->res->text = resolveSymbol(tac->res);
            asm_code += "\tmovl\t_"+tac->op1->get_text()+",\t%eax\n\tmovl\t%eax,\t_"+tac->res->text + "\n";
            break;
        case TAC_ADD:
            tac->op1->text = resolveSymbol(tac->op1);
            tac->op2->text = resolveSymbol(tac->op2);
            asm_code += "\tmovl\t_"+tac->op1->get_text()+",\t%edx\n\tmovl\t_"+tac->op2->get_text()+",\t%eax\n\taddl\t%edx,\t%eax\n\tmovl\t%eax,\t_"+tac->res->get_text()+"\n";
            break;
        case TAC_SUB:
            tac->op1->text = resolveSymbol(tac->op1);
            tac->op2->text = resolveSymbol(tac->op2);
            asm_code += "\tmovl\t_"+tac->op1->get_text()+",\t%edx\n\tmovl\t_"+tac->op2->get_text()+",\t%eax\n\tsubl\t%edx,\t%eax\n\tmovl\t%eax,\t_"+tac->res->get_text()+"\n";
            break;
        case TAC_MUL:
            tac->op1->text = resolveSymbol(tac->op1);
            tac->op2->text = resolveSymbol(tac->op2);
            asm_code += "\tmovl\t_"+tac->op1->get_text()+",\t%edx\n\tmovl\t_"+tac->op2->get_text()+",\t%eax\n\timull\t%edx,\t%eax\n\tmovl\t%eax,\t_" + tac->res->get_text() + "\n";
            break;
        case TAC_DIV:
            tac->op1->text = resolveSymbol(tac->op1);
            tac->op2->text = resolveSymbol(tac->op2);
            asm_code += "\tmovl\t_"+tac->op1->get_text()+",\t%eax\n\tcltd\n\tidivl\t_"+tac->op2->get_text()+"\n\tmovl\t%eax,\t_"+tac->res->get_text()+"\n";
            break;
        case TAC_EQUAL:
            tac->op1->text = resolveSymbol(tac->op1);
            tac->op2->text = resolveSymbol(tac->op2);
            asm_code += "\tmovl\t_"+tac->op1->get_text()+",\t%edx\n\tmovl\t_"+tac->op2->get_text()+",\t%eax\n\tcmpl\t%eax,\t%edx\n\tsete\t%al\n\tmovb\t%al,\t"+tac->res->get_text()+"\n";
            break;
        case TAC_BIGGER:
            tac->op1->text = resolveSymbol(tac->op1);
            tac->op2->text = resolveSymbol(tac->op2);
            asm_code += "\tmovl\t_"+tac->op1->get_text()+",\t%edx\n\tmovl\t_"+tac->op2->get_text()+",\t%eax\n\tcmpl\t%eax,\t%edx\n\tsetg\t%al\n\tmovb\t%al,\t_"+tac->res->get_text()+"\n";
            break;
        case TAC_SMALLER:
            tac->op1->text = resolveSymbol(tac->op1);
            tac->op2->text = resolveSymbol(tac->op2);
            asm_code += "\tmovl\t_"+tac->op1->get_text()+",\t%edx\n\tmovl\t_"+tac->op2->get_text()+",\t%eax\n\tcmpl\t%eax,\t%edx\n\tsetl\t%al\n\tmovb\t%al,\t_"+tac->res->get_text()+"\n";
            break;
        case TAC_AND:
            tac->op1->text = resolveSymbol(tac->op1);
            tac->op2->text = resolveSymbol(tac->op2);
            asm_code += "\tmovl\t_"+tac->op1->get_text()+",\t%eax\n\ttestl\t%eax,\t%eax\n\tje\tL"+to_string(Lindex)+"\n\tmovl\t_"+tac->op2->get_text()+",\t%eax\n\ttestl\t%eax,\t%eax\n\tje\tL"+to_string(Lindex+1)+"\n\tmovl\t1,\t%eax\n\tjmp\tL"+to_string(Lindex+1)+"\nL"+to_string(Lindex)+":\n\tmovl\t0,\t%eax\nL"+to_string(Lindex+1)+":\n\tmovb\t%al,\t_"+tac->res->get_text()+"\n";
            Lindex += 2;
            break;
        case TAC_OR:
            tac->op1->text = resolveSymbol(tac->op1);
            tac->op2->text = resolveSymbol(tac->op2);
            asm_code += "\tmovl\t_"+tac->op1->get_text()+",\t%eax\n\ttestl\t%eax,\t%eax\n\tjne\tL"+to_string(Lindex)+"\n\tmovl\t_"+tac->op2->get_text()+",\t%eax\n\ttestl\t%eax,\t%eax\n\tje\tL"+to_string(Lindex+1)+"\nL"+to_string(Lindex)+":\n\tmovl\t1,\t%eax\n\tjmp\tL"+to_string(Lindex+2)+"\nL"+to_string(Lindex+1)+":\n\tmovl\t0,\t%eax\nL"+to_string(Lindex+2)+":\n\tmovb\t%al,\t_"+tac->res->get_text()+"\n";
            Lindex += 3;
            break;
        case TAC_NOT:
            tac->op1->text = resolveSymbol(tac->op1);
            asm_code += "\tmovzbl\t_"+tac->op1->get_text()+",\t%eax\n\txorl\t1,\t%eax\n\tmovb\t%al,\t_"+tac->res->get_text()+"\n";
            break;
        case TAC_IFZ:
            tac->op1->text = resolveSymbol(tac->op1);
            asm_code += "\tmovzbl\t_"+tac->op1->get_text()+", %eax\n\ttestb\t%al, %al\n\tje\t_"+tac->res->get_text()+"\n";
            break;
        case TAC_LABEL:
            asm_code += "_"+tac->res->get_text()+":\n";
            break;
        case TAC_JUMP:
            asm_code += "\tjmp\t_"+tac->res->get_text()+"\n";
            break;
        case TAC_VEC_WRITE:{
            tac->op2->text = resolveSymbol(tac->op2);
            string index = resolveVecIndex(tac->op1);
            if (tac->op1->get_type() == SYMBOL_VAR)
                asm_code+= "\tmovl\t_"+tac->op1->get_text()+",\t%edx\n";
            asm_code+= "\tmovl\t_"+tac->op2->get_text()+",\t%eax\n";
            asm_code += "\tmovl\t%eax,\t_"+tac->res->get_text()+index+"\n";
            break;
        }
        case TAC_PARAM:
            params.push_back(tac->res->get_text());
            if (param_num == params.size())
            {
                for (int index = 0; index < params.size(); index++)
                {
                    asm_code += "\tmovl\t"+to_string((4*(index+2)) )+"(%ebp),\t%eax\n\tmovl\t%eax,\t_"+params[index]+"\n";
                }
                params.clear();
            }
            break;
        case TAC_ARG:
            tac->res->text = resolveSymbol(tac->res);
            argList.push_back(tac->res->get_text());
            break;
        case TAC_CALL:{
            int stack_size = 4*argList.size();
            if (argList.size() > 0){
                asm_code += "\tsubl\t$"+to_string(stack_size)+",\t%esp\n";
            }
            for (int index = 0; index < argList.size(); index++)
            {
                asm_code+= "movzbl\t_"+argList[index]+", %eax\n\tmovsbl\t%al,\t%eax\n\tmovl\t%eax,\t"+to_string(stack_size - (4*(index+1)))+"(%esp)\n";
            }
            asm_code += "\tcall\t_"+tac->op1->get_text()+"\n";
            asm_code += "\tmovl\t%eax,\t_"+tac->res->get_text()+"\n";
            argList.clear();
            break;
        }
        case TAC_RET:
            tac->res->text = resolveSymbol(tac->res);
            asm_code += "\tmovl\t_"+tac->res->get_text()+",\t%eax\n\tleave\n\tret\n";
            break;
        case TAC_ENDFUNC:
            break;
        default:
            break;
        }
    }
    cout << asm_code << endl;
    output_file << asm_code;
    output_file.close();
}

string ASM::resolveVecIndex (Symbol *symbol) {
    string index = "";
    if (symbol->get_type() == SYMBOL_VAR){
                index = "(,%edx,4)";
            }
            else {
                index = "+"+to_string(stoi(cleanVectorIndex(symbol->text))*4);
            }
    return index;
}