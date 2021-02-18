
/* falta adicionar descricoes a quase tudo aqui*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {/*  estrutura com dados do problema */
	int ** matriz;/*matriz(array de arrays) que é prenchido com os valores do .pbr*/
	int L;
	int C;
	int SL;
	int SC;
	int total_zeros;/* usado para fazer a estrutura da solucao e para guardar a mesma no ficheiro*/
}puzzle;


int **matriz_sol;/*matriz(array de arrays) que e prenchido com a coordenada do zero resolvido e o seu valor*/
   


puzzle matriz_struct;


void ler_ficheiro(char*);
    /* abre ficheiro .prb
     * guarda as informacoes necessarias ao programa na estrutura puzzle matriz_strcut
        * L, C, SL, SC, zeros totais guardados
     * aloca memoria para a matriz lida segundo as suas linhas e colunas
        * matriz e guardada
     * fecha file.*/
void aviso(char *);/* avisa caso o utilizador utilize um ficheiro incorreto, inexistente ou nem utilizee nenhum como argumento*/
void setup_solucao();
    /*Aloca memoria para uma matriz onde vao ser guardadas
     as solucoes, segundo o numero de zeros totais da matriz problema*/
void check_if_empty(); /*se a matriz estiver completamente vazia preenche com o valor medio*/
void verif_zero_alone();
    /*conta os zeros por linha
        * se existirem 0's sozinhos -> resolve(chama solve_zero_alone)
     *conta os zeros por coluna
        * se existirem 0's sozinhos -> resolve
    */
void not_solvable();/* caso o problema seja impossivel escreve "0 0 0" no ficheiro solucao a ser impresso*/ 
void solve_zero_alone(int,int,int);
    /*soma as linhas/colunas para e subrai a SL/SC para encontrar o 0*/
int alone(int,int);/*verifica se um 0 esta sozinho dadas as coordenadas do mesmo returna 1 se sozinho e 0 caso contrario*/
int find_gap_value(int, int);/*determina o valor maximo a ser inserido numa posicao da matriz garantindo que a mesma mantenha a condicao de Somas constantes*/
int solve_zero(); /*funcao recursiva que retorna 1 se o problema for resolvido e zero se nao tiver solucao
	para obter a solucao utiliza varias funcoes para determinar o proximo zero(find_next_zero) :
		 caso nao exista : verifica se a matriz atual e valida, caso nao seja retorna 0 (volta atras a menos que ja tenha tentado todas as solucoes possiveis)
		 caso exista : calcula o valor maximo que pode ser inserido na coordenada da matriz(max_gap=find_gap_value(L,C)) 
						entra num ciclo de guess= 1 ate guess = max_gap  onde verifica se o zero esta sozinho(alone();)
							caso esteja : guess = max_gap 
						coloca guess na posicao do zero a resolver
						repete ate estar resolvido onde retorna 1;
	caso nao seja resolvido retorna 0;
*/
int find_next_zero(int*, int*);/*percore a matriz ate encontrar um zero e devolve a sua posicao atraves de apontadores retorna 0 caso nao existam mais zeros*/
int check_valid();/* verifica a validade do problema correndo a matriz coluna a coluna (linha a linha e garantida a validade durante o o calculo do valor a ser inserido nos zeros)*/
void update_sol();/*le a matriz da solucao para encontrar a coordenada do zero e guardar o resultado no respetivo sitio*/
void free_mem();/*liberta a memoria alocada*/
void save_to_file(char *);/* guarda o resultado num ficheiro do tipo "nome_problema.sol" (para um "nome_problema.pbr" resolvido  imprimindo a estrutura de dados da solucao*/

