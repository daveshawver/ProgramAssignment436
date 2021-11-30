#include "ClosureMap.h"
#include <cstring>
#include <sstream>
#include <cmath>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

void ClosureMap::read_from_file(){

    ifstream input_stream("example.txt");    

    if (input_stream.fail()){
        cout << "there was a problem opening the file\n" << endl;
        exit(99);
    }
    
    cout << "reading from file" << endl;

    input_stream >> numAttributes >> numFDs;

    cout << "num attributes is " << numAttributes << endl;
    cout << "numFDs is " << numFDs << endl;

    // eat the newline
    input_stream.seekg (1, ios::cur);

    string temp4;

    getline(input_stream, temp4);
    
    stringstream ss (temp4);

    string *temp;
    for (int i = 0; i < numAttributes; i++){
        temp = new string();
        getline(ss, *temp, ' ');
        cout << "R attribute " << i+1 << "is: " << *temp << endl;
        R.push_back(temp);
    }



    for (int i = 0; i < R.size(); i++){
        R_as_Set.insert(*R[i]);
        // cout << *R[i] << ", ";
    }

    for (auto it = R_as_Set.begin(); it != R_as_Set.end(); it++){
        cout << *it << ", ";
    }


    FD* FDTemp;

    for (int i = 0; i < numFDs; i++){
        
        FDTemp = new FD();

        temp = new string();
        // get next line
        getline(input_stream, *temp);

        int posOfArrow = temp->find("->");

        string temp2 = temp->substr(0, posOfArrow);
        cout << "temp2 = " << temp2 << endl;

        stringstream lineEnteredStream(temp2);

        string token;

        while(getline(lineEnteredStream, token,' ')){
            FDTemp->LHS.insert(*(new string(token)));
        }

        string temp3 = temp->substr(posOfArrow + 2, temp->length() - posOfArrow + 1);
        cout << "temp3 = " << temp3 << endl;

        lineEnteredStream.clear();
        lineEnteredStream.str(*temp);

        lineEnteredStream.str(temp3);
        string line; 
        while(getline(lineEnteredStream, line)){
            cout << "line = " << line << endl;
            lineEnteredStream.clear();
            lineEnteredStream.str(line);
            while(getline(lineEnteredStream, token, ' ')){
                cout << "token = " << token << endl;
                FDTemp->RHS.insert(*(new string(token)));
            }
        }
        FDArray.push_back(FDTemp);
    }
}

ClosureMap::ClosureMap(int choice){

    if (choice == 1){
        read_from_file();
    }
    else if (choice == 0){

    string* temp;
    FD* FDTemp;

    cout << "First you will enter the relation attributes, then you will enter the list of functional dependencies.\n";
    cout << "(1)  Relation attributes:  First enter the number of relation attributes:\n";
    
    cin >> numAttributes;

    cin.ignore(100, '\n');

    cout << "\nNow type in the name each relation attribute, pressing enter after each one.\n";


    for (int i = 0; i < numAttributes; i++){
        temp = new string();
        getline(cin, *temp);
        R.push_back(temp);
    }

    cout << "Now enter the functional dependencies.\n";
    cout << "How many functional dependencies would you like to add?\n";

    cin >> numFDs;

    cin.ignore(100, '\n');

    for (int i = 0; i < numFDs; i++){
        FDTemp = new FD();
        
        cout << "\nType in LHS of functional dependency.  For multi-attribute entry, separate component attributes by a space then when finished with LHS press enter." << i+1 << ".\n";

        getline(cin, *temp);

        stringstream lineEnteredStream(*temp);

        string token;
        
        while(getline(lineEnteredStream, token,' ')){
            FDTemp->LHS.insert(*(new string(token)));
        }
        cout << "\nType in RHS of functional dependency.  For multi-attribute, separate component attributes by a space then when finished with RHS press enter." << i+1 << ".\n";

        getline(cin, *temp);

        lineEnteredStream.clear();
        lineEnteredStream.str(*temp);

        while(getline(lineEnteredStream, token,' ')){
            FDTemp->RHS.insert(*(new string(token)));

        }
        FDArray.push_back(FDTemp);
     }
    }
    else{
        cout << "not a valid choice ... " << endl;
        cout << "usage: 1 is for read from file " << endl;
        cout << "0 is for user input" << endl;
    }
}

void ClosureMap::print_init_FD_Array(){

    cout << "You added " << FDArray.size() << " functional dependencies originally" << endl;

    for (int i = 0; i < FDArray.size(); i++) {

          cout <<"FD " << i + 1 << endl;

        std::set<string>::iterator it;

        for (auto it = FDArray[i]->LHS.begin(); it != FDArray[i]->LHS.end(); ++it) {

          cout << "\tElement number " <<  distance(FDArray[i]->LHS.begin(), it) + 1 << " of the LHS is:\t" << *it << "\n\n";
        }

        for (auto it = FDArray[i]->RHS.begin(); it != FDArray[i]->RHS.end(); ++it) {
           cout << "\tElement number "  << distance(FDArray[i]->RHS.begin(), it) + 1 << " of the RHS is:\t" << *it <<  "\n\n";
        }
    }
}

