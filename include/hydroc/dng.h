//Funcoes para tratamento de Drenagem - Matriz de drenagem
//Primeira versao: 15/03/13
//Ultima atualizacao: 25/06/13


void drenagem_f(int **area, int **drenagem, int n, int y, int valdng){

for (i=1; i<=n-2; i++){                         
    for (j=1; j<=y-2; j++){                     

    if(area[i][j] < valdng) drenagem[i][j] = 0;
    
    if (area[i][j] >= valdng) drenagem[i][j] = 1;
        
    }//for i
    
 }//for j
    
}//funcao
