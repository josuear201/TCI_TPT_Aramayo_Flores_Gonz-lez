#include "ing_automata.h"

int main(){
	
	FILE *f = fopen("C:/Users/usuario/Desktop/2026/TC1/TPT/TCI_TPT_Aramayo_Flores_Gonz-lez-main/TCI_TPT_Aramayo_Flores_Gonz-lez-main/TPT 2 - copia/Debug/automata.txt", "r");
	if(!f){
		print_string("No se pudo abrir archivo\n");
		return 1;
	}
	automata* A = ing_automata(f);
	mostrar_automata(A);
	fclose(f);
	// Prueba cadenas
	char cadena_prueba[100];
	printf("\nIngrese una cadena para validar: ");
	scanf("%s", cadena_prueba);
	
	// Valida dependiendo al automata
	if (A->det == 1) {
		printf("\nDetectado: Automata Determinista (DFA)\n");
		aceptar_cadena_dfa(A, cadena_prueba);
	} else {
		printf("\nDetectado: Automata No Determinista (NFA)\n");
		aceptar_cadena_nfa(A, cadena_prueba);
	}
	
	return 0;
}
