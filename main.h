#define _CRT_SECURE_NO_DEPRECATE  //uso o IDE Visual Studio 2019
/*It looks like Microsoft has deprecated lots of calls which use buffers to improve code security. However, the solutions they're providing aren't portable. Anyway, if you aren't interested in using the secure version of their calls (like fopen_s), you need to place a definition of _CRT_SECURE_NO_DEPRECATE before your included header files.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//teste
typedef struct {
	int ** matriz;
	int L;
	int C;
	int SL;
	int SC;
}puzzle;

typedef struct{
	int L;
	int C;
	//int value;
}output;

puzzle matriz_struct;
void aviso(char *);
//puzzle ler_ficheiro();
void printMatriz(puzzle);		
void verif_zero_alone(puzzle);
void solve_zero_alone(int,int,puzzle,int);
void save_result(int, int , int );
void ler_file();

