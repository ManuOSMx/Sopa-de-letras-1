#include<string.h>
#include<stdio.h>
#include<stdlib.h>

void archivo(char nomb);
void impmat(char mat[][20]);
void llenmat(char mat[][20]);
int buscar(char *pal, char mat[][20],char nombAR, int num);
//Creamos un apuntador a archivo para ahí guardar los resultados
	FILE *ap;
	
int main(void){

	int num,c,x;
	char matriz[20][20]; //Definir el tamaño de la matriz 
	char pal[20],nombreAR[20];

//Llamamos primero a la funcion para llenar la matriz con las dimensiones dadas anteriormente
	llenmat(matriz);
//Una vez creada la matriz, la imprimiremos en pantalla
	impmat(matriz);
	
//Se creara un archivo .txt por defecto con el nombre que el usuario coloque
//Ahí se guardarán los resultados de las busquedas
	printf("¿Cual es el nombre del archivo?\n");
	scanf("%s",&nombreAR);

//Colocas cuantas palabras buscarás en la matriz Ej.: 1, 2, 3,  ...
	printf("Cuantas palabras buscaras?\n");
	scanf("%d",&num);

	
	for(c=0;c<num;c++){
		// Recibira la palabra en especifico que se mandara a buscar
		printf("Que palabra es?\n"); 
		scanf("%s",&pal);
		//Verifica si puede abrir el archivo guardado en la variable nombreAR
		if((ap=fopen(nombreAR,"w"))==NULL)
		{
			fprintf(stderr,"ERROR AL ABRIR\n");
			exit(1);
		}
		// Empezara a buscar la palabra en la funcion "BUSCAR" y verificara si esa palabra existe o no.
		if(buscar(pal, matriz,nombreAR,num)==1){  
			printf("\n--Existe--\n");

		}
		else{
			printf("\n--No existe--\n");
		}
	}

	return 0;
}
//------------------------------------funciones--------------------------------------//

//Se llenara la matriz mediante caracteres de forma aleatoria
void llenmat(char mat[][20])
{
	int i, j;
	//Crearemos una semilla para gererar caracteres de forma aleatoria
	srand(rand()); 
	for(i = 0; i < 20; i++) 
	{ 
	 for(j = 0; j < 20; j++) 
		{ 
		//Definimos el rango de caracteres [Para que solo sean letras minúsculas(Rango ASCII: 97 al 122)] que imprimira en pantalla ( Revisar tabla ASCII)
			mat[i][j]= (rand()%26)+97;
		}
	}
}

//---------------Creamos la funcion para poder imprimir la matris generada---------//
void impmat(char mat[][20])
{	
	int i, j;
	for(i = 0; i < 20; i++) 
	{ 
	printf("\t\t| ");
	 for(j = 0; j < 20; j++) 
		{ 
			printf("%c  ",mat[i][j]);
		}
		printf("|%d\n",i);
	}
	printf("\t\t  ___________________________________________________________\n");
	printf("\t\t  0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19\n");
}

//----------------Busqueda dentro de la matriz ------------ //
int buscar(char *pal, char mat[][20], char nombAR, int num){

	
	//Buscar en Horizontal1//
	int i,j,k,x;

	for(i = 0; i < 20; i++) 
	{ 
	 for(j = 0; j < 20; j++) 
		{ 
			if(mat[i][j]==pal[0]){
				char tempal[21] = "";
				for(k=j;k<20;k++){
					tempal[k-j]=mat[i][k];
					printf("%s\n",tempal);
					tempal[k-j+1]='\0';
					if(strcmp(pal,tempal)==0){
						printf("\n\nSe encontro la palabra en:\n Horizontal con posicion x=%d y=%d",j,i);
						for(x=0;x<num;x++){
						
							fprintf(ap,"	%d	|Palabra:	%s	|  Horizontal | Posicion X = %d  y Y= %d \n",x+1,pal,j,i);
						}
						return 1;
					}
				}
			}
			
		}
	}
	
	//Buscar en vertical//
	for(i = 0; i < 20; i++) 
	{ 
	 for(j = 0; j < 20; j++) 
		{ 
			if(mat[i][j]==pal[0]){
				char tempal[21] = "";
				for(k=i;k<20;k++){
					tempal[k-i]=mat[k][j];
					printf("%s\n",tempal);
					tempal[k-i+1]='\0';
					if(strcmp(pal,tempal)==0){
						printf("Es vertical con Posicion x=%d y=%d",j,i);
						for(x=0;x<num;x++){
						
							fprintf(ap,"	%d	|Palabra:	%s	|  Vertical | Posicion X = %d  y Y= %d \n",x+1,pal,j,i);
						}
						return 1;
					}
				}
			}
			
		}
	}
//Cerramos el apuntador a archivo
	fclose(ap);
	return 0;
}
