#ifndef AUTOMATA_H
#define AUTOMATA_H

#include "AST.h"
#define max 50
typedef char cad[max];
typedef struct delta{
	Tdata simb;
	Tdata dest;
	struct delta* sig;
}DELTA;
typedef DELTA* Delta;

typedef struct estado{
	Tdata nom;
	Delta delta;
	int esfin;
	struct estado* sig;
}ESTADO;
typedef ESTADO* Std;

typedef struct{
	Std Q;
	Tdata Alf;
	Tdata q0;
	int esdet;
}Automata;

//Creador de estructuras
//deltas
Delta nuevo_delta(Tdata simb, Tdata dest);
void agregar_delta(Delta* lista, Delta nuevo);
//std
Std nuevo_estado(Tdata nom, Delta delta, int esfin);
void agregar_estado(Std* lista, Std nuevo);
//automata
Automata nuevo_automata(Std Q, Tdata Alf, Tdata q0, int esdet);

//funciones de transiciones
Tdata fdelta(Automata automata, Tdata nom, Tdata simb);//el Tdata de regreso es un dest
Tdata fDELTA(Automata automata, Tdata cadena);//empieza desde q0
Tdata Udelta(Automata automata, Tdata estados, Tdata simb);//devuelve una union

//aceptacion
int es_aceptado(Automata automata, Tdata estados);
int acepta_cad(Automata automata, Tdata cadena);


//convertir AFD a AFND
Automata conversion(Automata automata);

//ingreso desde TXT
Automata ing_automata(char* nombre);
Std ing_std(FILE* f);
Delta ing_delta(FILE* f);
/*
std* carga_lista(FILE* f);
transicion* carga_transiciones(FILE* f);
Tdata estados_finales(std* Q);
*/
//mostrar
void mostrar_automata(Automata A);
void mostrar_Q(Std Q);
void mostrar_F(Std Q);
void mostrar_delta(Std Q);
void mostrar_aceptacion(Automata automata, Tdata cadena);
/*void mostrar_set(Tdata set);
void mostrar_transicion(transicion* t,int);
void mostrar_estado(std* e,int);
void mostrar_estados(std* Q);*/

//menu
void menu(Automata* A);

#endif
