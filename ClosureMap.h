#include <vector>
#include <set>
#include <utility>
#include <string>
#include <iostream>

using namespace std;

typedef struct commandLineArgs{
    int numArgs;
    string outFilePath;
    string inputFilePath;
} commandLineArgs;



typedef struct FD{

    set<string> LHS;
    set<string> RHS;

} FD;

class ClosureMap {
    private: int numAttributes, numFDs;

    public:
        vector<string*> R;
        set<string> R_as_Set;
        vector<FD*> FDArray;
        vector<pair<set<string>, set<string>>> R_Subset_Closure_Pairs;
        vector<set<string>> all_Subsets_of_R;
        vector<set<string>> superKeys;
        vector<set<string>> candidateKeys;
        
        void generate_all_subsets_of_R_and_closures();
        set<string> computeClosure(const set<string>* inputSubset);
        void generate_superkey_list();
        void remove_extra_sks_and_gen_cand_key_list();

        void read_from_file();
        void print_candidate_keys();
        void print_all_subsets_of_R();
        void print_init_FD_Array();
        void print_R();
        void print_superkeys();
        void print_all_subset_closure_pairs();
        void write_candidate_keys_to_file();

        ClosureMap(int choice);
};