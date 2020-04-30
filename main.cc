#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <getopt.h>
#include "rbt.h"


using namespace std;


const char* const short_opt = ":ht:s:i:o:";
const struct option long_opt[] = {
    {"help",           0, NULL, 'h'},
    {"test",           1, NULL, 't'},
    {"seed",           1, NULL, 's'},
    {"input",          1, NULL, 'i'},
    {"output",         1, NULL, 'o'},
    {NULL,             0, NULL,  0}
};


void usage(char* argv);
void unittest_rbt(unsigned int n, unsigned int seed, ostream& to,
                  unsigned int remain);

/* Main function 
 */
int main(int argc, char **argv)
{
    int c = 0;
    string test = "0";
    string seed_str = "0"; 
    string ifile_name;
    string ofile_name;

    if(argc < 2) {
        usage(argv[0]);
        return 0;
    }

    while((c = getopt_long(argc, argv, short_opt, long_opt, NULL)) != -1) {
        switch(c) {
            case 'h':
                usage(argv[0]);
                return 0;
            case 't':
                test = optarg;
                break;
            case 's':
                seed_str = optarg;
                break;
            case 'i':
                ifile_name = optarg;
                break;
            case 'o':
                ofile_name = optarg;
                break;
            default:
                usage(argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    // Unit Test
    int num_test = stoi(test);
    if(num_test > 0) {
        int seed = stoi(seed_str);
        unittest_rbt(num_test, seed, cout, 5);
    }

    // Check if input and output files were specified
    if(ifile_name.empty() || ofile_name.empty()) {
        usage(argv[0]);
        return -1;
    } 

    return 0;
}


/* Print information on how to properly use this program
 */
void usage(char* call)
{
    cout << "Usage: " << call << endl;
    cout << "Options:" << endl;
    cout << "\t-h or --help            Display this information" << endl;
    cout << "\t-t or --test n          RBT Unit Test with n elements" << endl;
    cout << "\t-i or --input ifname    Input file" << endl;
    cout << "\t-o or --output ofname   Output file" << endl;
}

void unittest_rbt(unsigned int n, unsigned int seed, ostream& to, 
                  unsigned int remain)
{
    to << "Unit Test for baseline RBT implementation" << endl;
    srand(seed);
    vector<int> keys(n);
    for(unsigned int i = 0; i < keys.size(); i++) {
        keys[i] = rand() % 100;
    }
    int num_keys = keys.size();

    /* or you can specify keys manually */
    /* Make sure this is commented out for the final submission */
    #if 0
    keys[0] = 15;
    keys[1] = 10;
    keys[2] = 20;
    keys[3] = 8;
    keys[4] = 12;
    keys[5] = 16;
    keys[6] = 25;
    num_keys = 7;
    keys.resize(num_keys);
    keys.shrink_to_fit();
    #endif
    #if 0
    keys[0] = 100;
    keys[1] = 1;
    keys[2] = 150;
    keys[3] = 101;
    keys[4] = 23;
    keys[5] = 47;
    num_keys = 6;
    keys.resize(num_keys);
    keys.shrink_to_fit();
    #endif


    // Unsorted numbers
    to << "Input: " << endl;
    for(int i = 0; i < num_keys; i++) {
        to << keys[i] << " ";
    }
    to << endl;

    // Sorted numbers should look like...
    vector<int> tmp = keys;
    sort(tmp.begin(), tmp.end());
    to << "Sorted input: " << endl;
    for(int i = 0; i < num_keys; i++) {
        to << tmp[i] << " ";
    }
    to << endl;


    // insert_node() test
    Node** nodes = new Node*[num_keys];
    RBT my_RBT;
    for(int i = 0; i < num_keys; i++) {
        nodes[i] = new Node(keys[i]);
        my_RBT.insert_node(nodes[i]);
    }

    // tree_min() and tree_max() test
    to << "----------" << endl;
    to << "RBT min: " << my_RBT.tree_min()->get_key() << endl;
    to << "RBT max: " << my_RBT.tree_max()->get_key() << endl;
    to << "----------" << endl;

    // walk() test
    to << "----------" << endl;
    to << "RBT walk" << endl;
    my_RBT.walk(to);
    to << "----------" << endl;

    // get_pred() and get_succ() test
    to << "----------" << endl;
    to << "Predecessor/Successor" << endl;
    for(int i = 0; i < num_keys; i++) {
        
        to << nodes[i]->get_key();
        if(my_RBT.get_pred(nodes[i]) != nullptr) {
             to << " pred: " << my_RBT.get_pred(nodes[i])->get_key();
        } else {
             to << " pred: " << "none";
        }
        if(my_RBT.get_succ(nodes[i]) != nullptr) {
             to << " succ: " << my_RBT.get_succ(nodes[i])->get_key() << endl;
        } else {
             to << " succ: " << "none" << endl;;
        }

    }
    to << "----------" << endl;


    // tree_search() test
    to << "----------" << endl;
    to << "tree_search() with fake keys" << endl;
    for(int i = 0; i < num_keys; i++) {
        Node* tmp = my_RBT.tree_search(keys[i] + 1);
        if(tmp != nullptr) {
            to << "Found " << tmp->get_key() << endl;
        } else {
            to << keys[i] + 1 << " was not found" << endl;
        }
    }
    to << "----------" << endl;

    
    // tree_search() and delete_node() test
    to << "----------" << endl;
    to << "tree_search() and delete_node()" << endl;
    for(unsigned int i = 0; i < num_keys - remain; i++) {
        to << "---- deleting " << keys[i] << "-----" << endl;
        Node* tmp = my_RBT.tree_search(keys[i]);
        if(tmp != nullptr) {
            my_RBT.delete_node(tmp);
            my_RBT.walk(to);
        } else {
            to << keys[i] << " was not found" << endl;
        }
    }
    to << "----------" << endl;

    // Cleanup
    delete [] nodes;

}






