#include <stdio.h>

#define SUCCESS 1
#define FAILURE 0

int to_summ(int f_oper, int s_oper, int *res){
	*res = s_oper + f_oper;
	return SUCCESS;
}

int to_dif(int f_oper, int s_oper, int *res){
	*res = s_oper - f_oper;
	return SUCCESS;
}

int to_mult(int f_oper, int s_oper, int *res){
	*res = s_oper * f_oper;
	return SUCCESS;
}

int to_div(int f_oper, int s_oper, int *res){
	if(f_oper == 0) 
		return FAILURE;
	*res = s_oper / f_oper;
	return SUCCESS;
}
