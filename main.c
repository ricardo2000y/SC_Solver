#include "main.h"

int main(int argc, char *argv[]){
    int i,j, **matrix, total_zero_counter =0;

    if (argc < 2) {
        aviso(argv[0]);
        exit(0);
    }

    ler_ficheiro(argv[1]);

    setup_solucao();

    printMatriz();

    verif_zero_alone();

    printSol();

    //funcao da arvore troço q vai resolver os outros 0's :D();
    //sort_sol();
    //guardar_file_sol();
    return 0;
}
