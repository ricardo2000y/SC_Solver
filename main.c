
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
        exit(1);
    }else if (!solve_zero()){


	    solucao.matriz_sol[0][0] = 0;
        solucao.matriz_sol[0][1] = 0;
        solucao.matriz_sol[0][2] = 0;
	};
	
	update_sol();

	printSol();


    //funcao da arvore tro�o q vai resolver os outros 0's :D();
    //sort_sol();
    //guardar_file_sol();
    return 0;
}
