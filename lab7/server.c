#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <ctype.h>



int main(void)
{
	int fpFIFOUp, fpFIFODown;
	char ch;
	//cria e abre fifo de subida ao server(leitura)
	if(access("fifoUp", F_OK) == -1)
	{
		if(mkfifo("fifoUp", S_IRUSR | S_IWUSR) != 0)
		{
			printf("Erro ao criar fifo UP\n");
			return -1;
		}
	}
	
	if((fpFIFOUp = open("fifoUp", O_RDONLY)) < 0)
	{
		printf("erro ao abrir fifo DOWN\n");
		return -2;
	}
	//fim: /cria e abre fifo de subida ao server(leitura)
	
	//cria e abre fifo de descida do server(escrita)
	if(access("fifoDown", F_OK) == -1)
	{
		printf("criando fifo down\n");
		if(mkfifo("fifoDown", S_IRUSR | S_IWUSR) != 0)
		{
			printf("Erro ao criar fifo\n");
			return -1;
		}
	}
	
	if((fpFIFODown = open("fifoDown", O_WRONLY)) < 0)
	{
		printf("erro ao abrir fifo\n");
		return -2;
	}
	
	//fim: cria e abre fifo de descida do server(escrita)
	
	while(read(fpFIFOUp, &ch, 1) > 0)
	{
		ch = toupper(ch);
		write(fpFIFODown, &ch, 1);
		fflush(NULL);
	}	

	return 0;
}
