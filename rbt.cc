#include "rbt.h"

#define NEG_INF -2147483647

// ---------------------------------------
// Node class
// Default constructor



Node::Node() {
    key = -1;
    color = "RED";
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}
// Constructor
Node::Node(int in_key) {
    key = in_key;
    color = "RED";
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}
// Destructor
Node::~Node() 
{
}

// set color
void Node::set_color(string in) {
    color = in;
}

// Add parent 
void Node::add_parent(Node* in) {
    parent = in;
}

// Add to left of current node
void Node::add_left(Node* in) {
    left = in;
}

// Add to right of current node
void Node::add_right(Node* in) {
    right = in;
}

// Get key
int Node::get_key()
{
    return key;
}
// Get color
string Node::get_color() 
{
    return color;
}
// Get parent node
Node* Node::get_parent()
{
    return parent;
}
// Get left node
Node* Node::get_left()
{
    return left;
}
// Get right node
Node* Node::get_right()
{
    return right;
}
// Print the key to ostream to
// Do not change this
void Node::print_info(ostream& to)
{
    to << key << endl;

    // if (to.at()->get_left()->get_key() != NEG_INF) {
    //    to << in->get_left->get_key() << in->get_left->get_color() << endl;
    // }
    // else
    //    to << "NULL or T.nil or sentinel or whatever";

}
// ---------------------------------------


// ---------------------------------------
// RBT class
// Walk the subtree from the given node
void RBT::inorder_walk(Node* in, ostream& to)
{
    if (in != sentinel) {
        inorder_walk(in->get_left(), to); // visit left node
        in->print_info(to);  // print node
        inorder_walk(in->get_right(), to);  // visit right node
    }
}

// Constructor
RBT::RBT()
{
    sentinel = new Node(NEG_INF);
    sentinel->set_color("BLACK");
    // else to be null
    sentinel->add_left(nullptr);
    sentinel->add_right(nullptr);
    sentinel->add_parent(nullptr);
    root = sentinel;
}

// Destructor
RBT::~RBT()
{
    // delete nodes in postorder
    while(tree_min() != sentinel){
        Node *dlt = tree_min();
        delete_node(dlt);
    }
    root = nullptr;
}

void RBT::left_rotate(Node* x) {
    Node* y = x->get_right(); // set y 
    x->add_right(y->get_left());  //turn y’s left subtree into x’s right subtree
    if (y->get_left() != sentinel) {
        y->get_left()->add_parent(x);
    }
    y->add_parent(x->get_parent());  //link x’s parent to y
    if (x->get_parent() == sentinel) {
        root = y;
    } else if (x == x->get_parent()->get_left()){
        x->get_parent()->add_left(y);
    } else {
        x->get_parent()->add_right(y);
    }
    y->add_left(x); //put x on y's left
    x->add_parent(y);
}

void RBT::right_rotate(Node* x) {
    Node* y = x->get_left();
    if (y != sentinel) {
        x->add_left(y->get_right());
        if (y->get_right() != sentinel) {
            y->get_right()->add_parent(x);
        }
        y->add_parent(x->get_parent());
        if (x->get_parent() == sentinel) {
            root = y;
        } else if (x == x->get_parent()->get_right()) {
            x->get_parent()->add_right(y);
        } else {
            x->get_parent()->add_left(y);
        }
        y->add_right(x);
        x->add_parent(y);
    }
}

