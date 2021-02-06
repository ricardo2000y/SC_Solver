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

    fclose(fPointer);
}

void setup_solucao(){
    int total_zero_counter=0, i,j;
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

void verif_zero_alone(puzzle matriz_struct) {

    int zero_location,j,i,alone_z_counter, z_counter=0,total_zero_counter=0,lock = 0;

	//--DESCRIÇÃO DAS VARIAVEIS--
	// zero_location: vai guardar as "coordenadas" do 0 [i][j]
	// alone_z_counter: incrementa se existirem 0's sozinhos
	// z_counter: serve para contar o nr de 0's de uma coluna ou linha

	// total_zero_counter: NAO SEI O Q FAZ
	// lock: NAO SEI O Q FAZ

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
					solve_zero_alone(i, zero_location, matriz_struct, 0);
					alone_z_counter++;
				}
			 	if (lock == 0)	{
			 		total_zero_counter += 	z_counter;
				 	if(i == matriz_struct.L-1) lock = 1;
				}
			}

		}//LEITURA POR LINHA REALIZADA
		//printf("\nLEITURA POR LINHA REALIZADA");
		//printMatriz(matriz_struct);

		for (j = 0; j < matriz_struct.C; j++, z_counter = 0) { //correr por coluna
			for (i = 0; i < matriz_struct.L;i++) {
				if (matriz_struct.matriz[i][j] == 0){   //se igual a 0 incrementa
					z_counter++;
					zero_location = i;
				}
				//se estivermos na ultima posicao da coluna, e so houver 1 zero, entao chamamos a funcao q resolve
				if (i == (matriz_struct.L - 1) && z_counter == 1){
					solve_zero_alone(zero_location, j, matriz_struct, 1);
					alone_z_counter++;
				
				}
			}
	}

	//printf("\nLEITURA POR COLUNA REALIZADA");
	//printMatriz(matriz_struct);
	} while (alone_z_counter!=0 );

}

void solve_zero_alone(int i, int j, puzzle matriz_struct, int tipo_de_varramento) {

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
    static int times_called = 0;
   // printf("\nSave Chamado, times called = %d, L= %d, C= %d, sol= %d", times_called+1, L,C, sol);
    solucao.matriz_sol[times_called][0]=L+1;
    solucao.matriz_sol[times_called][1]=C+1;
    solucao.matriz_sol[times_called][2]=sol;
    //printf("\nsolucao.matriz_sol[times_called][0]=%d\nsolucao.matriz_sol[times_called][1]=%d\nsolucao.matriz_sol[times_called][2]=%d",solucao.matriz_sol[times_called][0],solucao.matriz_sol[times_called][1],solucao.matriz_sol[times_called][2]);
    times_called++;
    solucao.zero_solved++;

}

void printSol(output solucao,puzzle matriz_struct) {
    int i, j, print_until;
    printf("\n");
    if (solucao.zero_solved != matriz_struct.total_zeros){
        print_until = solucao.zero_solved;
        printf("\nSolucao incompleta, ainda há zeros por resolver. Foram resolvidos %d zeros de %d.\n", solucao.zero_solved, matriz_struct.total_zeros);
    }else{
        print_until= matriz_struct.total_zeros;
        printf("\nTodos os zeros encontrados.SOLUCAO:\n");
    }

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

