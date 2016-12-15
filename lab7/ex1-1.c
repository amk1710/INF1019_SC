#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>


int main(void)
{
	int fpFIFO;
	char ch;
	if(access("fifo1", F_OK) == -1)
	{
		if(mkfifo("fifo1", S_IRUSR | S_IWUSR) != 0)
		{
			printf("Erro ao criar fifo\n");
			return -1;
		}
	}
	//abrindo fifo
	if((fpFIFO = open("fifo1", O_RDONLY)) < 0)
	{
		printf("erro ao abrir fifo\n");
		return -2;
	}
	//lendo da fifo
	
	while(read(fpFIFO, &ch, sizeof(ch)) > 0)
	{
		putchar(ch);
		fflush(stdout);
	}
	
	
}
