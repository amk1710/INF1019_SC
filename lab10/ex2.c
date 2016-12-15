#include <sys/types.h> 
#include <sys/dir.h> 
#include <sys/param.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>


#define TRUE 1
#define FALSE 0

extern  int alphasort(); 
char pathname[MAXPATHLEN];

int file_select(const struct direct   *entry) 
{ 
    if ((strcmp(entry->d_name, ".") == 0) || (strcmp(entry->d_name, "..") == 0))  
          return (FALSE); 
    else 
          return (TRUE); 
}

//apos executar no terminal o comando ln <arquivo> <nomeLink>, esse arquivo possuirá mais um link, como pode ser visto com a impressão feita por essa main.
  
int main(void)
{  
	int count,i; 
	struct direct **files;
	struct stat info;
	size_t size = MAXPATHLEN; 
	if (getcwd(pathname, size) == NULL )
	{  
		printf("Error getting path\n");
		exit(0);
	}
	printf("Current Working Directory = %s\n",pathname);
	count = scandir( pathname, &files, file_select, alphasort);
	/* If no files found, make a non-selectable menu item */
	if (count <= 0)
	{
		printf("No files in this directory\n");
		exit(0);
	}
	
	printf("Number of files = %d\n",count);
	for (i=1;i<count+1;++i)
	{
		printf("%s\t", files[i-1]->d_name);
		printf("inode: %ld\t", files[i-1]->d_ino);
		
		//pega infos do arquivo
		if(stat(files[i-1]->d_name, &info) == 1)
		{
			printf("erro ao pegar arquivo\n");
		}
		
		printf("número de links: %ld\n", info.st_nlink);
		
	}
	printf("\n"); /* flush buffer */ 
	return 0;
} 
