//Funcoes para tratamento do DEM - Modelo Digital de Elevacao
//Primeira versao: 15/03/13
//Ultima atualizacao: 25/06/13
                              
                    
void dem_f1(int **dem, int n, int y){ // funcao para criacao da matriz DEM atraves de valores aleatorios
     
  srand(time(NULL)); // metodo para gerar numeros aleatorios
  for (i=0; i<=n-1; i++) for (j=0; j<=y-1; j++) dem[i][j] = rand()%256; // laço para gerar a matriz com os valores aleatorios

} // encerra funcao dem_f1

////////////////////////////////////////////////////////////////////////////////

void dem_f2(int **dem, int n, int y){  // funcao para criacao da matriz DEM atraves de valores ja pre determinados  no codigo

// cada elemento da matriz recebe um valor qualquer

    dem[0][0]=10;
    dem[0][1]=15;
    dem[0][2]=23;
    dem[0][3]=11;
    dem[0][4]=65;
    dem[0][5]=58;
    dem[0][6]=55;
    dem[0][7]=23;
    dem[0][8]=12;
    
    dem[1][0]=133;
    dem[1][1]=98;
    dem[1][2]=6;
    dem[1][3]=45;
    dem[1][4]=3;
    dem[1][5]=12;
    dem[1][6]=9;
    dem[1][7]=102;
    dem[1][8]=90;
    
    dem[2][0]=18;
    dem[2][1]=56;
    dem[2][2]=3;
    dem[2][3]=40;
    dem[2][4]=8;
    dem[2][5]=207;
    dem[2][6]=255;
    dem[2][7]=7;
    dem[2][8]=25;
    
    dem[3][0]=56;
    dem[3][1]=234;
    dem[3][2]=176;
    dem[3][3]=36;
    dem[3][4]=29;
    dem[3][5]=7;
    dem[3][6]=37;
    dem[3][7]=133;
    dem[3][8]=88;
    
    dem[4][0]=39;
    dem[4][1]=166;
    dem[4][2]=247;
    dem[4][3]=234;
    dem[4][4]=54;
    dem[4][5]=14;
    dem[4][6]=77;
    dem[4][7]=60;
    dem[4][8]=201;
    
    dem[5][0]=189;
    dem[5][1]=2;
    dem[5][2]=200;
    dem[5][3]=14;
    dem[5][4]=150;
    dem[5][5]=6;
    dem[5][6]=20;
    dem[5][7]=39;
    dem[5][8]=200;
    
    dem[6][0]=73;
    dem[6][1]=160;
    dem[6][2]=30;
    dem[6][3]=222;
    dem[6][4]=10;
    dem[6][5]=182;
    dem[6][6]=162;
    dem[6][7]=217;
    dem[6][8]=26;
    
    dem[7][0]=173;
    dem[7][1]=60;
    dem[7][2]=130;
    dem[7][3]=20;
    dem[7][4]=1;
    dem[7][5]=85;
    dem[7][6]=18;
    dem[7][7]=42;
    dem[7][8]=197;
    
    dem[8][0]=3;
    dem[8][1]=18;
    dem[8][2]=50;
    dem[8][3]=22;
    dem[8][4]=100;
    dem[8][5]=132;
    dem[8][6]=70;
    dem[8][7]=240;
    dem[8][8]=9;

} // encerra funcao dem_f2

////////////////////////////////////////////////////////////////////////////////

// arquivo dem ja definido

void dem_f3(FILE *arq2, int **dem, int n, int y) { // funcao para gerar matriz DEM utilizando valores de um arquivo .txt

  for (i=0; i<=n-1; i++) for (j=0; j<=y-1; j++) fscanf(arq2,"%d",&dem[i][j]); // laco para fazer a leitura no arquivo

}
