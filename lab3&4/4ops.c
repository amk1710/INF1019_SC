#include <stdio.h>
#include <signal.h>
#include <stdlib.h>


void div0(int signo)
{
	printf("Não faça isso, jovem\n");
	exit(1);
	return;
}

int main(void)
{
	int a,b;
	signal(SIGFPE, div0);
	
	printf("n1:\n");
	scanf("%d", &a);
	printf("n2:\n");
	scanf("%d", &b);
	printf("Soma: %d\n", a+b);
	printf("Sub: %d\n", a-b);
	printf("Mult: %d\n", a*b);
	printf("Div: %d\n", a/b);
	return 0;	

}
