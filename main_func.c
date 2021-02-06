#include "main.h"

void printMatriz(puzzle matriz_struct) {
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
	//ver linha a linha:
	int zero_location,j,i,alone_z_counter;
	int z_counter = 0;
	int funcao_solve_zero_alone = 1;
	int lock = 0;
	int total_zero_counter=0;
	//L,C = i,j
	//na linha 0, quero avançar de coluna a coluna à procura de 0's, se n encontrar ent incrementa a linha
	do{	
		alone_z_counter = 0;
	 	//a correr por coluna
		for (i = 0; i < matriz_struct.L; i++, z_counter = 0) {
			for (j = 0; j < matriz_struct.C;j++) {
				if (matriz_struct.matriz[i][j] == 0) { //se igual a 0 incrementa
					z_counter++;
					zero_location = j; //j = index da coluna
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
		printf("\nLEITURA POR LINHA REALIZADA");
		printMatriz(matriz_struct);

		for (j = 0; j < matriz_struct.C; j++, z_counter = 0) {
			for (i = 0; i < matriz_struct.L;i++) {
				if (matriz_struct.matriz[i][j] == 0){
					z_counter++;
					zero_location = i;
				}
				//se estivermos na ultima posi��o da coluna, e s� houver 1 zero, ent�o chamamos a fun��o q resolve
				if (i == (matriz_struct.L - 1) && z_counter == 1){
					solve_zero_alone(zero_location, j, matriz_struct, 1);
					alone_z_counter++;
				
				}
			}
	}

	printf("\nLEITURA POR COLUNA REALIZADA");
	printMatriz(matriz_struct);
	} while (alone_z_counter!=0 );

}


void aviso(char *prog){
    fprintf(stdout, "aviso:deve inserir %s nome_de_ficheiro e nao apenas %s\n", prog, prog);
    return;
}

void solve_zero_alone(int i, int j, puzzle matriz_struct, int tipo_de_varramento) {

    int somaLinha = 0, somaColuna = 0, sol_linha = 0, sol_coluna = 0;

	int x;
	
	if (tipo_de_varramento == 0 /*leitura por linha*/) {
		for (x = 0; x < matriz_struct.C; x++) {
			somaLinha = somaLinha + matriz_struct.matriz[i][x];
		}
		sol_linha = matriz_struct.SL - somaLinha;
		matriz_struct.matriz[i][j] = sol_linha;
		//save_result(i , j , sol_linha , *output_file);
	}
	else if (tipo_de_varramento) {
		for (x = 0; x < matriz_struct.L; x++) {
			somaColuna = somaColuna + matriz_struct.matriz[x][j];
		}
		sol_coluna = matriz_struct.SC - somaColuna;
		matriz_struct.matriz[i][j] = sol_coluna;
		//save_result(i , j , sol_coluna , *output_file);
	}
}

void save_result(int i, int j,int total_zeros){// efetiamente ainda nao az nada
	output output_file[total_zeros]; // rever e pode ser feito com malloc ppbly
	
	static int k=0;
	output_file[k].C =i;
	output_file[k].L =j;
	k++;
/*	if (k== total_zeros){
		organiza esta porra e imprime tamb�m existe a alternativa de guardar por ordem autom�ticamente
		... ou seja usar a fun��o que corre por o file � procura de zeros para dar as coordenadas dos mesmos
		possivelmente ut�l mas precisa de ser feito com aten��o(provavelmente elimina a necessidade da variavel q conta o total)

	}*/
}