void RBT::insert_fixup(Node *in){
    Node* temp = sentinel;
    while(in->get_parent()!= sentinel && in->get_parent()->get_color() == "RED"){
        if(in->get_parent() == in->get_parent()->get_parent()->get_left()){
            temp = in->get_parent()->get_parent()->get_right();
            if(temp != sentinel && temp->get_color() == "RED"){
                in->get_parent()->set_color("BLACK");
                temp->set_color("BLACK");
                in->get_parent()->get_parent()->set_color("RED");
                in = in->get_parent()->get_parent();
            } else {
                if(in->get_parent() != sentinel && in == in->get_parent()->get_right()){
                    in = in->get_parent();
                    left_rotate(in);
                }
                in->get_parent()->set_color("BLACK");
                in->get_parent()->get_parent()->set_color("RED");
                right_rotate(in->get_parent()->get_parent());
            }
        } else {
            temp = in->get_parent()->get_parent()->get_left();
            if(temp!=sentinel && temp->get_color()=="RED"){
                in->get_parent()->set_color("BLACK");
                temp->set_color("BLACK");
                in->get_parent()->get_parent()->set_color("RED");
                in = in->get_parent()->get_parent();
            } else {
                if(in->get_parent() != sentinel && in == in->get_parent()->get_left()){
                    in = in->get_parent();
                    right_rotate(in);
                }
                in->get_parent()->set_color("BLACK");
                in->get_parent()->get_parent()->set_color("RED");
                left_rotate(in->get_parent()->get_parent());
            }
        }
    }
    root->set_color("BLACK");
}


// insert a node to the subtree
void RBT::insert_node(Node* in) {
    Node* y = sentinel;
    Node* x = root;
    while (x != sentinel) {
        y = x;
        if (in->get_key() < x->get_key()) {
            x = x->get_left();
        } else {
            x = x->get_right();
        }
    }
    in->add_parent(y);
    if (y == sentinel) {
        root = in;
    } else if (in->get_key() < y->get_key()) {
        y->add_left(in);
    } else {
        y->add_right(in);
    }
    in->add_left(sentinel);
    in->add_right(sentinel);
    in->set_color("RED");
    
    if (in != root) {
        insert_fixup(in);
    }
    root->set_color("BLACK");
}

void RBT::delete_fixup(Node* out){
    Node* w = sentinel;
    while(out != sentinel && (out != root) && (out->get_color() == "BLACK")){
        if(out->get_parent() != sentinel && out == out->get_parent()->get_left()){
            w = out->get_parent()->get_right();
            if(w != sentinel && w->get_color() == "RED"){
                w->set_color("BLACK");
                out->get_parent()->set_color("RED");
                left_rotate(out->get_parent());
                w = out->get_parent()->get_right();
            }
            if ((w != sentinel) && (w->get_left() != sentinel) && (w->get_right() != sentinel) && ((w->get_left())->get_color() == "BLACK") && ((w->get_right())->get_color() == "BLACK")){
                w->set_color("RED");
                out = out->get_parent();
            } else {
                if ((w != sentinel) && (w->get_right() != sentinel) && (w->get_right())->get_color() == "BLACK"){
                    if(w->get_left() != sentinel){
                            w->get_left()->set_color("BLACK");
                    }
                    w->set_color("RED");
                    right_rotate(w);
                    w = (out->get_parent())->get_right();
                }
                if(w != sentinel) {
                    w->set_color(out->get_parent()->get_color());
                }
                if(out->get_parent() != sentinel){
                    out->get_parent()->set_color("BLACK");
                }
                if(w != sentinel && w->get_right() != sentinel){
                    w->get_right()->set_color("BLACK");
                }
                left_rotate(out->get_parent());
                out = root;
            }

        } else {
            w = out->get_parent()->get_left();
            if(w != sentinel && w->get_color() == "RED"){
                w->set_color("BLACK");
                out->get_parent()->set_color("RED");
                left_rotate(out->get_parent());
                w = out->get_parent()->get_left();
            }
            if ((w != sentinel) && (w->get_right() != sentinel) && (w->get_left() != sentinel) && ((w->get_right())->get_color() == "BLACK") && ((w->get_left())->get_color() == "BLACK")){
                w->set_color("RED");
                out = out->get_parent();
            } else {
                if ((w != sentinel) && (w->get_left() != sentinel) && (w->get_left())->get_color() == "BLACK"){
                    if(w->get_right() != sentinel){
                            w->get_right()->set_color("BLACK");
                    }
                    w->set_color("RED");
                    right_rotate(w);
                    w = (out->get_parent())->get_left();
                }
                if(w != sentinel) {
                    w->set_color(out->get_parent()->get_color());
                }
                if(out->get_parent() != sentinel){
                    out->get_parent()->set_color("BLACK");
                }
                if(w != sentinel && w->get_left() != sentinel){
                    w->get_left()->set_color("BLACK");
                }
                left_rotate(out->get_parent());
                out = root;
            }
        }
    }
    if(out != sentinel){
        out->set_color("BLACK");
    }
}


