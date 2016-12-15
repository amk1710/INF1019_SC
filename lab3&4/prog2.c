#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main(void)
{
	while(1)
	{
		usleep(9000);
		printf("Huginho.\n");
	}
	return 0;
}
