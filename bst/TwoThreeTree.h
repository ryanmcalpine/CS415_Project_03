// Description: Prototypes for the 2-3 tree class.
// Created by Nicholas Keng and Ryan McAlpine.
//

#ifndef CS415_PROJECT_03_TWOTHREETREE_H
#define CS415_PROJECT_03_TWOTHREETREE_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class TwoThreeTree {
    public:
        TwoThreeTree();
        void contains() const;
        bool isEmpty();
        void printTree(ostream & out = cout) const;
        void buildTree(ifstream & input);
    private:
        struct node{
            node(const string &x, node *l, node *r)
                    :key(x), left(l), right(r){
                lines.resize(0);
            }
            string key;
            node * left;
            node * right;
            vector<int> lines;
        };
        node * root;
        void insertHelper(const string &X, int line, node *& t, int &distWords);
        bool containsHelper(const string & x, node * t, node* &result) const;
        void printTreeHelper(node *t, ostream & out) const;
        int findHeight(node *t);
};


#endif //CS415_PROJECT_03_TWOTHREETREE_H
