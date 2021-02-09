
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
    
	solve_zero();
	
	update_sol();

	printSol();
 
    //funcao da arvore tro�o q vai resolver os outros 0's :D();
    //sort_sol();
    //guardar_file_sol();
    return 0;
}
