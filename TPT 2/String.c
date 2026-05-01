#include "String.h"

str load2(const char* s){
	str r = (str)malloc(strlen(s)+1);
	strcpy(r, s);
	
	return r;
}
void print_string(str s){
	printf("%s", s);
}

