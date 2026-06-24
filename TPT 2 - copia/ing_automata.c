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
	d->string = load2(dest);
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
	nvo->nom->string = load2(nombre);
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
		a->string = load2(s);
		insert_set(&A->Alf, a);
	}

	fscanf(f, "%s", q0);
	A->q0 = create_str_ast();
	A->q0->string = load2(q0);

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
	print_string("{");
	int p;
	p = 1;
	while(set!= NULL){
		if(set->data!= NULL){
			if(!p)
				print_string(",");
			print_string(set->data->string);
			p = 0;
		}
		set = set->next;
	}
	
	print_string("}");
}
	
//mostrar conjuto Q
void mostrar_Q(std* Q){
	print_string("{");
	while(Q != NULL){
		print_string(Q->nom->string);
		if(Q->sig != NULL)
			print_string(",");
		Q = Q->sig;
	}
	printf("}");
}
//tabulaciones(estetico)
void tab(int Tab) {
	int i;
	for(i = 1; i < Tab; i++) {
		print_string("         "); 
	}
}

//mostrar transiciones
void mostrar_transicion(transicion* t, int Tab){
	int p;
	if(t == NULL){
		tab(Tab);
		print_string("      | \n");
		tab(Tab);
		print_string("      +-----> ");
	}
	else{
		p = 1;
		while(t != NULL){
			if(p) {
				print_string(" ---> ");
				mostrar_set(t->dest);
				
				print_string(" con = ");
				print_string(t->simb->string);
				p = 0;
			} else {
				print_string("\n");
				tab(Tab);
				print_string("      | ");
				print_string("\n");
				tab(Tab);
				print_string("      ");
				print_string(t->simb->string);
				print_string("\n");
				tab(Tab);
				print_string("      v ");
				print_string("\n");
				tab(Tab);
				print_string("      +-----> ");
				mostrar_set(t->dest);
			}
			t = t->sig;
		}
	}
}
	
//mostrar estados
void mostrar_estado(std* e, int Tab){
	if(e != NULL){
		print_string("\n");
		tab(Tab);
		print_string("      | ");
		print_string("\n");
		tab(Tab);
		print_string("      | ");
		
		print_string("\n");
		tab(Tab);
		print_string("      ");
		print_string(e->nom->string);
		if(e->esfin)
			print_string(" (Final)");
		
		mostrar_transicion(e->delta, Tab);
	}
}
	
