#include "main.h"

void ler_ficheiro(char *prog){
    FILE *fPointer;
    int i,j, **matrix, total_zero_counter =0;

    /* open file and read array size */
    fPointer = (FILE *) fopen(prog, "r");
    if (fPointer == (FILE *) NULL) {
        fprintf(stderr, "O ficheiro %s nao pode ser lido ou nao existe.  Tente novamente.\n", prog);
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
    for ( i = 0; i < matriz_struct.L;i++) {
        for ( j = 0; j < matriz_struct.C; j++) {
            fscanf(fPointer, "%s", fileInfo);
            matriz_struct.matriz[i][j] = atoi(fileInfo);
        }
    }

    for (i = 0; i < matriz_struct.L; i++) {
        for (j = 0; j < matriz_struct.C;j++) {
            if(matriz_struct.matriz[i][j]==0) total_zero_counter++;
        }
    }
    matriz_struct.total_zeros=total_zero_counter;

    fclose(fPointer);
}

void setup_solucao(){
    int x = 0, i, j;
        //ALOCAR MEMORIA PARA A ESTRUTURA DA SOLUÇÃO - 3 COLUNAS , NR DE LINHAS = 0'S TOTAIS
        solucao.matriz_sol = (int**)malloc(sizeof(int*) * matriz_struct.total_zeros); // alocar L linhas
        for (i = 0;i < matriz_struct.total_zeros;i++) {
            solucao.matriz_sol[i] = (int*)malloc(sizeof(int) * 3); //alocar 3 colunas para cada linha (L) [L][C][sol]
        }

    for (i = 0;i < matriz_struct.L;i++) {
        for (j = 0;j < matriz_struct.C;j++) {
            if(matriz_struct.matriz[i][j] == 0){
                solucao.matriz_sol[x][0] = i+1;
                solucao.matriz_sol[x][1] = j+1;
                solucao.matriz_sol[x][2] = 0;
                x++;
            }
        }
    }

}

void printMatriz() {
	int i, j;
	printf("\n");
	for (i = 0;i < matriz_struct.L;i++) {
		for (j = 0;j < matriz_struct.C;j++) {
			printf("%d\t", matriz_struct.matriz[i][j]);
		}
		printf("\n");
	}
}

void verif_zero_alone() {

    int zero_location,j,i,alone_z_counter, z_counter=0,total_zero_counter=0,lock = 0;
	//--DESCRIÇÃO DAS VARIAVEIS--
	// zero_location: vai guardar as "coordenadas" do 0 [i][j]
	// alone_z_counter: incrementa se existirem 0's sozinhos
	// z_counter: serve para contar o nr de 0's de uma coluna ou linha
	//L,C = i,j

    //na linha 0, quero avançar de coluna a coluna à procura de 0's, se n encontrar ent incrementa a linha
	do{	
		alone_z_counter = 0;
	 	//a correr a linha
		for (i = 0; i < matriz_struct.L; i++, z_counter = 0) {
			for (j = 0; j < matriz_struct.C;j++) {
				if (matriz_struct.matriz[i][j] == 0) {
					z_counter++;        //se X na posição [i][j]=0 incrementa
					zero_location = j;  //posição do 0 => [i][zero_location]
				}
				if (j == (matriz_struct.C - 1) && z_counter == 1){//se chegar ao fim da linha e existir apenas um 0
                                                                  //chama a função q resolve o 0 sozinho
					solve_zero_alone(i, zero_location,0);
					alone_z_counter++;
				}
			 	if (lock == 0)	{
			 		total_zero_counter += 	z_counter;
				 	if(i == matriz_struct.L-1) lock = 1;
				}
			}
		}
		//a correr a coluna
		for (j = 0; j < matriz_struct.C; j++, z_counter = 0) { //correr por coluna
			for (i = 0; i < matriz_struct.L;i++) {
				if (matriz_struct.matriz[i][j] == 0){   //se igual a 0 incrementa
					z_counter++;
					zero_location = i;
				}
				//se estivermos na ultima posicao da coluna, e so houver 1 zero, entao chamamos a funcao q resolve
				if (i == (matriz_struct.L - 1) && z_counter == 1){
					solve_zero_alone(zero_location, j, 1);
					alone_z_counter++;
				}
			}
	}
	} while (alone_z_counter!=0 );
}

void solve_zero_alone(int i, int j, int tipo_de_varramento) {

    int somaLinha = 0, somaColuna = 0, sol_linha = 0, sol_coluna = 0,x;

	
	if (tipo_de_varramento == 0 /*leitura por linha*/) {
		for (x = 0; x < matriz_struct.C; x++) {
			somaLinha = somaLinha + matriz_struct.matriz[i][x];
		}
		sol_linha = matriz_struct.SL - somaLinha;
		matriz_struct.matriz[i][j] = sol_linha;
		save_result(i , j , sol_linha);

	}
	else if (tipo_de_varramento == 1 /*leitura por coluna*/) {
		for (x = 0; x < matriz_struct.L; x++) {
			somaColuna = somaColuna + matriz_struct.matriz[x][j];
		}
		sol_coluna = matriz_struct.SC - somaColuna;
		matriz_struct.matriz[i][j] = sol_coluna;
        save_result(i , j , sol_coluna);

	}
}

void save_result(int L, int C, int sol){
   for (int i=0; i<matriz_struct.total_zeros; i++){
       if(solucao.matriz_sol[i][0]==L+1 && solucao.matriz_sol[i][1] == C+1) solucao.matriz_sol[i][2]=sol;
   }
}

void printSol() {
    int i, j, print_until;
    printf("\n");
    print_until= matriz_struct.total_zeros;
    for (i = 0;i < print_until;i++) {
        for (j = 0;j < 3;j++) {
            printf("%d\t", solucao.matriz_sol[i][j]);
        }
        printf("\n");
    }
}

void aviso(char *prog){
    fprintf(stdout, "aviso:deve inserir %s nome_de_ficheiro e nao apenas %s\n", prog, prog);
    return;
}
/*//----------------------------------------------------------------------------------------------------
int valid(int[][9], int, int, int);
int solve(int[][9]);
int find_empty_cell(int[][9], int *, int *);

int main() {
    int puzzle[9][9] = {{1, 7, 4, 0, 9, 0, 6, 0, 0},
                        {0, 0, 0, 0, 3, 8, 1, 5, 7},
                        {5, 3, 0, 7, 0, 1, 0, 0, 4},
                        {0, 0, 7, 3, 4, 9, 8, 0, 0},
                        {8, 4, 0, 5, 0, 0, 3, 6, 0},
                        {3, 0, 5, 0, 0, 6, 4, 7, 0},
                        {2, 8, 6, 9, 0, 0, 0, 0, 1},
                        {0, 0, 0, 6, 2, 7, 0, 3, 8},
                        {0, 5, 3, 0, 8, 0, 0, 9, 6}};
    int row = 0;
    int column = 0;

    if (solve(puzzle)) {
        printf("\n+-----+-----+-----+\n");
        for (int x = 0; x < 9; ++x) {
            for (int y = 0; y < 9; ++y) printf("|%d", puzzle[x][y]);
            printf("|\n");
            if (x % 3 == 2) printf("\n+-----+-----+-----+\n");
        }
    }
    else {
        printf("\n\nNO SOLUTION FOUND\n\n");
    }

    return 0;
}
int valid(){

}

int solve_zero() {
    // L,C vem das matriz das solucoes
    int L,C, max_gap;
    // condicao que verifica se ja estamos na ultima posicao e
    // somas constantes estão verificadas

    max_gap = find_gap_value(L,C);

    for (int guess = 1; guess <= max_gap ; guess++) {
        matriz_struct.matriz[L][C] = guess;
        // ? verif zero alone
        if(solve_zero(puzzle) && valid()) {

            return 1;
        }
        puzzle[L][C] = 0;

    }
    return 0;
}
//----------------------------------------------------------------------------------------------------*/


int find_gap_value( int L, int C){/*recebe a as coordenadas do zero */
    int x, somaLinha = -1, somaColuna = -1; // -1 para não ser contado o 0 que estamos a resolver

    for (x = 0; x < matriz_struct.C; x++) {
        if (matriz_struct.matriz[L][x]==0) somaLinha++; //por cada 0 que encontra incrementa somaLinha por 1
                                                        //pq o valor minimo de qualquer 0 (pos resolucao) é 1
        somaLinha += matriz_struct.matriz[L][x];
    }
    for (x = 0; x < matriz_struct.L; x++) {
        if (matriz_struct.matriz[x][C]==0) somaColuna++;
        somaColuna += matriz_struct.matriz[x][C];
    }

    somaLinha = matriz_struct.SL - somaLinha;
    somaColuna = matriz_struct.SC - somaColuna;
    if (somaLinha < somaColuna ) return somaLinha ;  // retorna o menor entre os valores máximos linha/coluna
    else return somaColuna;
}