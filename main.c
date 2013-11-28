/*=============================================================================

				Projeto de ICC - Grupo Burn
		
				- Arquivo principal (main.c)
				
	Programa desenvolvido para corrigir o curso d'agua de uma matriz DEM , 
	utilizando o metodo de BURN
==============================================================================*/     
           
// Bibliotecas 
#include <stdlib.h>
#include <stdio.h>
#include "hydroc.h"

// Inicio do programa
int main()
{
	
	/*---------------------------------------------------------------------------------
					Declaracao de Variaveis
	---------------------------------------------------------------------------------*/
	int i,j;   //i para linhas, j para colunas (matrizes)
	int n, y;   //i para linhas, j para colunas (matrizes)
	int valdng;              // valor que sera usado para delimitar a drenagem

	FILE *arqrio, *arqdem,*arqoutput;  // ponteiro para leitura das matrizes DEM e RIO
	
	//Arquivos externos
    arqdem = fopen ("dem_arquivo.txt","r"); //Arquivo DEM CORRIGIDO!
	arqrio = fopen ("rioBURN.txt","r"); //Arquivo rio BURN!
	arqoutput = fopen ("output.txt","w"); //Arquivo de saida
	
	//Ponteiros 
	int **dem;                // ponteiro para o DEM
	int **ldd;                // ponteiro para o LDD
	int **bacia;              // ponteiro para a bacia
	int **area;               // ponteiro para a AA
	int **rio;                // ponteiro para a AA
	int **drenagem;           // ponteiro para a drenagem
	int **novadrenagem;       // ponteiro para a novadrenagem
	int **burn;               // ponteiro para o burn
	
	//Funcoes
	void rioBurn(int **rio,int **drenagem, int **burn, int n,int y);
	void burn_f(int **rioburn,int **dem,int **burn, int n, int y);
		
	
	/*---------------------------------------------------------------------------------
					Inicio do programa burn
	---------------------------------------------------------------------------------*/
	printf("\n\n");
	printf("\n\n\t--------------------------------------------------------");
	printf("\n\n\t\t\t\tBURN\t\t\t");
	printf("\n\n\t--------------------------------------------------------\n\n\n");
	
	printf("Entre com a quantidade de Linhas da matriz DEM: ");
	scanf("%3d",&n);
	printf("\nEntre com a quantidade de Colunas da matriz DEM: ");
	scanf("%3d",&y);
	printf("\n\n");
	system("cls");
	
	
	/*---------------------------------------------------------------------------------
					Alocacao dinamica de memoria (matrizes)
	---------------------------------------------------------------------------------*/
	dem = (int **)calloc(n, sizeof(int *));  // alocar a matriz dem                                     
	for (i=0; i<n; i++) dem[i] = (int *)calloc(y, sizeof(int));
	
	rio = (int **)calloc(n, sizeof(int *));  // alocar a matriz ldd
	for (i=0; i<n; i++) rio[i] = (int *)calloc(y, sizeof(int));	
	
	ldd = (int **)calloc(n, sizeof(int *));  // alocar a matriz ldd
	for (i=0; i<n; i++) ldd[i] = (int *)calloc(y, sizeof(int));
	
	bacia = (int **)calloc(n, sizeof(int *));  // alocar a matriz bacia
	for (i=0; i<n; i++) bacia[i] = (int *)calloc(y, sizeof(int));
	
	area = (int **)calloc(n, sizeof(int *));  // alocar a matriz area
	for (i=0; i<n; i++) area[i] = (int *)calloc(y, sizeof(int));
	
	drenagem = (int **)calloc(n, sizeof(int *));  // alocar a matriz drenagem
	for (i=0; i<n; i++) drenagem[i] = (int *)calloc(y, sizeof(int));
	
	novadrenagem = (int **)calloc(n, sizeof(int *));  // alocar a matriz drenagem
	for (i=0; i<n; i++) novadrenagem[i] = (int *)calloc(y, sizeof(int));
	
	burn = (int **)calloc(n, sizeof(int *));  // alocar a matriz drenagem
	for (i=0; i<n; i++) burn[i] = (int *)calloc(y, sizeof(int));
		

	/*---------------------------------------------------------------------------------
					Leitura do arquivo DEM
	---------------------------------------------------------------------------------*/
	printf("\nDEM: \n\n");
	fprintf(arqoutput,"\nDEM: \n\n");
	
	dem_f3(arqdem, dem, n, y);
	
	imprimir_tela(dem,0,n-1);  // funcao que imprime a matriz DEM na tela  
	imprimir_arq(arqoutput,dem,0,n-1); // funcao que imprime a matriz DEM  no arquivo

	/*---------------------------------------------------------------------------------
					Leitura do arquivo RIO
	---------------------------------------------------------------------------------*/
	printf("\nRIO: \n\n");
	fprintf(arqoutput,"\nRIO: \n\n");	
	
	dem_f3(arqrio,rio,n,y);
	imprimir_tela(rio,1,n-2);  // funcao que imprime a matriz RIO na tela  
	imprimir_arq(arqoutput,rio,1,n-2); // funcao que imprime a matriz RIO  no arquivo
		
	/*---------------------------------------------------------------------------------
					LDD, Bacia e AA
	---------------------------------------------------------------------------------*/	
	
	ldd_f(dem, ldd, n, y); // chamar a funcao para gerar a matriz de LDD
	bacia_f(ldd, bacia, n, y, 2, 2);
	area_f(ldd, bacia, area, n, y);
	
	/*---------------------------------------------------------------------------------
					Drenagem
	---------------------------------------------------------------------------------*/	
	printf("\nEntre com o valor de drenagem: ");
	scanf("%d",&valdng); // valdng representa o valor de drenagem que sera passado para a operacao de delimitacao de drenagem na matriz DEM
	
	drenagem_f (area, drenagem, n, y, valdng); // chama a funcao que gera a matriz drenagem
	
	printf("\nDRENAGEM: \n\n");
	fprintf(arqoutput,"\nDRENAGEM: \n\n");
	
	imprimir_tela(drenagem,1,n-2); // funcao que imprime a matriz drenagem na tela
	imprimir_arq(arqoutput,drenagem,1,n-2); // funcao que imprime a matriz drenagem no arquivo
	
	/*---------------------------------------------------------------------------------
					Ajuste da matriz drenagem com o novo rio
	---------------------------------------------------------------------------------*/	
	
	rioBurn(rio,drenagem,novadrenagem,n,y);

	printf("\nDRENAGEM NOVA: \n\n");
	fprintf(arqoutput,"\nDRENAGEM NOVA: \n\n");	
	imprimir_tela(novadrenagem,1,n-2); // funcao que imprime a matriz de drenagem + rio novo na tela
	imprimir_arq(arqoutput,novadrenagem,1,n-2); // funcao que imprime a matriz drenagem + rio novo  no arquivo	

	/*---------------------------------------------------------------------------------
					Processo de BURN - Afundamento
	---------------------------------------------------------------------------------*/		
	
	burn_f(novadrenagem,dem,burn,n,y);
	
	printf("\nBURN - NOVO DEM: \n\n");
	fprintf(arqoutput,"\nBURN NOVO DEM: \n\n");	
	imprimir_tela(burn,1,n-2); // funcao que imprime a matriz de drenagem + rio novo na tela
	imprimir_arq(arqoutput,burn,1,n-2); // funcao que imprime a matriz drenagem + rio novo  no arquivo	
	
	/*---------------------------------------------------------------------------------
					Liberacao de memoria
	---------------------------------------------------------------------------------*/	
	free(dem); 
	free(ldd);
	free(bacia);
	free(area);
	free(rio);
	free(novadrenagem);
	free(drenagem);
	fclose(arqdem);
	fclose(arqrio);
	fclose(arqoutput);	
	
	/*---------------------------------------------------------------------------------
					Fim do programa
	---------------------------------------------------------------------------------*/	
		
	system("pause");
	return 0;

}


void rioBurn(int **rio,int **drenagem, int **novadrenagem, int n, int y){
 for(i=1;i<=n-1;i++) for(j=1;j<=n-1;j++) novadrenagem[i][j]=0;
 
	for(i = 0; i <n-1; i++){
		for(j = 0; j <y-1 ; j++)
		{
			novadrenagem[i][j] = rio[i][j] + drenagem[i][j];
			if(novadrenagem[i][j]== 0)
			{
				novadrenagem[i][j] = 1;
			}else
			{
				novadrenagem[i][j] = 0;
			}
		}
	}
}

void burn_f(int **novadrenagem,int **dem,int **burn, int n, int y){
	for(i = 0; i <n-1; i++){
		for(j = 0; j <y-1 ; j++)
		{
			burn[i][j] = dem[i][j] * novadrenagem[i][j];
		}
	}
}
