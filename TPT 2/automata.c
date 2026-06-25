#include "automata.h"

#include <stdio.h>
//Creador de estructuras
//deltas
Delta nuevo_delta(Tdata simb, Tdata dest){
    Delta nuevo;
    nuevo = (Delta)malloc(sizeof(DELTA));
    nuevo->simb = simb;
    nuevo->dest = dest;
    nuevo->sig = NULL;
    return nuevo;
}
void agregar_delta(Delta* lista, Delta nuevo){
    while(*lista != NULL){
        lista = &(*lista)->sig;
    }
    *lista = nuevo;
}
//std
Std nuevo_estado(Tdata nom, Delta delta, int esfin){
    Std nuevo;
    nuevo = (Std)malloc(sizeof(ESTADO));
    nuevo->nom = nom;
    nuevo->delta = delta;
    nuevo->esfin = esfin;
    nuevo->sig = NULL;
	return nuevo;
}
void agregar_estado(Std* lista, Std nuevo){
    while(*lista != NULL){
        lista = &(*lista)->sig;
    }
    *lista = nuevo;
}
//automata
Automata nuevo_automata(Std Q, Tdata Alf, Tdata q0, int esdet){
    Automata nuevo;
    nuevo.Q = Q;
    nuevo.Alf = Alf;
    nuevo.q0 = q0;
    nuevo.esdet=esdet;
    return nuevo;
}

//funciones de transiciones
Std buscar_estado(Std Q, Tdata nom){
    while (Q != NULL) {
		if (igual_ast(Q->nom, nom) == 1) {
			return Q;
		}
		Q = Q->sig;
	}
	return NULL;
}
Delta buscar_delta(Std estado, Tdata simb){
    Delta delta;
    delta = estado->delta;
    while (delta != NULL) {
		if (igual_ast(delta->simb, simb) == 1) {
			return delta;
		}
		delta = delta->sig;
	}
	return NULL;
}
Tdata fdelta(Automata automata, Tdata nom, Tdata simb){
    Std estado = buscar_estado(automata.Q, nom);
    Delta transicion = buscar_delta(estado, simb);
    return transicion->dest;
}
Tdata fDELTA(Automata automata, Tdata cadena){
    Tdata nom = automata.q0;
    while(cadena != NULL){
        nom = fdelta(automata, nom, recorre_lista(&cadena));
    }
    return nom;
}
Tdata Udelta(Automata automata, Tdata estados, Tdata simb){
    Tdata union_deltas = NULL;
    Tdata aux;
    if (automata.esdet == 0){
        while (estados !=NULL){
            aux = fdelta(automata, recorre_lista(&estados), simb)
            union_set2(&union_deltas, aux);
        }
    }
    return union_deltas;
}

//aceptacion
int es_aceptado(Automata automata, Tdata estados){
    Std std;
    if (automata.esdet != 0){//Si es AFD (solo hay un estado)
        std = buscar_estado(automata.Q, estados);
        return std->esfin;
    }
    else{
        while (estados != NULL){//Si es AFND (recorre el conjunto de estados hasta encontrar un estado de aceptecion)
            std = buscar_estado(automata.Q, recorre_lista(&estados));
            if (std->esfin != 0) return 1;
        }
    }
    return 0;
}
int acepta_cad(Automata automata, Tdata cadena){
    return es_aceptado(automata, fDELTA(automata, cadena));
}

//convertir AFD a AFND
Automata conversion(Automata automata){
    if (automata.esdet == 1) return NULL;
    Tdata nom = NULL;
    insert_set(&nom,buscar_estado(automata.Q, automata.q0));
    Tdata Alf;
    Tdata simb;
    Std nvo_Q = nuevo_estado(nom, NULL, es_aceptado(automata, nom));
    Std estado = nvo_Q;
    agregar_estado(&nvo_Q, nom);
    while (estado != NULL){
    Alf = automata.Alf;
        while (Alf != NULL){
            simb = recorre_lista(&Alf);
            nom = Udelta(automata, estado->nom, simb);
            agegar_delta(estado->delta, nuevo_delta(simb, nom));
            if (NULL == buscar_estados(nvo_Q, nom)){
                agregar_estado(&estado, nuevo_estado(nom, NULL, es_aceptado(automata, nom)));
            }
        }
    }
    return nuevo_automata(nvo_Q, automata.Alf, nvo_Q->nom, 1);
}

