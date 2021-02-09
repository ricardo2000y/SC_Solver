//#define _CRT_SECURE_NO_DEPRECATE  //uso o IDE Visual Studio 2019
/*It looks like Microsoft has deprecated lots of calls which use buffers to improve code security. However, the solutions they're providing aren't portable. Anyway, if you aren't interested in using the secure version of their calls (like fopen_s), you need to place a definition of _CRT_SECURE_NO_DEPRECATE before your included header files.*/
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
	int zero_solved;
}output;

puzzle matriz_struct;
output solucao;

void ler_ficheiro(char*);
    /* abre ficheiro .prb
     * guarda as informações necessárias ao programa na estrutura puzzle matriz_strcut
        * L, C, SL, SC, zeros totais guardados
     * aloca memoria para a matriz lida segundo as suas linhas e colunas
        * matriz é guardada
     * fecha file.*/
void aviso(char *);
void setup_solucao();
    /*Aloca memoria para uma matriz onde vao ser guardadas
     as solucoes, segundo o numero de zeros totais da matriz problema*/

void printMatriz(); //self-explanatory

void printSol();
    /* imprime as solucoes que já tem resolvidas
     * se nao tiver TODAS as solucoes resolvidas informa o utilizador*/

void verif_zero_alone();
    /*conta os zeros por linha
        * se existirem 0's sozinhos -> resolve
     *conta os zeros por coluna
        * se existirem 0's sozinhos -> resolve
    */
void solve_zero_alone(int,int,int);
    /*soma as linhas/colunas para e subrai a SL/SC para encontrar o 0*/
void save_result(int, int , int );
    /*le a matriz da solução para encontrar a coordenada do zero e guardar o resultado no respetivo sitio*/

int find_gap_value(int, int);
int solve_zero();
int find_next_zero(int*, int*);
int check_valid();
void update_sol();
