#include "String.h"

str load2(const char* s){
	str r = (str)malloc(strlen(s)+1);
	strcpy(r, s);
	
	return r;
}
void print_string(str s){
	printf("%s", s);
}

	int compare_str(str s1, str s2) {
	return strcmp(s1, s2);
}
	
str concat_str(str s1, str s2) {
	int L1,L2;
	str C;
	
	L1 = strlen(s1);
	L2 = strlen(s2);
	
	C= (str)malloc(L1 + L2 + 1);
	
	if (C != NULL) {
		strcpy(C, s1);
		strcat(C, s2);
	}
	return C;
}
