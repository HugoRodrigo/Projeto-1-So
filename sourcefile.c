/*------Progeto 1 SO----------
* Hugo Rodrigo Gomes de Castro - 2707
* Igor de Oliveira Silva - 3672
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <inttypes.h>
#include <time.h>


typedef struct sCommand{
	int init;
	char command[50];
	char parameterA[50];
	char parameterB[50];
	char parameterC[50];
}Command;

void ls(char folder[100]){
	DIR *dir;
    struct dirent *lsdir;
    struct stat statbuf;
    char dirAux[200];
	char time[50];
	
    dir = opendir(folder);
	if (dir==NULL){
		perror("Erro ao abrir diretorio");
		return;
	}
	printf ("Tipo\tUltima vez editado\tTamanho \tNome\n");
    while ( ( lsdir = readdir(dir) ) != NULL )
    {
    	strcpy(dirAux,folder);
    	strcat(dirAux,lsdir->d_name);
    	stat(dirAux, &statbuf);
    	if (stat==0) perror("erro: ");
    	
		if(S_ISREG(statbuf.st_mode)) {
			printf("-");
		}
		if(S_ISDIR(statbuf.st_mode)) {
			printf("d");
		}
		if(S_ISCHR(statbuf.st_mode)) {
			printf("c");
		}
	    strftime(time, 50, "%Y-%m-%d %H:%M:%S", localtime(&statbuf.st_mtime));
        printf ("\t%s\t%jd \t\t%s\n",time,(intmax_t)statbuf.st_size, lsdir->d_name);
    }

    closedir(dir);
}

void lerArquivo( char name[]){
    FILE *file ;
    int i;
    char line[1000];
    char * result;
    file = fopen( name , "r" );
    if(file==NULL){
    	perror("Erro ao abrir diretorio");
    	return;
	}
    while (!feof(file))
	{
		result = fgets(line, 1000, file);
		if (result)
			printf(line);
	}
    fclose(file);
}

void criarArquivo( char name[]){
    FILE *file ;
    int i;
    char line[1000];
    file = fopen( name , "w" );
    if(file==NULL){
    	perror("Erro ao abrir diretorio");
    	return;
	}
	printf("Entre com o texto: (Use \"done text\" na ultima linha para finalizar o texto)\n");
    do{
    	printf("-");
    	gets(line);
    	if(strcmp(line,"done text")==0){
    		break;
		}
    	fprintf( file , "%s\n" , line);
	}while(1==1);
    printf("Texto salvo em %s",name);
    fclose(file);
}

void duplicarArquivo( char from[],char to[]){
    FILE *fileFrom ;
    FILE *fileTo;
    int i;
    char line[1000];
    char * result;
    fileFrom = fopen( from , "r" );
	if(fileFrom==NULL){
    	perror("Erro ao abrir arquivo 1");
    	return;
	}
    fileTo = fopen(to,"w");
    if(fileTo==NULL){
    	perror("Erro ao abrir arquivo 2");
    	fclose(fileFrom);
    	return;
	}
    while (!feof(fileFrom))
	{
		result = fgets(line, 1000, fileFrom);
		if (result)
			fprintf( fileTo , "%s" , line);
	}
	printf("\nCopiado texto de %s para %s\n",from,to);
    fclose(fileFrom);
    fclose(fileTo);
}

void grep( char name[], char word[50]){
    FILE *file ;
    int i;
    char line[1000];
    char * result;
    file = fopen( name , "r" );
    if(file==NULL){
    	perror("Erro ao abrir diretorio");
    	return;
	}
    while (!feof(file))
	{
		result = fgets(line, 1000, file);
		if (result && findWord(line,word)==1){
			printf(line);
		}
	}
    fclose(file);
}
int findWord(char line [1000], char word[50]){
	if(strstr(line, word) != NULL)
		return 1;
	return 0;
}

void touchFile( char name[]){
    FILE *file ;
    int i;
    file = fopen( name , "a" );
    if(file==NULL){
    	perror("Erro ao abrir diretorio");
    	return;
	}
	fprintf( file , "%s" , " ");
    fclose(file);
}
void deleteFile(char name[]){
	char i;
	int test;
	printf("\nCerteza que quer deletar o arquino %s:(s/n)\n",name);
	scanf("%c",&i);
	if(i=='s'){
		test = remove(name);
		if(test == 0)
			printf("\nArquivo %s deletado!\n",name);
		else
			printf("\nERRO: Nao foi possivel deletar o arquivo %s!\n",name);
	}else{
		printf("\nArquivo %s nao deletado!\n",name);
	}
}
int main()
{
	int quit = 0;
	char command[100];
	Command commands[20];
	char *token;
	int i =0;
	char dir[100] = "c:/";
	char name[200] = "c:/";
	char nameB[200] = "c:/";
	DIR *dirTest;
	
	for(i=0;i<20;i++){
		commands[i].init= 0;
		strcpy(commands[i].parameterA, "");
		strcpy(commands[i].parameterB, "");
	}
	do {
		i=0;
		fflush(stdin);
		printf("\nmeu-shell> %s> ",dir);
		gets(command);
		token = strtok(command, ",");
		do{
			strcpy(commands[i].command,token);
			commands[i].init = 1;
			token = strtok(NULL, ",");
			i++;
		}while(token != NULL);
		
		i=0;
		do{
			token = strtok(commands[i].command, " ");

			strcpy(command,token);
			token = strtok(NULL, " ");
			if(token != NULL)
				strcpy(commands[i].parameterA,token);
			token = strtok(NULL, " ");
			if(token != NULL)
				strcpy(commands[i].parameterB,token);
			token = strtok(NULL, " ");
			if(token != NULL)
				strcpy(commands[i].parameterC,token);
			strcpy(commands[i].command,command);
			i++;
	
		}while(commands[i].init == 1 && i<20);
		
		i=0;
		do{
			//printf("\nComando: %s\nParemetro 1: %s\nParametro 2: %s\nParametro 3: %s\n",commands[i].command,commands[i].parameterA,commands[i].parameterB,commands[i].parameterC);
			//printf("\n");
			
			
			if(strcmp(commands[i].command,"quit")==0){
				quit=1;
			}
			if(strcmp(commands[i].command,"ls")==0){
				if(strcmp(commands[i].parameterA,"") == 0){
					ls(dir);
				}else{
					printf ("Diretorio: %s\n",commands[i].parameterA);
					ls(commands[i].parameterA);
				}
				
			}
			if(strcmp(commands[i].command,"cd") == 0){
				
			    dirTest = opendir(commands[i].parameterA);
			    if (dirTest==NULL){
					perror("Erro ao abrir diretorio");
				}else{
					closedir(dirTest);
					strcpy(dir,commands[i].parameterA);
				}
							
			}
			
			
			if(strcmp(commands[i].command,"cat")==0){
				if(strcmp(commands[i].parameterA,">")==0){
					strcpy(name,dir);
					strcat(name, "/" );
					strcat(name, commands[i].parameterB );
					criarArquivo(name);
				}else{
					if(strcmp(commands[i].parameterB,">")==0){
						strcpy(name,dir);
						strcat(name, "/" );
						strcat(name, commands[i].parameterA );
						strcpy(nameB,dir);
						strcat(nameB, "/" );
						strcat(nameB, commands[i].parameterC );

						duplicarArquivo(name,nameB);
					}else{	
						strcpy(name,dir);
						strcat(name, "/" );
						strcat(name, commands[i].parameterA );
						lerArquivo(name);
					}
				}
			}
			if(strcmp(commands[i].command,"grep")==0){
				strcpy(name,dir);
				strcat(name, "/" );
				strcat(name, commands[i].parameterB );
				grep(name,commands[i].parameterA);
				
			}
			if(strcmp(commands[i].command,"touch")==0){
				strcpy(name,dir);
				strcat(name, "/" );
				strcat(name, commands[i].parameterA );
				touchFile(name);
			}
			if(strcmp(commands[i].command,"delete")==0){
				strcpy(name,dir);
				strcat(name, "/" );
				strcat(name, commands[i].parameterA );
				dirTest = opendir(name);
			    if (dir==NULL){
					perror("Erro ao abrir diretorio");
				}else{
					closedir(dirTest);
					deleteFile(name);
				}
				
				
			}
			strcpy(commands[i].command,"");
			strcpy(commands[i].parameterA,"");
			strcpy(commands[i].parameterB,"");
			strcpy(commands[i].parameterC,"");
			commands[i].init=0;
			i++;
		}while(commands[i].init==1&&i<20);
		
		
		if(quit == 1)
			break;
			
	} while (1 == 1);
	return 0;
}

