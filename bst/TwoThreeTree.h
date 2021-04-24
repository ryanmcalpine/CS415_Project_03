// Description: Prototypes for the 2-3 tree class.
// Created by Nicholas Keng and Ryan McAlpine.
//

#ifndef CS415_PROJECT_03_TWOTHREETREE_H
#define CS415_PROJECT_03_TWOTHREETREE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class TwoThreeTree {
    public:
        TwoThreeTree();
        void contains() const;
        bool isEmpty();
        void printTree(ostream & out = cout) const;
        void buildTree(ifstream & input);
    private:
        struct node{
            node(const string &x, node *l, node *m, node *r)
                    :key1(x), key2(""), left(l), middle(m), right(r){
                lines1.resize(0);
                lines2.resize(0);
            }
            string key1;
            string key2;
            node * left;
            node * middle;
            node * right;
            vector<int> lines1;
            vector<int> lines2;
        };
        node * root;
        node* insertHelper(const string &X, int line, node *& rt, int &distWords);
        void promote(const string &x, int line, node *& t, int &distWord);
        node* findParent(node *& t);
        node* findParentHelper(node *& r, node *& t);
        bool containsHelper(const string & x, node * t, node* &result) const;
        void printTreeHelper(node *t, ostream & out) const;
        int findHeight(node *t);
};


#endif //CS415_PROJECT_03_TWOTHREETREE_H
