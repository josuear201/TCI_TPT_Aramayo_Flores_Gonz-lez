#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>
#include "String.h" //Operaciones sobre STR

#define STR 1
#define SET 2
#define LIST 3

struct dataType{
	int nodeType;   /* STR, SET, LIST */
	union{
		str string;
		struct{
			struct dataType* data;
			struct dataType* next;
		};
	};
};

typedef struct dataType* Tdata;

Tdata create_str_ast();
Tdata create_list();
Tdata create_set();

Tdata ing_str_ast();
//SUGERENCIAS
/*
int compare_str_ast(Tdata s1, Tdata s2) ;

Tdata concat_str_ast(Tdata s1, Tdata s2) ;
*/
//cada funcion llama a compare_str_ast y concat_str_ast respectivamente
int compare_str_ast(Tdata s1, Tdata s2);

Tdata concat_str_ast(Tdata s1, Tdata s2);

//Operaciones sobre SET
void insert_set(Tdata* set, Tdata elem);// (sin duplicados)
int belongs(Tdata set, Tdata elem);
void remove_set(Tdata* set, Tdata elem);

//#Operaciones algebraicas
Tdata union_set(Tdata A, Tdata B);
Tdata intersection_set(Tdata A, Tdata B);
Tdata difference_set(Tdata A, Tdata B);
//No hay dato tipo bool en C
//Cambiar a int
int subset(Tdata A, Tdata B);
int equals_set(Tdata A, Tdata B);


//Operaciones sobre LIST
void append(Tdata*, Tdata);
int length(Tdata);
Tdata copy_list(Tdata); //(copia profunda)
Tdata concat(Tdata, Tdata);
void search(Tdata, Tdata);


#endif
