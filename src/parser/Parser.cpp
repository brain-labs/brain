/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Brain, 2016.
 */

#include "Parser.h"
#include "../ast/instr/ShiftInstr.h"
#include "../ast/instr/IncrementInstr.h"
#include "../ast/instr/InputInstr.h"
#include "../ast/instr/OutputInstr.h"
#include "../ast/instr/LoopInstr.h"
#include "../ast/instr/ArithmeticInstr.h"
#include "../ast/instr/DebugInstr.h"
#include "../ast/instr/BreakInstr.h"
#include "../ast/instr/IfInstr.h"
#include "../ast/instr/FloatInstr.h"
#include "../ast/instr/MovInstr.h"

// Forward declaration of a static member
static bool has_done_then = false;

void Parser::parse(std::vector<Instr *> &instrs, int level)
{
    char c = 0;
    while ((c = _data[_index++]))  {
        Instr *instr = nullptr;
        if (ArgsOptions::instance()->get_optimization() ==
                BO_IS_OPTIMIZING_O1 && !instrs.empty()) {

            Instr *last_instruction = instrs.back();
            if (last_instruction->update_instruction(c)) {
                continue;
            }
        }

        switch (c)
        {
        case TT_SHIFT_LEFT:
            instr = new ShiftInstr(-1);
            break;
        case TT_SHIFT_RIGHT:
            instr = new ShiftInstr(1);
            break;
        case TT_SHIFT_JUMP:
            instr = new ShiftInstr();
            break;
        case TT_INCREMENT:
            instr = new IncrementInstr(1);
            break;
        case TT_DECREMENT:
            instr = new IncrementInstr(-1);
            break;
        case TT_OUTPUT:
            instr = new OutputInstr();
            break;
        case TT_INPUT:
            instr = new InputInstr();
            break;
        case TT_BEGIN_WHILE:
        {
            std::vector<Instr *> loop_instruction;
            parse(loop_instruction, level + 1);
            instr = new LoopInstr(loop_instruction, LT_WHILE);
            break;
        }
        case TT_END_WHILE:
        {
            if (level > 0) {
                // exit the recursivity.
                return;
            }

            break;
        }
        case TT_BEGIN_FOR:
        {
            std::vector<Instr *> loop_instruction;
            parse(loop_instruction, level + 1);
            instr = new LoopInstr(loop_instruction, LT_FOR);
            break;
        }
        case TT_END_FOR:
        {
            if (level > 0) {
                // exit the recursivity.
                return;
            }

            break;
        }
        case TT_IF_THEN:
        {
            std::vector<Instr *> if_instruction;
            parse(if_instruction, level + 1);
            instr = new IfInstr(if_instruction);
            break;
        }
        case TT_IF_ELSE:
        {
            if (!has_done_then) {
                if (level == 0) {
                    break;
                }

                _index--; // move one step back to read the ':' again
                has_done_then = true;
                return; // return to exit the 'then' recursivity
            }

            // do the else
            if (!instrs.empty()) {
                Instr *instr = instrs.back();

                if (instr->instruction_category() == ET_BRANCH) {
                    std::vector<Instr *> else_instruction;
                    parse(else_instruction, level + 1);
                    ((IfInstr *)instr)->set_else(else_instruction);
                }
            }

            has_done_then = false; // reset the flag
            break;
        }
        case TT_IF_END:
        {
            if (level > 0) {
                return;
            }

            break;
        }
        case TT_MUL:
            instr = new ArithmeticInstr(AT_MUL);
            break;
        case TT_DIV:
            instr = new ArithmeticInstr(AT_DIV);
            break;
        case TT_REM:
            instr = new ArithmeticInstr(AT_REM);
            break;
        case TT_DEBUG:
            instr = new DebugInstr();
            break;
        case TT_BREAK:
            instr = new BreakInstr();
            break;
        case TT_FLOAT:
            instr = new FloatInstr();
            break;
        case TT_MOV:
            instr = new MovInstr();
            break;
        default:
            // Ignored character
            continue;
        }

        if (instr) {
            instrs.push_back(instr);
        }
    }
}

void Parser::code_gen(llvm::Module *M, llvm::IRBuilder<> &B)
{
    ASTInfo::instance()->code_gen(M, B);

    for (auto& instr : _instrs) {
        instr->code_gen(M, B, nullptr);
    }
}

void Parser::debug_description(int level)
{
    for (auto& instr : _instrs) {
        std::cout << std::string(level * 2, ' ');
        instr->debug_description(level+1);
    }
}

void Parser::ast_code_gen()
{
    for (auto& instr : _instrs) {
        instr->ast_code_gen();
    }
}
