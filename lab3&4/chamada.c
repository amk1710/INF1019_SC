#include <stdio.h>
#include <time.h>
#include <signal.h>

time_t tempo;

void inicio(int signo)
{
	tempo = time(0);
	return;
}

void fim(int signo)
{
	tempo = time(0) - tempo;
	int segundos = tempo;
	float custo;
	if(segundos > 60)
	{
		custo = 120 + (segundos - 60);
	}
	else
	{
		custo = 2 * segundos;
	}
	custo = custo/100;
	printf("Sua ligação custou %.2f reais\n", custo);
	
}

int main(void)
{
	signal(SIGUSR1, inicio);
	signal(SIGUSR2, fim);
	while(1);
}
