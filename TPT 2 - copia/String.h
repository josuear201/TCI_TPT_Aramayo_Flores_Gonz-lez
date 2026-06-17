#ifndef STRING_H
#define STRING_H
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
typedef char* str;

str load2(const char* s);

void print_string(str s);

int compare_str(str s1, str s2);
str concat_str(str s1, str s2);
//SUGERENCIA
/*
int compare_str(str s1, str s2) ;

str concat_str(str s1, str s2) ;
*/
//luego habria que implementarlas y agregar 
//compare_str_ast y concat_str_ast en AST.h
//remover linea 3: #include "AST.h"



#endif
