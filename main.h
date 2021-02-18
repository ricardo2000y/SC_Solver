
// falta adicionar descricoes a quase tudo aqui
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int ** matriz;
	int L;
	int C;
	int SL;
	int SC;
	int total_zeros;
}puzzle;

typedef struct{
	int **matriz_sol;
    int L;
	int C;
	int result;
}output;

puzzle matriz_struct;
output solucao;

void ler_ficheiro(char*);
    /* abre ficheiro .prb
     * guarda as informa��es necess�rias ao programa na estrutura puzzle matriz_strcut
        * L, C, SL, SC, zeros totais guardados
     * aloca memoria para a matriz lida segundo as suas linhas e colunas
        * matriz � guardada
     * fecha file.*/
void aviso(char *);
void setup_solucao();
    /*Aloca memoria para uma matriz onde vao ser guardadas
     as solucoes, segundo o numero de zeros totais da matriz problema*/




void verif_zero_alone();
    /*conta os zeros por linha
        * se existirem 0's sozinhos -> resolve
     *conta os zeros por coluna
        * se existirem 0's sozinhos -> resolve
    */
void solve_zero_alone(int,int,int);
    /*soma as linhas/colunas para e subrai a SL/SC para encontrar o 0*/
int alone(int,int);
int find_gap_value(int, int);
int solve_zero();
int find_next_zero(int*, int*);
int check_valid();
void update_sol();/*le a matriz da solucao para encontrar a coordenada do zero e guardar o resultado no respetivo sitio*/
void free_mem();
void save_to_file(char *);


void not_solvable();
