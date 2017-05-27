#ifndef _BST_H_
#define _BST_H_

typedef struct data_{
	int value;
}Data;

typedef struct node_{
		Data data;
		struct node_ * left;
		struct node_ * right;
		struct node_ * parent;
}Node;

typedef struct tree_{
	Node * root;
}Tree;

Node * createNode(Data d, Node * parent);
Tree * createTree();
Data * insertNode(Node * temp, Data value);
Data * insert(Tree * tree, Data value);
void sortNode(Node * temp , Data * arr,int * n);
void sort(Tree * tree, Data * array);
Data * search(Tree * bst, Data value);
Node * cloneNode(Node * temp);
Tree * clone(Tree *t);
int compareNode(Node * tnode, Node * cpnode);
int compare(Tree *t, Tree * copy);
void shortcircuit(Tree * bst,Node * node,int direction);
Node * searchMin(Node * temp);
void promotion(Tree * bst,Node *temp,int direction);
void removeNode(Tree * bst,Node * temp,Data value,int direction);
void removeData(Tree * bst, Data value);
void deleteLeaf(Node * temp);
void deleteTree(Tree * bst);

#endif