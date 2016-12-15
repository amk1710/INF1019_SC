#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>



int main(void)
{
	int fpFIFOUp, fpFIFODown;
	char ch;
	//abre fifo de subida ao server(escrita)
	if(access("fifoUp", F_OK) == 0)
	{
		if((fpFIFOUp = open("fifoUp", O_WRONLY)) < 0)
		{
			printf("erro ao abrir fifo\n");
			return -2;
		}
	}
	//fim: /cria e abre fifo de subida ao server(escrita)
	
	//abre fifo de descida do server(leitura)
	
	
	if(access("fifoUp", F_OK) == 0)
	{
		if((fpFIFODown = open("fifoDown", O_RDONLY)) < 0)
		{
			printf("erro ao abrir fifo\n");
			return -2;
		}
	}
	
	//fim: cria e abre fifo de descida do server(leitura)
	
	while(1)
	{
		scanf("%c", &ch);
		write(fpFIFOUp, &ch, 1);
		fflush(NULL);
		read(fpFIFODown, &ch, 1);
		putchar(ch);
		fflush(stdout);
		
	}
	
	
	
	
	

	return 0;
}
