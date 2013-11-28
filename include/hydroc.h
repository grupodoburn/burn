//Biblioteca HydroC - operacao de objetos hidrologicos via codigos C/C++
//Primeira versao: 15/03/13
//Ultima atualizacao: 25/06/13
                  
                  
//variaveis globais
int i, j; //indexadores do espaco bidimensional - i para linhas, j para colunas
int tambacia;
       
//inclusao de codigos da biblioteca, um para cada conjunto de funcoes relativas ao mesmo objeto hidrologico
#include "hydroc\dem.h" // biblioteca para utilizar a funcao dem
#include "hydroc\ldd.h" // biblioteca para utilizar a funcao ldd
#include "hydroc\aa.h"  // biblioteca para utilizar a funcao aa
#include "hydroc\dng.h" // biblioteca para utilizar a funcao dng
#include "hydroc\bacia.h" // biblioteca para utilizar a funcao bacia

//inclusao de codigos da biblioteca, um para cada conjunto de funcoes relativas ao mesmo objeto hidrologico
#include "hydroc\imprimir_tela.h"  // biblioteca utilizada para imprimir codigo na tela
#include "hydroc\imprimir_arq.h"   // biblioteca utilizada para imprimir codigo no arquivo