//ingreso desde TXT
Delta ing_delta(FILE* f){
    Delta delta;
        Tdata simb;
        Tdata dest;

    char c = fgetc(f);
        simb = ing_ast(f);
        dest = ing_ast(f);
    delta = nuevo_delta(simb, dest);

    c = fgetc(f);
    if (c == '1') agregar_delta(&delta, ing_delta(f));
    return delta;
}
Std ing_std(FILE* f){
    Std estado;
        Tdata nom;
        Delta delta;
        int esfin;

    char c = fgetc(f);
        if (c == '1') esfin = 1;
        else esfin = 0;
        nom = ing_ast(f);
        delta = ing_delta(f);
    estado = nuevo_estado(nom, delta, esfin);

    c = fgetc(f);
    if (c == '1') agregar_estado(&estado, ing_std(f));
    return estado;
}
Automata ing_automata(char* nombre){
    int esdet;
    Tdata q0;
    Tdata Alf;
    Std Q;
    char c;
    FILE*f = fopen(nombre,"r");//Abre archivo con el nombre. "r" es para decir que se va a leer (read) el archivo
    if (f == NULL) {
        printf("\nNo se pudo abrir el archivo");
        return NULL;
    }
    else{
        c = fgetc(f);
        if (c == '1') esdet = 1;
        else esdet = 0;
        q0 = ing_ast(f);
        Alf = ing_ast(f);
        Q = ing_std(f);
    }
    fclose(f);//cierra el archivo
    return nuevo_automata(Q, Alf, q0, esdet);
}

//mostrar
void mostrar_Q(Std Q){
    printf("{");
    while(Q != NULL){
        mostrar_ast(estado->nom);
        Q =Q->sig;
    }
    printf("}");
}
void mostrar_F(Std Q){
    printf("{");
    while(Q != NULL){
        if (Q->esfin == 1) mostrar_estado(Q);
        Q =Q->sig;
    }
    printf("}");
}
void mostrar_delta(Std Q){
    Delta t;
	while(Q != NULL){
		t = Q->delta;
		while(t != NULL){
			printf("\n\td(");
			mostrar_estado(Q);
			printf(", ");
			mostrar_ast(t->simb);
			print_string(") = ");
			mostrar_ast(t->dest);
			t = t->sig;
		}
		Q = Q->sig;
	}
}
/*void mostrar_estados(Std Q){
	int Tab; 
	Tab = 1; 
	print_string("	   A");
	print_string("\n      +--------+");
	print_string("\n      |        v");
	while(Q != NULL){
		mostrar_estado(Q, Tab);
		Tab++; 
		Q = Q->sig;
	}
	print_string("\n");
}*/
void mostrar_automata(Automata A){
	if(A.esdet != 0) printf("\nAFD: ");
    else printf("\nAFND: ");
	printf("A = (Q, S, d, q0, F)\n");
	printf("\nQ = ");
	mostrar_Q(A.Q);
	printf("\nS = ");
    mostrar_ast(A.Alf);
	printf("\nq0 = ");
	mostrar_ast(A.q0);
	printf("\nF = ");
	mostrar_F(A.Q);
	printf("\n\nd:");
	mostrar_delta(A.Q);
	/*printf("\n\nDETALLE ESTADOS:\n");
	mostrar_estados(A.Q);
	printf("\n");*/
}
void mostrar_aceptacion(Automata automata, Tdata cadena){
    Tdata estado = fDELTA(automata, cadena);
    printf("\n\tD(");
    mostrar_ast(automata.q0);
    printf(", ");
    mostrar_ast(cadena);
    print_string(") = ");
    mostrar_ast(estado);
    if (es_aceptado(automata, estados) != 0) printf("\nLa cadena es aceptada");
    else printf("\nLa cadena no es aceptada");
}

//menu
void menu(Automata* A){
    int m;
    Automata B;
    Tdata cad;
    do{
        printf("\nMenu de automata");
        printf("\n1. Mostrar automata");
        printf("\n2. Procesar cadena");
        if (A->esdet == 0)printf("\n3. Convertir a AFND");
        printf("\n0. Terminar");
        printf("\nSeleccione opcion");
        scanf("%i",&m);
        switch (m){
            case 0: break;
            case 1: mostrar_automata(*A); break;
            case 2: printf("\nIngresar cadena: ");
                mostrar_aceptacion(*A,ingresar_cadena());
                break;
            case 3: B = conversion(*A);
                if (B == NULL) printf("\nLa conversion fallo");
                else{
                    printf("\nCambio de automata.");
                    menu(&B);
                }
                break;
            default: Printf("\nValor no reconocido");
        }
    }while (c != 0);
    printf("\nSe termino el programa");
}
