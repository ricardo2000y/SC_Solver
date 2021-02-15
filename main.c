
#include "main.h"

int main(int argc, char *argv[]){

    if (argc < 2) {
        aviso(argv[0]);
        exit(0);
    }

    ler_ficheiro(argv[1]);

    setup_solucao();

    printMatriz();

    verif_zero_alone();

    if(check_valid()){
        update_sol();
        printSol();
        save_to_file(argv[1]);
        free_mem();
        exit(1);
    }else if (!solve_zero()){
        int i=0;
        free(solucao.matriz_sol);
        solucao.matriz_sol = (int**)malloc(sizeof(int*) * 1);
        for(i=0; i<4; i++){
            solucao.matriz_sol[i] = (int*)malloc(sizeof(int) * 3);
        }
	    solucao.matriz_sol[0][0] = 0;
        solucao.matriz_sol[0][1] = 0;
        solucao.matriz_sol[0][2] = 0;
        printSol();
        solucao.zero_solved = 1;
        save_to_file(argv[1]);
        free_mem();
        exit(1);
	}
    update_sol();
    save_to_file(argv[1]);
    free_mem();
	
    return 0;
}
