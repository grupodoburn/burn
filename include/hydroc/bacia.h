//Funcoes para tratamento das Bacias Hidrograficas
//Primeira versao: 15/03/13
//Ultima atualizacao: 25/06/13


void bacia_f(int **ldd, int **bacia, int n, int y, int exui, int exuj){ // funcao utilizada para a criacao da matriz bacia              
      
 int novotambacia; 

 tambacia = 0; // variavel global
 novotambacia = 1;

 for (i=1; i<=n-2; i++) for (j=1; j<=y-2; j++) bacia[i][j]=0; // gerar a matriz com valores zerados                      
     
 tambacia = 0;
 novotambacia = 1;

 exui++; 
 exuj++;

 bacia[exui][exuj]=1;

 while (novotambacia > tambacia){
                
       tambacia = novotambacia;
      
   for (i=1; i<=n-2; i++){                         
        for (j=1; j<=y-2; j++){                       
             if (bacia[i][j]==1){                        

                 if(ldd[i-1][j-1]==9) {      // 1
                    bacia[i-1][j-1]=1; 
                    novotambacia++;
                 }
           
                 if(ldd[i-1][j]==8) {        //2
                    bacia[i-1][j]=1; 
                    novotambacia++;
                 }
           
                 if(ldd[i-1][j+1]==7) {      //3
                    bacia[i-1][j+1]=1; 
                    novotambacia++;
                 }
           
                 if(ldd[i][j-1]==6) {        //4
                    bacia[i][j-1]=1; 
                    novotambacia++;
                 }
           
                 if(ldd[i][j+1]==4) {        //6
                    bacia[i][j+1]=1; 
                    novotambacia++;
                 }
           
                 if(ldd[i+1][j-1]==3) {      //7
                    bacia[i+1][j-1]=1; 
                    novotambacia++;
                 }
           
                 if(ldd[i+1][j]==2) {        //8
                    bacia[i+1][j]=1; 
                    novotambacia++;
                 }
           
                 if(ldd[i+1][j+1]==1) {      // ativo = 9
                    bacia[i+1][j+1]=1; 
                    novotambacia++;
                 }
           
                 bacia[i][j]=2;
              
        }// if
    }//for i
  }//for j
 }//while
}//funcao
