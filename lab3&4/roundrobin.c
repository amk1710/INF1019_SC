#include <stdio.h>
#include <signal.h>
#include <unistd.h>


int main(void)
{
	int pid1, pid2, pid3, pidP;
		
	pidP = getpid();
	pid1 = fork();
	if(pid1 == 0)
	{
		//zezinho
		execve("./prog1", NULL, NULL);
	}
	kill(pid1, SIGSTOP);
	pid2 = fork();
	if(pid2 == 0)
	{
		//huginho
		execve("./prog2", NULL, NULL);
	}
	kill(pid2, SIGSTOP);
	pid3 = fork();
	if(pid3 == 0)
	{
		//luisinho
		execve("./prog3", NULL, NULL);
	}
	kill(pid3, SIGSTOP);
	
	if(getpid() == pidP)
	{
		while(1)
		{
		
			kill(pid3, SIGCONT);
			sleep(1);
		
			kill(pid3, SIGSTOP);
			kill(pid2, SIGCONT);
			sleep(2);
		
			kill(pid2, SIGSTOP);
			kill(pid1, SIGCONT);
			sleep(2);
		
			kill(pid1, SIGSTOP);
		}
	}	
}
