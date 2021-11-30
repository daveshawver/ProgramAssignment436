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
        void generate_all_subsets_of_R();
        void read_from_file();
        void print_all_subsets_of_R();
        void printClosureMap();
        void print_R();
        ClosureMap(int choice);
};
