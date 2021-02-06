#define _CRT_SECURE_NO_DEPRECATE  //uso o IDE Visual Studio 2019
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
void printSol(output, puzzle);
void aviso(char *);
void printMatriz();
void verif_zero_alone(puzzle);
void solve_zero_alone(int,int,puzzle,int);
void save_result(int, int , int );
void ler_file(int, char*);


