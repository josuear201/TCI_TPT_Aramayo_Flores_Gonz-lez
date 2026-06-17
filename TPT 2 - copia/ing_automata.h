#ifndef ING_AUTOMATA_H
#define ING_AUTOMATA_H

#include "AST.h"
#define max 50
typedef char cad[max];
typedef struct transicion{
	Tdata simb;
	Tdata dest;
	struct transicion* sig;
}transicion;

typedef struct estado{
	Tdata nom;
	transicion* delta;
	int esfin;
	struct estado* sig;
}std;

typedef struct{
	std* Q;
	Tdata Alf;
	Tdata q0;
	int det;
}automata;

//ingreso desde TXT
automata* ing_automata(FILE* f);
std* ing_std(FILE* f);
std* carga_lista(FILE* f);
transicion* ing_transicion(FILE* f);
transicion* carga_transiciones(FILE* f);
Tdata estados_finales(std* Q);
//mostrar
void mostrar_automata(automata* A);
void mostrar_estados(std* Q);
void mostrar_estado(std* e,int);
void mostrar_transicion(transicion* t,int);
void mostrar_delta(std* Q);
void mostrar_Q(std* Q);
void mostrar_set(Tdata set);

#endif
