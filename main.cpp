#include <iostream>
#include "ClosureMap.h"
#include <stdlib.h>

commandLineArgs CL;

int main(int argc, char* argv[]){

    CL.numArgs = argc;


    if (argc > 3){
        cout << "Incorrect number of command line arguments.  The options are: " << endl;
        cout << "1.  Zero command line arguments -- user will enter all data and output will be printed to terminal." << endl;
        cout << "2.  One command line argument -- user enters input filename and output will be printed to terminal." << endl;
        cout << "3.  Three command line arguments -- user enters input filename and output filepath and output will be printed \n";
        cout << "\tto both the terminal and to the file path that is entered.\n";
        exit(99);
    }


    if (argc == 2){
        string *temp3 = new string(argv[1]);
        CL.inputFilePath = *temp3;
    }

    cout << CL.inputFilePath << endl;


    if (argc == 3){
        string* temp = new string(argv[1]);
        CL.inputFilePath = *temp;
        string *temp1 = new string(argv[2]);
        CL.outFilePath = *temp1;
    }

    ClosureMap closMap(argc);
    closMap.print_init_FD_Array();
    closMap.print_R();
    closMap.generate_all_subsets_of_R_and_closures();
    closMap.print_all_subsets_of_R();
    closMap.print_all_subset_closure_pairs();
    closMap.generate_superkey_list();
    closMap.print_superkeys();
    closMap.remove_extra_sks_and_gen_cand_key_list();
    closMap.print_candidate_keys();
    if (argc==2){
        closMap.write_candidate_keys_to_file();
    }

    return 0;
}