void RBT::transplant(Node* u, Node* v) {
    if (u->get_parent() == sentinel) {
        root = v;
    } else if (u == u->get_parent()->get_left()) {
        u->get_parent()->add_left(v);
    } else {
        u->get_parent()->add_right(v);
    }
    v->add_parent(u->get_parent());
}


void RBT::delete_node(Node* out){
    Node* y = out;
    Node* x = sentinel;
    string y_original_color = y->get_color();

    if(out->get_left() == sentinel){
        x = out->get_right();
        transplant(out, out->get_right());
    } else if (out->get_right() == sentinel){
        x = out->get_left();
        transplant(out, out->get_left());
    } else {
        y = get_min(out->get_right());
        y_original_color = y->get_color();
        x = y->get_right();
        if (y->get_parent() == out){
            if(x != sentinel){
                x->add_parent(y);
            }
        } else {
            transplant(y, y->get_right());
            y->add_right(out->get_right());
            y->get_right()->add_parent(y);
        }
        transplant(out, y);
        y->add_left(out->get_left());
        y->get_left()->add_parent(y);
        y->set_color(out->get_color());
    }
    if(y_original_color == "BLACK"){
        delete_fixup(x);
    }
    //delete out;
}

// minimum key in the RBT
Node* RBT::tree_min()
{
    if (root == sentinel) {
        return root;
    }
    return get_min(root);
}

// maximum key in the RBT
Node* RBT::tree_max()
{
    if (root == sentinel) {
        return root;
    }
    return get_max(root);
}

// Get the minimum node from the subtree of given node
Node* RBT::get_min(Node* in)
{
    // returns the left most node
    while (in->get_left() != sentinel) {
        in = in->get_left();
    }
    return in;
}
// Get the maximum node from the subtree of given node
Node* RBT::get_max(Node* in)
{
    // returns the right most node
    while (in->get_right() != sentinel) {
        in = in->get_right();
    }
    return in;
}

// Get successor of the given node
Node* RBT::get_succ(Node* in)
{   
    // find the left most node of the right child 
    if (in->get_right() != sentinel) {
        return get_min(in->get_right());
    }
    // the node doesn't have a right subtree
    // find left most parent's parent
    Node* candidate = in->get_parent();
    while (candidate && in == candidate->get_right()) {
        in = candidate;
        candidate = candidate->get_parent();
    }
    return candidate;
}

// Get predecessor of the given node
Node* RBT::get_pred(Node* in)
{    
    // find the right most node of the left child 
    if (in->get_left() != sentinel) {
        return get_max(in->get_left());
    }
    // If candidate == NULL, we're at the root and have no predecessor,
    // so we return candidate.
    // If curr_node != candidate->get_left, then curr_node must be
    // candidate->get_right, so we return candidate.
    Node* candidate = in->get_parent();
    while (candidate && in == candidate->get_left()) {
        in = candidate;
        candidate = candidate->get_parent();
    }
    return candidate;
}

// Walk the RBT from min to max
void RBT::walk(ostream& to)
{
    inorder_walk(root, to);
}

// Search the tree for a given key
Node* RBT::tree_search(int search_key)
{
    Node* x = root;
    while (x && search_key != x->get_key()) {
        if (search_key < x->get_key()) {
            x = x->get_left();
        } else {
            x = x->get_right();
        }
    }
    return x;
}
// ---------------------------------------

