#ifndef RBT_H_
#define RBT_H_
#include <string>
#include <iostream>

using namespace std;

class Node {
private:
    int key;
    Node* parent;
    Node* left;
    Node* right;
public:
    string color;
    // Default constructor
    Node();
    // Constructor
    Node(int in_key);
    // Destructor
    // a virtual constructor is required for inheritance
    ~Node();
    // set colot to current node
    void set_color(string in);
    // Add to parent of current node
    void add_parent(Node* in);
    // Add to left of current node
    void add_left(Node* in);
    // Add to right of current node
    void add_right(Node* in);

    // Get key
    int get_key();
    // Get color
    string get_color();
    // Get parent node
    Node* get_parent();
    // Get left node
    Node* get_left();
    // Get right node
    Node* get_right();


    void print_info(ostream& to);
};

class RBT {
private:
    Node* root;

    Node* sentinel;

    // Walk the subtree from the given node
    void inorder_walk(Node* in, ostream& to);
    // Get the minimum node from the subtree of given node
    Node* get_min(Node* in);
    // Get the maximum node from the subtree of given node
    Node* get_max(Node* in);

    void left_rotate(Node* x);

    void right_rotate(Node* x);

    void insert_fixup(Node* x);

    void delete_fixup(Node* x);

    void transplant(Node* u, Node* v);
public:
    // Constructor and Destructor
    RBT();
    ~RBT();

    // Modify tree
    void insert_node(Node* in);
    void delete_node(Node* out);

    // Find nodes in the tree
    Node* tree_min(); // minimum key value
    Node* tree_max(); // maximum key value
    Node* get_succ(Node* in); // successor for a given node
    Node* get_pred(Node* in); // predecessor for a given node
    void walk(ostream& to); // Traverse the tree from min to max recursively
    Node* tree_search(int search_key);
};
#endif