void ClosureMap::generate_all_subsets_of_R_and_closures(){

    int count = pow(2, R.size());

    cout << "R.size = " << R.size() << endl;

    set<string> *tempSetP;

    for (int i = 0; i < count; i++) {
        tempSetP = new set<string>;
        for (int j = 0; j < R.size(); j++){
            // cout << "i = " << i << endl;
            // cout << "j = " << j << endl;
            if ((i & (1 << j)) != 0){
                // cout << "j ===== "<< j << endl;
                fflush(stdout);
                tempSetP->insert(*R[j]);
            }
        }
        if (!tempSetP->empty()){
            all_Subsets_of_R.push_back(*tempSetP);
            pair<set<string>, set<string>>* tempSubsetPair = new pair<set<string>, set<string>>();
            tempSubsetPair->first = *tempSetP;
            tempSubsetPair->second = computeClosure(tempSetP);
            R_Subset_Closure_Pairs.push_back(*tempSubsetPair);
        }
    }
}


void ClosureMap::print_all_subsets_of_R(){

    for (int i = 0; i < all_Subsets_of_R.size(); i++){
        cout << "subset " << i + 1 << " = ";
        for (auto it = all_Subsets_of_R[i].begin(); it != all_Subsets_of_R[i].end(); it++){
            cout << *it << " ";
        }
        cout << endl;
    }

}


void ClosureMap::print_R(){

    for (int i = 0; i < R.size(); i++){
        cout << *R[i] << ", ";
    }
}

void ClosureMap::print_all_subset_closure_pairs(){

    for (int i = 0; i < R_Subset_Closure_Pairs.size(); i++){

        cout << "pair " << i << ": \n";
        cout << "\tsubset = ";
        for(auto it = R_Subset_Closure_Pairs[i].first.begin(); it !=R_Subset_Closure_Pairs[i].first.end(); it++){
            cout << *it << ", ";
        }
        cout << "\n\tclosure = ";
        for(auto it2 = R_Subset_Closure_Pairs[i].second.begin(); it2 !=R_Subset_Closure_Pairs[i].second.end(); it2++){
            cout << *it2 << ", ";
        }
        cout << "\n\n";
    }
}

// compute the attribute closure set
set<string> ClosureMap::computeClosure(const set<string>* inputSubset){

      set<string> result(*inputSubset);
      set<string> previousStateofResult;



    while(!equal(result.begin(), result.end(), previousStateofResult.begin(), previousStateofResult.end())){
        previousStateofResult = result;
        for (int i = 0; i < FDArray.size() ; i++){
            set<string>currentLHS = FDArray[i]->LHS;
            set<string>currentRHS = FDArray[i]->RHS;
            if (includes(result.begin(), result.end(), currentLHS.begin(), currentLHS.end())){
                // form union in place
                std::set<string> temp_set;
                std::set_union(result.begin(), result.end(), 
                            currentRHS.begin(), currentRHS.end(), 
                            std::inserter(temp_set, temp_set.begin()));
                result.swap(temp_set);       // temp_set will be deleted
                temp_set.clear();
            }
        }
    }
    return result;
}

void ClosureMap::generate_superkey_list(){

    for(int i = 0; i < R_Subset_Closure_Pairs.size(); i++){
        if(equal(R_Subset_Closure_Pairs[i].second.begin(), R_Subset_Closure_Pairs[i].second.end(), R_as_Set.begin(), R_as_Set.end())){
            superKeys.push_back(R_Subset_Closure_Pairs[i].first);
        }
    }
}

void ClosureMap::print_superkeys(){

    for(int i = 0; i < superKeys.size(); i++){
        cout << "\nsuperkey " << i + 1 << " is (" ; 
        for (auto it = superKeys[i].begin(); it != superKeys[i].end(); it++){
            cout << *it;
            auto it2 = it;
            if (++it2 != superKeys[i].end()){
                cout << ", ";
            }
        }
        cout << ")";
    }
    cout << endl;
}

void ClosureMap::print_candidate_keys(){

    for(int i = 0; i < candidateKeys.size(); i++){
        cout << "\n candidate key " << i + 1 << " is (" ; 
        for (auto it = candidateKeys[i].begin(); it != candidateKeys[i].end(); it++){
            cout << *it;
            auto it2 = it;
            if (++it2 != candidateKeys[i].end()){
                cout << ", ";
            }
        }
        cout << ")";
    }
    cout << endl;
}



void ClosureMap::remove_extra_sks_and_gen_cand_key_list(){

    vector<set<string>> candidateKeysPrevious;

    for(int i = 0; i < superKeys.size(); i++){
        candidateKeys.push_back(superKeys[i]);
        // candidateKeysPrevious.push_back(superKeys[i]); 
    }

    bool list_was_changed = true;

    while (list_was_changed == true){
        list_was_changed = false;
        candidateKeysPrevious.clear();

        for(int i = 0; i < superKeys.size(); i++){
                candidateKeysPrevious.push_back(candidateKeys[i]);
                // candidateKeysPrevious.push_back(superKeys[i]); 
        }

        for(int i = 0; i < candidateKeys.size() - 1; i++){
            for(int j = i+1; j < candidateKeys.size(); j++){
                if (includes(candidateKeys[i].begin(), candidateKeys[i].end(), candidateKeys[j].begin(), candidateKeys[j].end())){
                    candidateKeys.erase(candidateKeys.begin() + i);
                    list_was_changed = true;
                    i--;
                }
                else{
                    if(includes(candidateKeys[j].begin(), candidateKeys[j].end(), candidateKeys[i].begin(), candidateKeys[i].end())){
                        candidateKeys.erase(candidateKeys.begin() + j);
                        list_was_changed = true;
                        if (i > 0){i--;}
                    }
                }
            }
        }
    }


}