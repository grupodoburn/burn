/*=============================================================================

				Projeto de ICC - Grupo Burn
		
				- Arquivo principal (main.c)
				
	Programa desenvolvido para corrigir o curso d'água de uma matriz DEM, 
	utilizando o metodo de BURN.
	
==============================================================================*/     
           
// Bibliotecas 
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <hydroc.h>

// Início do programa
int main(){

/*------------------------------------------------------------------------------
					        Declaração de Variáveis
------------------------------------------------------------------------------*/
	
    int i,j;
    // i para linhas, j para colunas (matrizes)
	int n, y;
    // n para linhas, y para colunas (matrizes)
	int valdng;
    // Valor que será usado para delimitar a drenagem

    double tI, tF, tempo_gasto; 
    // Variáveis da contagem do tempo de computação

	FILE *arqrio, *arqdem, *arqoutput;
    // Ponteiros para leitura das matrizes DEM, RIO e para o arquivo de saída
	
	
	/*                         Arquivos externos                              */
    arqdem = fopen ("dem_arquivo.txt","r"); 
    //Arquivo de DEM a ser modificado
	arqrio = fopen ("rioBURN.txt","r");     
    //Arquivo de rio mostrando a mudança a ser implementada
	arqoutput = fopen ("output.txt","w");   
    //Arquivo de saída
	
	
	/*                            Ponteiros                                   */
	int **dem;                    // Ponteiro para a Matriz do DEM
	int **ldd;                    // Ponteiro para a Matriz de LDD
	int **bacia;                  // Ponteiro para a Matriz da Bacia
	int **area;                   // Ponteiro para a Matriz de Área Acumulada
	int **rio;                    // Ponteiro para a Matriz do Rio
	int **drenagem;               // Ponteiro para a Matriz de Drenagem
	int **drenagem_aditiva;       // Ponteiro para a Matriz de Drenagem + Rio
	int **drenagem_aditiva_inv;   // Ponteiro para a Matriz de Drenagem + Rio Invertida
	int **DEM_burned;             // Ponteiro para a Matriz do DEM "Queimado"
	
	
	/*                             Funções                                    */
    void rioBurn(int **rio,int **drenagem, int **drenagem_aditiva, int **drenagem_aditiva_inv, int n, int y);
	void burn_f(int **drenagem_aditiva_inv,int **dem, int **DEM_burned, int n, int y);
	
	tI = clock(); 
    //Iniciada a contagem de tempo de computação 
	
/*------------------------------------------------------------------------------
                           Início do programa burn
------------------------------------------------------------------------------*/
	printf("________________________________________________________________________________");
	printf("\n\n                                      BURN");
	printf("\n\n________________________________________________________________________________\n\n\n");

    printf("              Nao se esqueca de nomear os arquivos de entrada como\n                       'dem_arquivo.txt' e 'rioBURN.txt'!\n\n\n\n");
    system("pause");
    system("cls");
    
    printf("________________________________________________________________________________");
	printf("\n\n                                      BURN");
	printf("\n\n________________________________________________________________________________\n\n\n");
	
	printf("Entre com a quantidade de Linhas da matriz DEM: ");
	scanf("%3d",&n);
	printf("\nEntre com a quantidade de Colunas da matriz DEM: ");
	scanf("%3d",&y);
	printf("\n");

	
	
/*------------------------------------------------------------------------------
					Alocação dinâmica de memória (matrizes)
------------------------------------------------------------------------------*/
	dem = (int **)calloc(n, sizeof(int *));  // Alocar a Matriz do DEM                                     
	for (i=0; i<n; i++) dem[i] = (int *)calloc(y, sizeof(int));
	
	rio = (int **)calloc(n, sizeof(int *));  // Alocar a Matriz do Rio
	for (i=0; i<n; i++) rio[i] = (int *)calloc(y, sizeof(int));	
	
	ldd = (int **)calloc(n, sizeof(int *));  // Alocar a Matriz de ldd
	for (i=0; i<n; i++) ldd[i] = (int *)calloc(y, sizeof(int));
	
	bacia = (int **)calloc(n, sizeof(int *));  // Alocar a Matriz da Bacia
	for (i=0; i<n; i++) bacia[i] = (int *)calloc(y, sizeof(int));
	
	area = (int **)calloc(n, sizeof(int *));  // Alocar a Matriz de Área Acumulada
	for (i=0; i<n; i++) area[i] = (int *)calloc(y, sizeof(int));
	
	drenagem = (int **)calloc(n, sizeof(int *));  // Alocar a Matriz de Drenagem
	for (i=0; i<n; i++) drenagem[i] = (int *)calloc(y, sizeof(int));
	
	drenagem_aditiva = (int **)calloc(n, sizeof(int *));  // Alocar a Matriz de Drenagem + Rio
	for (i=0; i<n; i++) drenagem_aditiva[i] = (int *)calloc(y, sizeof(int));
	
	drenagem_aditiva_inv = (int **)calloc(n, sizeof(int *));  // Alocar a Matriz de Drenagem + Rio Invertida
	for (i=0; i<n; i++) drenagem_aditiva_inv[i] = (int *)calloc(y, sizeof(int));
	
	DEM_burned = (int **)calloc(n, sizeof(int *));  // Alocar a Matriz do DEM "Queimado"
	for (i=0; i<n; i++) DEM_burned[i] = (int *)calloc(y, sizeof(int));
		

/*------------------------------------------------------------------------------
					       Leitura do arquivo DEM
------------------------------------------------------------------------------*/
	
	fprintf(arqoutput,"\n MATRIZ DO DEM: \n\n");
	
	dem_f3(arqdem, dem, n, y);
	
	imprimir_arq(arqoutput,dem,0,n-1); 
    // Função que imprime a Matriz do DEM no arquivo

/*------------------------------------------------------------------------------
					       Leitura do arquivo RIO
------------------------------------------------------------------------------*/
    
	fprintf(arqoutput,"\n MATRIZ DO RIO: \n\n");	
	
	dem_f3(arqrio,rio,n,y);
	
	imprimir_arq(arqoutput,rio,0,n-1); 
    // Função que imprime a Matriz do rio  no arquivo
		
/*------------------------------------------------------------------------------
					           LDD, Bacia e AA
------------------------------------------------------------------------------*/	
	
	ldd_f(dem, ldd, n, y); // chamar a funcao para gerar a matriz de LDD
	bacia_f(ldd, bacia, n, y, 2, 2);
	area_f(ldd, bacia, area, n, y);
	
/*------------------------------------------------------------------------------
                                   Drenagem
------------------------------------------------------------------------------*/	
	printf("Entre com o valor de drenagem: ");
	scanf("%d",&valdng); 
    /* valdng representa o valor de drenagem que será passado para a 
       operação de delimitação de drenagem na matriz do DEM */
	
	system("cls");
	// "Limpando" a tela
	
	drenagem_f(area, drenagem, n, y, valdng); 
    // Chama a função que gera a Matriz Drenagem
	
	fprintf(arqoutput,"\n MATRIZ DRENAGEM DO DEM: \n\n");
	
	imprimir_arq(arqoutput,drenagem,0,n-1); 
    // Função que imprime a Matriz de Drenagem no arquivo
	
/*------------------------------------------------------------------------------
					Ajuste da matriz drenagem com o novo rio
------------------------------------------------------------------------------*/	
                                                                                
	rioBurn(rio,drenagem,drenagem_aditiva,drenagem_aditiva_inv,n,y);

	fprintf(arqoutput,"\n MATRIZ DRENAGEM + MATRIZ RIO: \n\n");
	
	imprimir_arq(arqoutput,drenagem_aditiva,0,n-1); 
    // Função que imprime a Matriz de Drenagem + Matriz do Rio no arquivo	

/*------------------------------------------------------------------------------
					   Processo de BURN - Afundamento
------------------------------------------------------------------------------*/		
	
	burn_f(drenagem_aditiva_inv,dem,DEM_burned,n,y);
	
	fprintf(arqoutput,"\n MATRIZ DEM 'QUEIMADO': \n\n");
	
	imprimir_arq(arqoutput,DEM_burned,0,n-1); 
    // Função que imprime a Matriz de Drenagem + Matriz do Rio Invertida no arquivo
    
/*------------------------------------------------------------------------------
                         Mostrando arquivos em tela
------------------------------------------------------------------------------*/
    printf("________________________________________________________________________________");
    
    printf("\n\n MATRIZ DEM: \n\n");
   	imprimir_tela(dem,0,n-1);  
    // Função que imprime a Matriz do DEM na tela  
    
    printf("\n MATRIZ RIO: \n\n");
	imprimir_tela(rio,0,n-1);  
    // Função que imprime a Matriz do rio na tela 
    
    printf("\n MATRIZ DRENAGEM DO DEM: \n\n");
   	imprimir_tela(drenagem,0,n-1); 
    // Função que imprime a Matriz de Drenagem na tela
    
    printf("\n MATRIZ DRENAGEM + MATRIZ RIO: \n\n");
    imprimir_tela(drenagem_aditiva,0,n-1); 
    // Função que imprime a Matriz de Drenagem + Matriz do Rio na tela
    
   	printf("\n MATRIZ DEM 'QUEIMADO': \n\n");
    imprimir_tela(DEM_burned,0,n-1);
    // Função que imprime a Matriz de Drenagem + Matriz do Rio Invertida na tela
    
    printf("\n\n________________________________________________________________________________\n\n");
/*------------------------------------------------------------------------------
					        Liberacao de memoria
------------------------------------------------------------------------------*/	
	free(dem); 
	free(ldd);
	free(bacia);
	free(area);
	free(rio);
	free(drenagem_aditiva);
	free(drenagem_aditiva_inv);
	free(drenagem);
	free(DEM_burned);
	fclose(arqdem);
	fclose(arqrio);
	fclose(arqoutput);	
	
/*------------------------------------------------------------------------------
                              Contagem de tempo
------------------------------------------------------------------------------*/	
	tF = clock(); // Terminando a contagem do tempo de processamento
  
    tempo_gasto = ( (double) (tF - tI) ) / CLOCKS_PER_SEC;
    
    printf("\nO tempo gasto no processo foi de %.2f segundos.\n\n\n", tempo_gasto);
    
    system("pause");
    system("cls");
    
/*------------------------------------------------------------------------------
                                Agradecimentos
------------------------------------------------------------------------------*/
    printf("________________________________________________________________________________\n\n");
    printf("                                   GRUPO BURN");
    printf("\n\n________________________________________________________________________________\n\n");
    printf("   MEMBROS:\n\n");
    printf(" - Erika Sanchez\n - Gabriel Mineiro\n - Gustavo Zielo\n - Lucas Magno\n - Lucas Valerio\n - Marcos Tadao\n - Roberta Vieira\n\n");
    printf("\n   Agradecimentos aos professor Leonardo Bacelar Lima Santos\n   pela assistencia na realizacao do trabalho.\n\n");
    
    printf("________________________________________________________________________________\n\n");
    printf("                              WE GONNA LET IT BURN!");
    printf("\n\n________________________________________________________________________________\n\n");
/*------------------------------------------------------------------------------
				              	Fim do programa
------------------------------------------------------------------------------*/	
		
	system("pause");
	return 0;

}

/*------------------------------------------------------------------------------
		        	Funções a serem chamadas fora da Hydroc
------------------------------------------------------------------------------*/	

void rioBurn(int **rio,int **drenagem, int **drenagem_aditiva, int **drenagem_aditiva_inv, int n, int y){
 for(i=0;i<=n-1;i++) for(j=0;j<=n-1;j++) drenagem_aditiva[i][j]=0;
 
	for(i = 0; i <n; i++){
		for(j = 0; j <y ; j++)
		{
			drenagem_aditiva[i][j] = rio[i][j] + drenagem[i][j];
			if(drenagem_aditiva[i][j]== 0)
			{
				drenagem_aditiva_inv[i][j] = 1;
			}else
			{
				drenagem_aditiva_inv[i][j] = 0;
			}
		}
	}
}

void burn_f(int **drenagem_aditiva_inv,int **dem,int **DEM_burned, int n, int y){
	for(i = 0; i <n; i++){
		for(j = 0; j <y ; j++)
		{
			DEM_burned[i][j] = dem[i][j] * drenagem_aditiva_inv[i][j];
		}
	}
}
