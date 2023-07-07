#include"header.h"
#include"func.h"


int hash_func(int key)
{
	return (key% CAPACITY);
}

int hash_func_cust(int key)
{
	return (key% PEOPLE);
}


void f_greeting()
{
	printf("\n Your response has been recorded\n\n Thankyou for visiting. Come again. \n----------------------------------------------------------\n\n");
}




