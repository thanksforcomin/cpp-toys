#include <iostream>

struct Node
{
    int key, priority;
    struct Node *left, *right;
    Node(int k) { key = k; priority = rand(); left = right = NULL; }
};

Node* merge(Node* left, Node* right) {
    if(!left) return right;
    if(!right) return left;

    if(left->priority > right->priority) {
        left->right = merge(left->right, right);
        return left;
    } else {
        right->left = merge(left, right->left);
        return right;
    }
}

std::pair<Node*, Node*> split(int x, Node* R) {
    if(!R) return {NULL, NULL};
    if(R->key >= x) {
        auto r = split(x, R->right);
        R->right = r.first;
        return {R, r.second};
    } else {
        auto r = split(x, R->left);
        R->left = r.second;
        return {r.first, R};
    }
}