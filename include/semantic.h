#ifndef COMPILA_SEMANTIC_H
#define COMPILA_SEMANTIC_H

#include "types.h"
#include "errors.h"

bool isDeclared();
void IsIdAlreadyUsed(TSYM TIDF);
void isConst();
void isPrograID();
void ANALYSE_SEMENTIC();
int getAdresse();
int getValue();

#endif // COMPILA_SEMANTIC_H