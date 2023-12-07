#include <iostream>

struct Node
{
    int key, priority;
    struct Node *left, *right;
    Node(int k) { key = k; priority = rand(); left = right = NULL; }
};

/*
    This function merges two branches together. It's guaranteed that the 
    left branch keys are smaller then right branch keys. It's just the heap property
    of the tree that needs to be satisfied.
*/
Node* merge(Node* left, Node* right) {
    if(!left) return right;
    if(!right) return left;

    /*
        To satisfy the heap property we need to compare the priorities of
        the left and right branches. 
    */
    if(left->priority > right->priority) {
        /*
            Every branch to the right of Left is guaranteed to have a lesser key than Right branch.
            It just kinda works like a basic binary search tree.
        */
        left->right = merge(left->right, right);
        return left;
    } else {
        right->left = merge(left, right->left);
        return right;
    }
}

/*
    This function splits the tree into two branches. The left branch keys
    are smaller or equal to x, and right branch keys are greater than x.
*/
std::pair<Node*, Node*> split(int x, Node* R) {
    if(!R) return {NULL, NULL};
    /*
        The R key is more than x, which means that we should search the right branch
    */
    if(R->key >= x) {
        auto r = split(x, R->right);
        /*
            We found the exact two branches that we need. Let's just put them as there are.
        */
        R->right = r.first;
        return {R, r.second};
    } else {
        auto r = split(x, R->left);
        R->left = r.second;
        return {r.first, R};
    }
}

void insert(int x, Node*& R) {
    auto r = split(x, R);
    Node *n = new Node(x);
    R = merge(r.first, merge(n, r.second));
}