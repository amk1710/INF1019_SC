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


int file_select(const struct direct   *entry) 
{ 
    if ((strcmp(entry->d_name, ".") == 0) || (strcmp(entry->d_name, "..") == 0))  
          return (FALSE); 
    else 
          return (TRUE); 
}

//função escreve em nArq e tam o número de arquivos e o tamanho total deles da propria pasta e todas as subpastas. Retorna a maior profundidade obtida. Level é o nível de recursão
int percorre(char *path, long *nArq, long *tam, int level)
{
	
	int count,i; 
	struct direct **files;
	struct stat info;
	char temp[MAXPATHLEN];
	
	long n = 0, t = 0;
	
	int lmax = level, l;
	
	
	count = scandir( path, &files, file_select, alphasort);
	/* If no files found, make a non-selectable menu item */
	if (count <= 0)
	{
		return -1;
	}
	
	for (i=1;i<count+1;++i)
	{
		printf("%*s[%s]\n",4*level, "",files[i-1]->d_name);
						
		//pega infos do arquivo
		if(stat(files[i-1]->d_name, &info) == 1)
		{
			printf("erro ao pegar arquivo\n");
		}
		
		if((int)(files[i-1]->d_type) == 4)
		{
			strcat(temp, path);
			strcat(temp, "/");
			strcat(temp, files[i-1]->d_name);
			l = percorre(temp, &n, &t, level +1);
			if(l > lmax)
			{
				lmax = l;
			}
		}
		
		
		n++;
		t += info.st_size;
		strcpy(temp, "");
		
	}
	
	*tam += t;
	*nArq += n;
	
	return lmax;
	
	
}

int main(void)
{  
	size_t size = MAXPATHLEN; 
	char pathname[MAXPATHLEN];
	
	//contadores para numero de arquivos e tamanho total
	long int nArq = 0, tam = 0;	
	int lmax;
	
	if (getcwd(pathname, size) == NULL )
	{  
		printf("Error getting path\n");
		exit(0);
	}
	
	printf("Current Working Directory = %s\n",pathname);
	
	lmax = percorre(pathname, &nArq, &tam, 0);
	
	printf("Total number of files = %ld\n",nArq);
	printf("Total size of files = %ld\n",tam);
	printf("Profundidade máxima = %d\n", lmax);
	
	printf("\n"); /* flush buffer */ 
	return 0;
}
