
#include "main.h"
#include <sys/time.h>
int main(int argc, char *argv[]){
    if (argc < 2) {
        aviso(argv[0]);
        exit(0);
    }

    ler_ficheiro(argv[1]);
    setup_solucao();
    check_if_empty();
    verif_zero_alone();

   if (!solve_zero())not_solvable();
   else update_sol();
	
    save_to_file(argv[1]);
    free_mem();
    	
    return 0;
}
