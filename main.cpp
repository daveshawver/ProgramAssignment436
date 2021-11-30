#include <iostream>
#include "ClosureMap.h"
#include <stdlib.h>

int main(int argc, char* argv[]){

    if (argc != 2){
        cout << " must make a valid choice!! (0 for user input or 1 for read from file)" << endl;
        exit(99);
    }

    ClosureMap closMap(atoi(argv[1]));
    closMap.printClosureMap();
    closMap.print_R();
    closMap.generate_all_subsets_of_R();
    closMap.print_all_subsets_of_R();

    return 0;
}

