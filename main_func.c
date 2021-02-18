#include "main.h"
// falta defenir a condi��o de problema imposssivel output deve ser apenas uma linha com 3 0 espa�ados
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
        //ALOCAR MEMORIA PARA A ESTRUTURA DA SOLU��O - 3 COLUNAS , NR DE LINHAS = 0'S TOTAIS
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

void printMatriz() {// apagar antes de entregar 
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

    int zero_location,j,i,alone_z_counter, z_counter=0,total_zero_counter=0;
	//--DESCRI��O DAS VARIAVEIS--
	// zero_location: vai guardar as "coordenadas" do 0 [i][j]
	// alone_z_counter: incrementa se existirem 0's sozinhos
	// z_counter: serve para contar o nr de 0's de uma coluna ou linha
	//L,C = i,j

    //na linha 0, quero avan�ar de coluna a coluna � procura de 0's, se n encontrar ent incrementa a linha
	do{
		alone_z_counter = 0;
	 	//a correr a linha
		for (i = 0; i < matriz_struct.L; i++, z_counter = 0) {
			for (j = 0; j < matriz_struct.C;j++) {
				if (matriz_struct.matriz[i][j] == 0) {
					z_counter++;        //se X na posi��o [i][j]=0 incrementa
					zero_location = j;  //posi��o do 0 => [i][zero_location]
				}
				if (j == (matriz_struct.C - 1) && z_counter == 1){//se chegar ao fim da linha e existir apenas um 0
                                                                  //chama a fun��o q resolve o 0 sozinho
					solve_zero_alone(i, zero_location,0);
					alone_z_counter++;
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

	}
	else if (tipo_de_varramento == 1 /*leitura por coluna*/) {
		for (x = 0; x < matriz_struct.L; x++) {
			somaColuna = somaColuna + matriz_struct.matriz[x][j];
		}
		sol_coluna = matriz_struct.SC - somaColuna;
		matriz_struct.matriz[i][j] = sol_coluna;
	}
}


void printSol() {// apagar antes de enviar
    int i, j, print_until;
    printf("\n");
    if(solucao.matriz_sol[0][0] == 0 && solucao.matriz_sol[0][1] == 0 && solucao.matriz_sol[0][2] == 0){
        print_until=1;
    }else print_until= matriz_struct.total_zeros;
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

int find_next_zero(int* L , int* C){
	int i,j;
	for (i = 0; i < matriz_struct.L; i++) {
			for (j = 0; j < matriz_struct.C;j++) {
				if (matriz_struct.matriz[i][j] == 0){
					*L = i;
					*C = j;
					return 1;
					}
				}
				
			}
	return 0;
}

int check_valid(){
	int L=0,C=0 ,check_soma_coluna = 0;
    for (C = 0 ; C < matriz_struct.C ; C++){
        check_soma_coluna = 0;
        for (L = 0 ; L < matriz_struct.L; L++){
            check_soma_coluna  += matriz_struct.matriz[L][C] ;

        }

        if(check_soma_coluna != matriz_struct.SC) return 0;
    }
	/*for (L = 0 ; L < matriz_struct.L ; L++){
	    check_soma_linha = 0;
		for (C = 0 ; C < matriz_struct.C; C++){
            check_soma_linha += matriz_struct.matriz[L][C];
			}
			if(check_soma_linha != matriz_struct.SL) return 0;
		}*/
    //printMatriz();//-----------------------------------------apagar antes de enviar
    return 1;
}

int valid_value(int L, int C){
	
    int check_soma_linha = 0 ,check_soma_coluna = 0, x;
	printf("i made it");
	 
		for (x = 0; x < matriz_struct.C; x++) {
			check_soma_linha +=  matriz_struct.matriz[L][x];
		}
		printf("%d    %d",check_soma_linha, matriz_struct.SL);
		if(check_soma_linha != matriz_struct.SL) return 0;
	printf("i made it 2");	
		for (x = 0; x < matriz_struct.L; x++) {
			check_soma_coluna +=  matriz_struct.matriz[x][C];
		}
		if(check_soma_coluna != matriz_struct.SC) return 0;
	printf("i made it 3");

	return 1;
}

int alone(int L, int C){
	int x, zero_counter=0;
	for (x = 0; x < matriz_struct.C; x++) {
			if(  matriz_struct.matriz[L][x]==0) zero_counter++;
		}
		if (zero_counter == 1) {
			return 1;
			}
	zero_counter=0;
	for (x = 0; x < matriz_struct.L; x++) {
			if(  matriz_struct.matriz[x][C]==0) zero_counter++;
		}
	if (zero_counter == 1){
		return 1;
		}
	return 0;
}

int solve_zero() {
    // L,C vem das matriz das solucoes
    int L,C, max_gap=0,x,guess;
    // condicao que verifica se ja estamos na ultima posicao e
    // somas constantes est�o verificadas
    //printMatriz();
	if (find_next_zero(&L, &C)){
		max_gap = find_gap_value(L,C);
		
	}
	else if(check_valid())return 1;
		
	else return 0;

		for  (guess = 1; guess <= max_gap ; ) {
			
			if(alone(L,C)) guess = max_gap;
			matriz_struct.matriz[L][C] = guess;
			++guess;
			//if(!valid_value(L,C);	 tenho q arranjar maneira de meter esta treta algures -
			if (solve_zero()) return 1;
				
			matriz_struct.matriz[L][C] = 0;
		    }

    return 0;
}

void update_sol(){
	int i, L ,C;
    for ( i=0; i < matriz_struct.total_zeros; i++){
       if(solucao.matriz_sol[i][2]==0 ) {
       		L = solucao.matriz_sol[i][0]-1;
       		C = solucao.matriz_sol[i][1]-1;
       		solucao.matriz_sol[i][2] = matriz_struct.matriz[L][C];
	  	 }
       
   }

}

int find_gap_value( int L, int C){/*recebe a as coordenadas do zero */
    int x, somaLinha = -1, somaColuna = -1; // -1 para nao ser contado o 0 que estamos a resolver

    for (x = 0; x < matriz_struct.C; x++) {
        if (matriz_struct.matriz[L][x]==0) somaLinha++; //por cada 0 que encontra incrementa somaLinha por 1
                                                        //pq o valor minimo de qualquer 0 (pos resolucao) = 1
        somaLinha += matriz_struct.matriz[L][x];
    }
    for (x = 0; x < matriz_struct.L; x++) {
        if (matriz_struct.matriz[x][C]==0) somaColuna++;
        somaColuna += matriz_struct.matriz[x][C];
    }

    somaLinha = matriz_struct.SL - somaLinha;
    somaColuna = matriz_struct.SC - somaColuna;
    if (somaLinha < somaColuna ) return somaLinha ;  // retorna o menor entre os valores maximos linha/coluna
    else return somaColuna;
}

void free_mem(){
    printf("\nFree da memoria");
    free(matriz_struct.matriz);
    free(solucao.matriz_sol);
}

void save_to_file (char *prog){
    printf("\n IM IN SAVE TO FILE");
    int i, j, print_until;
    FILE *fp;
    int len = strlen(prog)-3;
    char dest[len+3];
    char sol[] = "sol";

    if(solucao.matriz_sol[0][0] == 0 && solucao.matriz_sol[0][1] == 0 && solucao.matriz_sol[0][2] == 0){
        print_until=1;
    }else print_until= matriz_struct.total_zeros;

    strncpy(dest, prog,len);
    strcat(dest, sol);
    fp = fopen(dest, "w");
    printf("\n%s", dest);
    if(fp == NULL)
    {
        printf("\nError!");
        exit(1);
    }
    for(i=0; i<print_until; i++){
        for(j=0; j<3; j++){
            fprintf(fp,"%d ",solucao.matriz_sol[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}


