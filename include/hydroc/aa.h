//Funcoes para tratamento da AA - Matriz de Area Acumulada
//Primeira versao: 15/03/13
//Ultima atualizacao: 25/06/13
         
         
void bacia_f(int **ldd, int **bacia, int n, int y, int exui, int exuj); // funcao para chamar a matriz bacia para utilizar seus parametros

void area_f(int **ldd, int **bacia, int**area, int n, int y){ // funcao para criacao da matriz area

 int xi, xj;
 
 for (xi=1; xi<=n-2; xi++){                         
      for (xj=1; xj<=y-2; xj++){         
           area[xi][xj]=0;            
           // laço para determinar os exus             
           bacia_f(ldd, bacia, n, y, xi-1, xj-1);
          
           area[xi][xj]=tambacia;             
      }//for j
 }//for i

}//area_f
