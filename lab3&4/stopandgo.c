#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define TEMPO 10

//não pronto

//ativa filho1. desativa filho2
void sigusr1Handler(int signal)
{
	
}

//ativa filho2. desativa filho1
void sigusr2Handler(int signal)
{
	
}


int main(int argc, char *argv[]) 
{ 
	//pid's dos dois filhos
	pid_t pid1, pid2;
	int i;
	signal(SIGALRM, alarmHandler);
	 
	if((pid1 = fork()) < 0) 
	{ 
		fprintf(stderr, "Erro ao criar filho\n");
		 
		exit(-1); 
	} 
	if(pid1 != 0) /*parent*/
	{
		
		if((pid2 = fork()) < 0) 
		{ 
			fprintf(stderr, "Erro ao criar filho\n");
		 
			exit(-1); 
		} 
	} 
	if(pid1 != 0 && pid2 != 0) /* parent */
	{
		
		while(1)
		{
			if(i >= 10)
			{
				kill(pid1, SIGKILL);
				kill(pid2, SIGKILL);//mata os filhos
			}
		}
	} 
	else
	{
		while(1)
		{
			sleep(0.5);
			printf("Filho: %d", getpid());
		}
	}
		
	return 0; 
}
