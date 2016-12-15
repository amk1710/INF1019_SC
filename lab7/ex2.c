#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>



int main(void)
{
	int fpFIFO, pid, status;
	char ch;
	char msg1[] = "OI PAI!\n";
	char msg2[] = "oi papai";
	
	if(access("fifo2", F_OK) == -1)
	{
		if(mkfifo("fifo2", S_IRUSR | S_IWUSR) != 0)
		{
			printf("Erro ao criar fifo\n");
			return -1;
		}
	}
	
	if((fpFIFO = open("fifo2", O_RDWR)) < 0)
	{
		printf("erro ao abrir fifo\n");
		return -2;
	}

	if((pid = fork()) < 0)
	{
		printf("Erro no fork\n");
		exit(1);
	}
	if(pid == 0)
	//filho 1
	{
		
		write(fpFIFO, msg1, strlen(msg1));
		close(fpFIFO);
		return 0;
		
	}
	else
	{
		
		waitpid(0, &status, 0);
		if((pid = fork()) < 0)
		{
			printf("Erro no fork\n");
			exit(1);
		}
		if(pid == 0)
		//filho 2
		{
			write(fpFIFO, msg2, strlen(msg2));
			close(fpFIFO);
			return 0;
		
		}
		else
		//pai
		{
			waitpid(0, &status, 0);
			while(read(fpFIFO, &ch, sizeof(ch)) > 0)
			{
				putchar(ch);
				fflush(stdout);
			}
			close(fpFIFO);
		}
		
	}
	return 0;
}
