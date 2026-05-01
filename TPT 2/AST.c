#include "AST.h"
#include <stdio.h>


Tdata create_str_ast(){
	Tdata n = (Tdata)malloc(sizeof(struct dataType));
	n->nodeType = STR;
	n->string = NULL;
	return n;
}
Tdata create_set(){
	Tdata n = (Tdata)malloc(sizeof(struct dataType));
	n->nodeType = SET;
	n->data = NULL;
	n->next = NULL;
	return n;
}
Tdata create_list(){
	Tdata n = (Tdata)malloc(sizeof(struct dataType));
	n->nodeType = LIST;
	n->data = NULL;
	n->next = NULL;
	return n;
}
			 
void insert_set(Tdata* set, Tdata elem){ 
	Tdata nvo;
	if(belongs(*set,elem)==1){
		printf("\n el elemento ya se encuentra");}
	else{
		nvo = (Tdata) malloc(sizeof(struct dataType));
		nvo->nodeType = SET;
		nvo->data=elem;
		nvo->next = *set;
		*set=nvo;}
}
int belongs(Tdata set, Tdata elem){
	
	int b = 0; 
	
	
	if (set != NULL && elem != NULL) { 
		while(set != NULL){
			
			if(set->data != NULL && compare_str_ast(set->data, elem) == 0)
				b = 1;
			set = set->next;
		}
	}
	return b;
}
void remove_set(Tdata* set, Tdata elem){
	Tdata act,temp;
	act=*set;
	
	if(*set!=NULL){
		if(compare_str_ast((*set)->data,elem)==1){
			temp= *set;
			*set=(*set)->next;
			free(temp);
		}
		else{
				while(act->next!=NULL){
					if(compare_str_ast(act->next->data,elem)==1){
						temp=act->next;
						act->next=temp->next;
						free(temp);
					}
					else
							act=act->next;
				}}}
}
	
Tdata union_set(Tdata A, Tdata B){
	Tdata nvo;
	Tdata aux;
	
	nvo = NULL;
	aux = A;
	while(aux!= NULL){
		insert_set(&nvo,aux->data);
		aux=aux->next;
	}
	aux=B;
	while(aux!=NULL){
		insert_set(&nvo,aux->data);
		aux=aux->next;
	}
	return nvo;
}
Tdata intersection_set(Tdata A, Tdata B){
	Tdata nvo,aux;
	
	nvo = NULL;
	aux = A;
	
	while(aux!=NULL){
		if(belongs(B,aux->data)==1){
			insert_set(&nvo,aux->data);
		}
		aux=aux->next;}
	
	return nvo;
}
Tdata difference_set(Tdata A, Tdata B){
	Tdata nvo,aux;
	
	nvo = NULL;
	aux = A;
	
	while(aux!=NULL){
		if(belongs(B,aux->data)==0){
			insert_set(&nvo,aux->data);
		}
		aux=aux->next;
	}
	return nvo;
}
int subset(Tdata A, Tdata B){
	int b;
	Tdata aux;
	aux=A;
	b=0;
	while(aux!=NULL){
		if(belongs(B,aux->data)==0)
			b=1;
		aux=aux->next;
	}
	return b;
}
int equals_set(Tdata A, Tdata B){
	int b;
	Tdata aux;
	aux=A;
	b=0;
	while(aux!=NULL){
		if(belongs(B,aux->data)==0)
			b=1;
		aux=aux->next;
	}
	aux=B;
	while(aux!=NULL){
		if(belongs(A,aux->data)==0)
			b=1;
		aux=aux->next;
	}
	return b;
}
	

//Operaciones sobre LIST
//interfaces privadas
int is_list(Tdata);
Tdata copy_ast(Tdata);
int equal_ast(Tdata, Tdata);
int equals_list(Tdata, Tdata);

//implementaciones
int is_list(Tdata list){
	int salida;
	salida = 0;
	if (list!=NULL)
		if (list->nodeType == LIST)
			salida = 1;
	return salida;
}
	
