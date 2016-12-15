#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define TAM 20

int main(void)
{
	int fpFIFO;
	char c;
	if(access("fifo1", F_OK) == -1)
	{
		if(mkfifo("fifo1", S_IRUSR | S_IWUSR) != 0)
		{
			printf("Erro ao criar fifo\n");
			return -1;
		}
	}
	//abrindo fifo
	if((fpFIFO = open("fifo1", O_WRONLY)) < 0)
	{
		printf("erro ao abrir fifo\n");
		return -2;
	}
	//escrevendo na fifo
	while(1)
	{
		scanf("%c", &c);
		write(fpFIFO, &c, 1);
		//fflush(NULL);
	}
}