//mostrar lista de estados
void mostrar_estados(std* Q){
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
}
//trancicionesde delta
void mostrar_delta(std* Q){
	transicion* t;
	while(Q != NULL){
		t = Q->delta;
		while(t != NULL){
			print_string("\nd(");
			print_string(Q->nom->string);
			printf(",");
			print_string(t->simb->string);
			print_string(") = ");
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
	print_string("\nA = (Q, S, d, q0, F)\n");
	print_string("\nQ = ");
	mostrar_Q(A->Q);
	print_string("\nS = ");
	mostrar_set(A->Alf);
	print_string("\nq0 = ");
	print_string(A->q0->string);
	print_string("\nF = ");
	mostrar_set(F);
	print_string("\n\nd:");
	mostrar_delta(A->Q);
	print_string("\n\nDETALLE ESTADOS:\n");
	mostrar_estados(A->Q);
	print_string("\n");}
}
// Buscar estado
std* buscar_estado(std* Q, str nombre_estado) {
	while (Q != NULL) {
		if (compare_str(Q->nom->string, nombre_estado) == 0) {
			return Q;
		}
		Q = Q->sig;
	}
	return NULL; // Estado no encontrado
}
// Aceptar cadena determinista
int aceptar_cadena_dfa(automata* A, const char* cadena) {
	if (A == NULL) return 0;
	
	std* estado_actual = buscar_estado(A->Q, A->q0->string);
	int i = 0;
	
	while (cadena[i] != '\0') {
		char simb_act[2] = {cadena[i], '\0'};
		transicion* t = estado_actual->delta;
		int transicion_encontrada = 0;
		
		while (t != NULL) {
			if (compare_str(t->simb->string, simb_act) == 0) {
				if (t->dest != NULL && t->dest->data != NULL) {
					estado_actual = buscar_estado(A->Q, t->dest->data->string);
					transicion_encontrada = 1;
					break;
				}
			}
			t = t->sig;
		}
		
		if (!transicion_encontrada) {
			printf("[DFA] Rechazada: No hay transicion desde '%s' con '%c'.\n", estado_actual->nom->string, cadena[i]);
			return 0;
		}
		i++;
	}
	
	if (estado_actual != NULL && estado_actual->esfin == 1) {
		printf("[DFA] Cadena ACEPTADA Termino en: %s\n", estado_actual->nom->string);
		return 1;
	} else {
		printf("[DFA] Cadena RECHAZADA: Termino en estado no final: %s\n", estado_actual ? estado_actual->nom->string : "Nulo");
		return 0;
	}
}

void union_nfa(Tdata* dest, Tdata src) {
	Tdata aux = src;
	while (aux != NULL) {
		if (aux->data != NULL && aux->data->nodeType == STR) {
			// Creamos un nodo STR nuevo para no compartir memoria que pueda corromperse
			Tdata nuevo_str = create_str_ast();
			nuevo_str->string = load2(aux->data->string);
			
			// insert_set se encarga de verificar que no se duplique con 'belongs'
			insert_set(dest, nuevo_str);
		}
		aux = aux->next;
	}
}
// Aceptar cadena no determinista
int aceptar_cadena_nfa(automata* A, const char* cadena) {
	if (A == NULL) return 0;
	
	// Conjunto de estados en los que se encuentra el autómata actualmente
	Tdata estados_actuales = create_set();
	
	Tdata q0_ast = create_str_ast();
	q0_ast->string = load2(A->q0->string);
	insert_set(&estados_actuales, q0_ast);
	
	int i = 0;
	while (cadena[i] != '\0') {
		char simb_act[2] = {cadena[i], '\0'};
		
		// Nuevo conjunto vacío para recolectar los destinos de este paso
		Tdata proximos_estados = create_set(); 
		
		Tdata curr = estados_actuales;
		int transiciones_totales_caracter = 0;
		
		// Procesamos todos los estados actuales en paralelo
		while (curr != NULL) {
			if (curr->data != NULL) {
				std* est_nodo = buscar_estado(A->Q, curr->data->string);
				if (est_nodo != NULL) {
					transicion* t = est_nodo->delta;
					while (t != NULL) {
						if (compare_str(t->simb->string, simb_act) == 0) {
							// Usamos la unión segura específica para NFA
							union_nfa(&proximos_estados, t->dest);
							transiciones_totales_caracter++;
						}
						t = t->sig;
					}
				}
			}
			curr = curr->next;
		}
		
		// Si no se recolectaron estados o el conjunto quedó vacío de datos reales
		if (proximos_estados == NULL || proximos_estados->data == NULL || transiciones_totales_caracter == 0) {
			printf("[NFA] Rechazada: El automata se estanco en el caracter '%c'.\n", cadena[i]);
			return 0;
		}
		
		// Liberamos el conjunto anterior (opcional, para cuidar memoria) y avanzamos
		estados_actuales = proximos_estados;
		i++;
	}
	
	// Verificación final de aceptación
	Tdata curr = estados_actuales;
	int aceptada = 0;
	
	printf("[NFA] Estados alcanzados al final: ");
	mostrar_set(estados_actuales);
	printf("\n");
	
	while (curr != NULL) {
		if (curr->data != NULL) {
			std* est_nodo = buscar_estado(A->Q, curr->data->string);
			if (est_nodo != NULL && est_nodo->esfin == 1) {
				aceptada = 1;
				break; 
			}
		}
		curr = curr->next;
	}
	
	if (aceptada) {
		printf("[NFA] Cadena ACEPTADA Al menos un estado alcanzado es final.\n");
		return 1;
	} else {
		printf("[NFA] Cadena RECHAZADA: Ninguno de los estados alcanzados es final.\n");
		return 0;
	}
}