void append(Tdata* list, Tdata elem){
	Tdata auxList;
	if (is_list(*list)!=0){
		auxList = *list;
		while (auxList != NULL){
			auxList = auxList->next;
		}
		if (auxList->data == NULL)
			auxList->data = elem;
		else {
			auxList->next = create_list();
			auxList = auxList->next;
			auxList->data = elem;
		}
	}
	else
		printf("\nEl elemento ingresado no es una lista");
}
int length(Tdata list){
	int salida;
	salida = 0;
	if (is_list(list)!=0){
		while (list != NULL){
			salida++;
			list = list->next;
		}
		if (list->data == NULL)
			salida--;
	}
	else{
		printf("\nEl elemento ingresado no es una lista");
		salida = -1;
	}
	return salida;
}
Tdata copy_ast(Tdata ast){ //(copia profunda)
	Tdata nuevo, aux;
	nuevo = NULL;
	if (ast != NULL){
		if (ast->nodeType == STR){
			nuevo = create_str_ast();
			nuevo->string = load2(ast->string);
		}
		else{
			if (ast->nodeType == SET){
				nuevo = create_set();
				aux = nuevo;
			}
			else {
				nuevo = create_list();
				aux = nuevo;
			}
			while (ast != NULL){
				aux->data = copy_ast(ast->data);
				ast = ast->next;
				aux = aux->next;
				aux = create_set();
			}
		}
	}
	return nuevo;
}
Tdata copy_list(Tdata list){ //(copia profunda)
	Tdata nuevo;
	nuevo = NULL;
	if (is_list(list)!=0)
		nuevo = copy_ast(list);
	else
		printf("\nEl elemento ingresado no es una lista");
	return nuevo;
}
Tdata concat(Tdata l1, Tdata l2){
	Tdata nuevo,aux;
	nuevo = NULL;
	if (is_list(l1)!=0 && is_list(l2)!=0){
		nuevo = copy_list(l1);
		aux = nuevo;
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = copy_list(l2);
	}
	else
		printf("\nAl menos un elemento ingresado no es una lista");
	return nuevo;
}
int equal_ast(Tdata l1, Tdata l2){
	int salida;
	salida = 0;
	if (l1 != NULL && l2 != NULL){
		if (l1->nodeType == l2->nodeType){
			switch (l1->nodeType){
			case STR:
				if (compare_str_ast(l1, l2)==0)
					salida = 1;
				break;
			case SET:
				salida = equals_set(l1, l2);
				break;
			case LIST:
				salida = equals_list(l1, l2);
				break;
			}
		}
	}
	else if(l1 == l2)
		salida = 1;
	return salida;
}
int equals_list(Tdata l2, Tdata l1){
	int salida;
	if (length(l1)==length(l2)){
		salida = 1;
		while (is_list(l1)!=0 && is_list(l2)!=0 && salida == 1){
			if (equal_ast(l1->data, l2->data) == 0)
				salida = 0;
			l1 = l1->next;
			l2 = l2->next;
		}
	}
	else 
						   salida = 0;
	return salida;
}
void search(Tdata list, Tdata elem){
	int salida;
	salida = 0;
	if (is_list(list)!=0){
		while (list != NULL){
			if (equal_ast(list->data, elem) != 0){
				salida = 1;
			}
			list = list->next;
		}
	}
	else
		printf("\nEl elemento ingresado no es una lista");
	if (salida == 1)
		printf("\nEl elemento esta en la lista");
}
str concat_str_ast(Tdata s1, Tdata s2) {
	Tdata R;
	str C;
	
	if (s1->nodeType != STR || s2->nodeType != STR) {
		printf("Error: Los parámetros para concatenar deben ser STR.\n");
		return NULL;
	}
	C=concat_str(s1->string, s2->string);
	
	R->string=C;
	
	return R;
}
int compare_str_ast(Tdata s1, Tdata s2) {
	int r;
	
	if (s1->nodeType != STR || s2->nodeType != STR) {
		printf("Error: Intento de comparar tipos que no son STR.\n");
		r = -1; 
	}
	r = compare_str(s1->string, s2->string);
	
	return r;
}

int compare_str_ast(Tdata s1, Tdata s2) {
	int r;
	
	if (s1->nodeType != STR || s2->nodeType != STR) {
		printf("Error: Intento de comparar tipos que no son STR.\n");
		r = -1; 
	}
	r = strcmp(s1->string, s2->string);
	
	return r;
}
