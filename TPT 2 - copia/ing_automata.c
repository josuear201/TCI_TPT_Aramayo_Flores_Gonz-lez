#include "ing_automata.h"
//transiciones
transicion* ing_transicion(FILE* f){
	transicion* nvo = (transicion*)malloc(sizeof(transicion));
	cad simb,dest;
	Tdata d;
	
	fscanf(f, "%s %s", simb, dest);
	
	nvo->simb = create_str_ast();
	nvo->simb->string = strdup(simb);
	nvo->dest = create_set();
	d = create_str_ast();
	d->string = strdup(dest);
	insert_set(&nvo->dest, d);
	nvo->sig = NULL;
	
	return nvo;
}
	
transicion* carga_transiciones(FILE* f){
	int i,cant;
	transicion* ini; 
	transicion* act; 
	transicion* nvo; 
	
	ini = NULL;
	act = NULL;
	fscanf(f, "%d", &cant);
	
	for(i=1;i<=cant;i++){
		nvo = ing_transicion(f);
		if(ini == NULL){
			ini = nvo;
			act = nvo;
		}
		else{
			act->sig = nvo;
			act = nvo;
		}
	}
	
	return ini;
}
	
//estados
std* ing_std(FILE* f){
	std* nvo;
	cad nombre;
	int esfin,t;
	
	nvo = (std*)malloc(sizeof(std));
	fscanf(f, "%s %d %d", nombre,&esfin,&t);
	
	nvo->nom = create_str_ast();
	nvo->nom->string = strdup(nombre);
	nvo->esfin = esfin;
	
	if(t == 1)
		nvo->delta = carga_transiciones(f);
	else
		nvo->delta = NULL;
	nvo->sig = NULL;
	
	return nvo;
}
	
std* carga_lista(FILE* f){
	std* ini;
	std* act;
	std* nvo;
	int cant,i;
	
	ini=NULL;
	act=NULL;
	fscanf(f, "%d", &cant);
	
	for(i=1;i<=cant;i++){
		nvo = ing_std(f);
		if(ini == NULL){
			ini = nvo;
			act = nvo;
		}else{
			act->sig = nvo;
			act = nvo;
		}
	}
	return ini;
}
	
//Automata 
automata* ing_automata(FILE* f){
	automata* A;
	int cantAlf,i;
	cad s,q0;
	
	A = (automata*)malloc(sizeof(automata));
	fscanf(f, "%d", &A->det);
	
	A->Q = carga_lista(f);
	A->Alf = create_set();
	fscanf(f, "%d", &cantAlf);
	for(i=1;i<=cantAlf;i++){
		fscanf(f, "%s", s);
		Tdata a = create_str_ast();
		a->string = strdup(s);
		insert_set(&A->Alf, a);
	}

	fscanf(f, "%s", q0);
	A->q0 = create_str_ast();
	A->q0->string = strdup(q0);

	return A;
}
	
//estado final
Tdata estados_finales(std* Q){
	Tdata F;
	F = create_set();
	while(Q!=NULL){
		if(Q->esfin == 1)
			insert_set(&F, Q->nom);
		Q = Q->sig;
	}
	return F;
}
	
//mostrar set
void mostrar_set(Tdata set){
	printf("{");
	int p;
	p = 1;
	while(set!= NULL){
		if(set->data!= NULL){
			if(!p)
				printf(",");
			print_string(set->data->string);
			p = 0;
		}
		set = set->next;
	}
	
	printf("}");
}
	
//mostrar conjuto Q
void mostrar_Q(std* Q){
	printf("{");
	while(Q != NULL){
		print_string(Q->nom->string);
		if(Q->sig != NULL)
			printf(",");
		Q = Q->sig;
	}
	printf("}");
}
//tabulaciones(estetico)
void tab(int Tab) {
	int i;
	for(i = 1; i < Tab; i++) {
		printf("         "); 
	}
}

//mostrar transiciones
void mostrar_transicion(transicion* t, int Tab){
	int p;
	if(t == NULL){
		tab(Tab);
		printf("      | \n");
		tab(Tab);
		printf("      +-----> ");
	}
	else{
		p = 1;
		while(t != NULL){
			if(p) {
				printf(" ---> ");
				mostrar_set(t->dest);
				printf("  (con '%s')", t->simb->string);
				p = 0;
			} else {
				printf("\n");
				tab(Tab);
				printf("      | ");
				printf("\n");
				tab(Tab);
				printf("      | %s", t->simb->string);
				printf("\n");
				tab(Tab);
				printf("      v ");
				printf("\n");
				tab(Tab);
				printf("      +-----> ");
				mostrar_set(t->dest);
			}
			t = t->sig;
		}
	}
}
	
//mostrar estados
void mostrar_estado(std* e, int Tab){
	if(e != NULL){
		printf("\n");
		tab(Tab);
		printf("      | ");
		printf("\n");
		tab(Tab);
		printf("      | ");
		
		printf("\n");
		tab(Tab);
		printf("    (%s)", e->nom->string);
		if(e->esfin)
			printf(" (Final)");
		
		mostrar_transicion(e->delta, Tab);
	}
}
	
//mostrar lista de estados
void mostrar_estados(std* Q){
	int Tab; 
	Tab = 1; 
	printf("	   A");
	printf("\n      +--------+");
	printf("\n      |        v");
	while(Q != NULL){
		mostrar_estado(Q, Tab);
		Tab++; 
		Q = Q->sig;
	}
	printf("\n\n");
}
//trancicionesde delta
void mostrar_delta(std* Q){
	transicion* t;
	while(Q != NULL){
		t = Q->delta;
		while(t != NULL){
			printf("\nd(");
			print_string(Q->nom->string);
			printf(",");
			print_string(t->simb->string);
			printf(") = ");
			mostrar_set(t->dest);
			t = t->sig;
		}
		Q = Q->sig;
	}
}
	
//mostrar todo el Automata
void mostrar_automata(automata* A){
	if(A != NULL){
	Tdata F = estados_finales(A->Q);
	printf("\nA = (Q, S, d, q0, F)\n");
	printf("\nQ = ");
	mostrar_Q(A->Q);
	printf("\nS = ");
	mostrar_set(A->Alf);
	printf("\nq0 = ");
	print_string(A->q0->string);
	printf("\nF = ");
	mostrar_set(F);
	printf("\n\nd:");
	mostrar_delta(A->Q);
	printf("\n\nDETALLE ESTADOS:\n");
	mostrar_estados(A->Q);
	printf("\n");}
}
