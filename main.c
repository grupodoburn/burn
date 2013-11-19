/*=============================================================================

				Projeto de ICC - Grupo Burn
		
				- Arquivo principal (main.c)
				
	Programa desenvolvido para corrigir o curso d'agua de uma matriz DEM , 
	utilizando o metodo de BURN
==============================================================================*/     
           
// Bibliotecas 
#include <stdlib.h>
#include <stdio.h>
#include <hydroc.h>

// Inicio do programa
int main()
{
	
	//variaveis
	//int i, j;   //i para linhas, j para colunas (matrizes)
	
	//FILE *arqrio, *arqdem;  // ponteiro para leitura das matrizes DEM e RIO
	
	//Arquivos externos
    //arqdem = fopen ("dem_arquivo.txt","r"); //Arquivo DEM CORRIGIDO!
	//arqrio = fopen ("rioBURN.txt","r"); //Arquivo rio BURN!

	
	
	// CABEÇALHO
	printf("\n\n");
	printf("\n\n\t--------------------------------------------------------");
	printf("\n\n\t\t\t\tBURN\t\t\t");
	printf("\n\n\t--------------------------------------------------------\n\n\n");
	//---------------------------------------------------------------------------------
	
	printf("Entre com a quantidade de Linhas: ");
	scanf("%3d",&n);
	printf("\nEntre com a quantidade de Colunas: ");
	scanf("%3d",&y);
	printf("\n\n");
	system("cls");
	
	
	
	
	system("pause");
	return 0;

}
