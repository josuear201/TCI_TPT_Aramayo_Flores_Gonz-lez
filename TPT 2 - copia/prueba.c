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
	
	return 0;
}
