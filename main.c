#include "main.h"

int main(int argc, char *argv[]){
    int i,j, **matrix, total_zero_counter =0;
    FILE *fPointer;

    /* informa o utilizador que tem que escolher o ficheiro a processar */
    if (argc < 2) {
        aviso(argv[0]);
        exit(0);
    }

    /* open file and read array size */
    fPointer = (FILE *) fopen(argv[1], "r");
    if (fPointer == (FILE *) NULL) {
        fprintf(stderr, "O ficheiro %s nao pode ser lido ou nao existe.  Tente novamente.\n", argv[1]);
        exit(0);
    }
    char fileInfo[150];

    //atoi -> The C library function int atoi(const char *str) converts the string argument str to an integer (type int).
    fscanf(fPointer, "%s", fileInfo);
    matriz_struct.L  = atoi(fileInfo);
    fscanf(fPointer, "%s", fileInfo);
    matriz_struct.C = atoi(fileInfo);
    fscanf(fPointer, "%s", fileInfo);
    matriz_struct.SL = atoi(fileInfo);
    fscanf(fPointer, "%s", fileInfo);
    matriz_struct.SC = atoi(fileInfo);

   	matriz_struct.matriz = (int**)malloc(sizeof(int*) * matriz_struct.L); // alocar L linhas
	for (i = 0;i < matriz_struct.L;i++) {
		matriz_struct.matriz[i] = (int*)malloc(sizeof(int) * matriz_struct.C); //alocar C colunas para cada linha (L)
	}

	printf("L = %d\nC = %d\nSL= %d\nSC = %d\n", matriz_struct.L, matriz_struct.C, matriz_struct.SL, matriz_struct.SC);
	//ciclo q mete o q l� no file para o array de arrays matrix[L][C]
	for ( i = 0; i < matriz_struct.L;i++) {
		for ( j = 0; j < matriz_struct.C; j++) {
			fscanf(fPointer, "%s", fileInfo);
			matriz_struct.matriz[i][j] = atoi(fileInfo);
		}
	}
    //teste
    fclose(fPointer);

    for (i = 0; i < matriz_struct.L; i++) {
        for (j = 0; j < matriz_struct.C;j++) {
            if(matriz_struct.matriz[i][j]==0) total_zero_counter++;
        }
    }
    matriz_struct.total_zeros=total_zero_counter;
    //ALOCAR MEMORIA PARA A ESTRUTURA DA SOLUÇÃO - 3 COLUNAS , NR DE LINHAS = 0'S TOTAIS
    int ** matriz_sol;
    solucao.matriz_sol = (int**)malloc(sizeof(int*) * matriz_struct.total_zeros); // alocar L linhas
    for (i = 0;i < matriz_struct.total_zeros;i++) {
        solucao.matriz_sol[i] = (int*)malloc(sizeof(int) * 3); //alocar 3 colunas para cada linha (L) [L][C][sol]
    }
    printMatriz();
    verif_zero_alone(matriz_struct);
    printSol(solucao, matriz_struct);
    //guardar_file_sol();

    return 0;
}
