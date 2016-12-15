#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include<stdlib.h>

#include <stdio.h>



//3 linhas por 4 colunas
int main (int argc,char *argv[]) 
{ 
	//segmentos de memoria de mat1, 2 e 3.
	int seg_mat1, seg_mat2, seg_mat3;
	
	//ponteiros para matrizes mat1, 2 e 3.
	int *mat1, *mat2, *mat3;
	
	int idpai, pid, status;
	int id; 
	
	int linhas = 3;
	int colunas = 4;
	
	int i,j,c;
	
	
	// aloca a memória compartilhada das tres matrizes
	seg_mat1 = shmget (IPC_PRIVATE, sizeof(int)*linhas*colunas, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
	seg_mat2 = shmget (IPC_PRIVATE, sizeof(int)*linhas*colunas, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
	seg_mat3 = shmget (IPC_PRIVATE, sizeof(int)*linhas*colunas, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
	
	// associa a memória compartilhada ao processo
	mat1 = (int*) shmat (seg_mat1, 0, 0);
	mat2 = (int*) shmat (seg_mat2, 0, 0);
	mat3 = (int*) shmat (seg_mat3, 0, 0);
	
	
	// comparar o retorno com -1
	if((mat1) == -1 || (mat2) == -1 || (mat3) == -1 || (id) == -1)
	{
		puts("erro de associação de memória\n");
		exit(-1);
	}
	
	c = 0;
	
	for(i=0; i < linhas; i++)
	{
		for(j=0; j < colunas;j++)
		{
			mat1[i*colunas+j] = c;
			c++;
			
		}
	}
	
	for(i=0; i < linhas; i++)
	{
		for(j=0; j < colunas;j++)
		{
			mat2[i*colunas+j] = c;
			c--;
		}
	}
	
	
	idpai = getpid();
	id = fork();
	
	
	if(id < 0)
	{
		puts ("Erro na criação do novo processo"); 
		exit (-2); 
	}
	//processo filho1
	if(id == 0)
	{
		for(j=0;j < colunas;j++)
		{
			mat3[0*colunas+j] = mat1[0*colunas+j] + mat2[0*colunas + j];
		}
		id = fork();
		//filho2
		if(id == 0)
		{
			for(j=0;j < colunas;j++)
			{
				mat3[1*colunas+j] = mat1[0*colunas+j] + mat2[0*colunas + j];
			}
		id = fork();
		//filho3
		if(id == 0)
		{
			for(j=0;j < colunas;j++)
			{
				mat3[2*colunas+j] = mat1[0*colunas+j] + mat2[0*colunas + j];
			}
		}
		
	}
	}
	
	//processo pai
	if (getpid() == idpai)
	{
		wait (&status);
		for(i=0; i < linhas; i++)
		{
			for(j=0; j < colunas;j++)
			{
				printf("mat3[%d][%d]: %d\n", i, j, mat3[i*colunas+j]);
			}
		}
		
	}
	
	
	// libera a memória compartilhada do processo
	shmdt (mat1);
	shmdt (mat2);
	shmdt (mat3); 
	// libera a memória compartilhada
	shmctl (seg_mat1, IPC_RMID, 0); 
	shmctl (seg_mat2, IPC_RMID, 0); 
	shmctl (seg_mat2, IPC_RMID, 0);  
	return 0; 
} 
