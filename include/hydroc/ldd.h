//Funcoes para tratamento do LDD
//Primeira versao: 15/03/13
//Ultima atualizacao: 25/06/13
                             
                    
void ldd_f(int **dem, int **ldd, int n, int y){ // função para a criação da matriz de ldd 
     
 int max, aux;
 int k, h, decli;

 ldd[0][0]=1;
 ldd[n-1][0]=7;
 ldd[0][n-1]=3;
 ldd[n-1][n-1]=9;
 for(i=1;i<=n-2;i++) ldd[i][0]=4;
 for(i=1;i<=n-2;i++) ldd[i][n-1]=6;
 for(j=1;j<=n-2;j++) ldd[0][j]=2;
 for(j=1;j<=n-2;j++) ldd[n-1][j]=8;

 for (i=1; i<=n-2; i++){
      for (j=1; j<=y-2; j++){
        
      max=0;
      aux=0;
        
      for (k=-1;k<=1;k++){
           for (h=-1;h<=1;h++){

                aux++;
                decli = dem[i][j] - dem[i+k][j+h];
                //printf("i=%4d, j=%4d, k=%4d, h=%4d, decli=%4d, max=%4d",i,j,k,h,decli, max); // i j k h decli max_antes 
                //printf("\n\n");
            
                if (decli > max){
                    max = decli;
                    ldd[i][j]= aux;
                }     
                //printf("max=%4d, ldd=%4d");
                //printf("\n\n");
                //max_depois ldd    
         } //h
      } //k

      if (max==0) ldd[i][j] = 5;
      } //j 
   } //i
} //funcao


