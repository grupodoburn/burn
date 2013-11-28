//Funcao para imprimir matriz em tela
//Primeira versao: 15/03/13
//Ultima atualizacao: 25/06/13
         
                 
void imprimir_tela(int **matriz, int inicio, int final){    
     
  for (i=inicio; i<=final; i++){
       for (j=inicio; j<=final; j++){
            printf("\t%4d ", matriz[i][j]);
       }
       printf("\n");      
  }

  printf("\n");
  
}//funcao
