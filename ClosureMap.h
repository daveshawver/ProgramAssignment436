#include <vector>
#include <set>
#include <utility>
#include <string>
#include <iostream>

using namespace std;

typedef struct FD{

    set<string> LHS;
    set<string> RHS;

} FD;

class ClosureMap {
    private: int numAttributes, numFDs;

    public:
        vector<string*> R;
        vector<FD*> FDArray;
        vector<pair<set<string>, set<string>>> R_Subset_Closure_Pairs;
        vector<set<string>> all_Subsets_of_R;
        void generate_all_subsets_of_R_and_closures();
        void read_from_file();
        void print_all_subsets_of_R();
        void print_init_FD_Array();
        void print_R();
        set<string> computeClosure(const set<string>* inputSubset);
        void print_all_subset_closure_pairs();
        ClosureMap(int choice);
};