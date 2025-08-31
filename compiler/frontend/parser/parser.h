#ifndef COMPILA_PARSER_H
#define COMPILA_PARSER_H

#include "types.h"
#include "errors.h"
#include "lexer.h"

void testSymbole(CODE_LEX cl, CodeErreur erreur);
bool isDeclared();

void PROGRAM();
void BLOCK();
void CONSTS();
void VARS();
void INSTS();
void INST();
void AFFEC();
void SI();
void TANTQUE();
void ECRIRE();
void LIRE();
void EXPR();
void TERM();
void FACT();
void COND();
void RELOP();
void ADDOP();
void MULOP();
void POUR();
void REPETER();
void CAS();

extern MNEMONIQUES OP;
extern MNEMONIQUES CO;

#endif // COMPILA_PARSER_H