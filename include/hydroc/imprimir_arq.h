//Funcao para imprimir matriz em arquivo
//Primeira versao: 15/03/13
//Ultima atualizacao: 25/06/13     
         
         
void imprimir_arq(FILE *arq1, int **matriz, int inicio, int final){    

  for (i=inicio; i<=final; i++){
       for (j=inicio; j<=final; j++){
            fprintf(arq1,"%4d ", matriz[i][j]);
       }
       fprintf(arq1,"\n");      
  }

  fprintf(arq1,"\n\n");

}//funcao
