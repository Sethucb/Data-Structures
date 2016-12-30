#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//Creates a node and set the node value and parent node
Node * createNode(Data d, Node * parent){
	Node * node = (Node*)malloc(sizeof(Node));
	node->parent = parent;
	node->left = NULL;
	node->right = NULL;
	node->data = d;
	return node;
}

//Create and return a tree
Tree * createTree(){
	Tree * tree = (Tree*)malloc(sizeof(Tree));
	tree->root = NULL;
	return tree;
}

//Inserts a node and value starting from root of the tree
//Helper function for Insert()
Data * insertNode(Node * temp, Data value){
	if(value.value < temp->data.value){
		if(temp->left!=NULL){
			return insertNode(temp->left,value);			
		}
		else{		
			Node *lnode = createNode(value, temp);
			temp->left = lnode;	
			return &(lnode->data);		
		}
	}
	else if(value.value > temp->data.value){
		if(temp->right!=NULL){
			return insertNode(temp->right,value);
		}
		else{
			Node * rnode = createNode(value, temp);
			temp->right = rnode;
			return &(rnode->data);		
		}
	}
	else{
		return NULL;
	}
}

//Insert a node to tree
Data * insert(Tree * tree, Data value){
	if(tree->root == NULL){
		Node * temp = createNode(value,NULL);
		tree->root = temp;	
		return &(temp->data);
	}
	else{
		return insertNode(tree->root,value);
	}
}

//Sorts the node values of a tree
//Helper function for sort()
void sortNode(Node * temp , Data * arr,int * n){
	if(temp!=NULL){
		sortNode(temp->left,arr,n);
		arr[*n] = temp->data;
		*n = *n + 1;
		sortNode(temp->right,arr,n);		
	}
	else{
		return;
	}
}

//Sort the tree node
void sort(Tree * tree, Data * array){
	if(tree!=NULL){
		int i=0;
		sortNode(tree->root,array,&i);
	}
}

//Search a value in tree
//Helper function for search()
Data * searchNode(Node * temp, Data value){
	if(temp!=NULL){
		if(temp->data.value == value.value){
			return &(temp->data);
		}
		else if(value.value > temp->data.value){
			return searchNode(temp->right,value);
		}
		else
			return searchNode(temp->left,value);
		}
	else{
		return NULL;
	}

}

//Search for value in tree
Data * search(Tree * bst, Data value){
	if(bst!=NULL){
		return searchNode(bst->root,value);
	}
}

//Clone every node of a tree
//Helper function for clone()
Node * cloneNode(Node * temp ){
	if(temp!=NULL){
		Node * node = (Node*)malloc(sizeof(Node));
		node->data = temp->data;
		node->parent = temp->parent;
		node->left = cloneNode(temp->left);
		node->right = cloneNode(temp->right);
		return node;
	}
	else{
		return NULL;
	}

}

//Clone a tree
Tree * clone(Tree *t){
	if(t!=NULL){
		Tree * tree = (Tree*)malloc(sizeof(Tree));
		tree->root = cloneNode(t->root);
		return tree;
	}
	else{
		return NULL;
	}
}

//Checks if two nodes are equal
//Helper function for compare()
int compareNode(Node * tnode, Node * cpnode){
	if(tnode == NULL && cpnode == NULL){
		return 1;
	}
	else if(tnode==NULL || cpnode==NULL){
		return 0;
	}
	else {
		return (tnode->data.value == cpnode->data.value &&
			compareNode(tnode->left , cpnode->left) &&
			compareNode(tnode->right , cpnode->right)
			);
	}
}

//Compares two trees
int compare(Tree *t, Tree * copy){
	if(t==NULL && copy==NULL){
		return 1;
	}
	else if(t==NULL || copy==NULL){
		return 0;
	}
	else{
		return compareNode(t->root,copy->root);
	}
}

//Shortcircuit algorithm implementation
void shortcircuit(Tree * bst,Node * node,int direction){
	if(direction == 0){
		if (node->left == NULL){
			bst->root = node->right;
			bst->root->parent = NULL;
			free(node);
			return;
			
		}
		else{
			bst->root = node->left;
			bst->root->parent = NULL;
			free(node);
			return;
		}
	}

	Node * parent = node->parent;
	if(direction == 1){
		if (node->right == NULL){
			parent->right = node->left;
			node->left->parent = parent;
		}
		else{
			parent->right = node->right;
			node->right->parent = parent;
		}
		free(node);
		
	}
	else if(direction == -1){
		if (node->right == NULL){
			parent->left = node->left;
			node->left->parent = parent;
		}
		else{
			parent->left = node->right;
			node->right->parent = parent;
		}
		free(node);
	}
}
Node * searchMin(Node * temp){
	while(temp != NULL && temp->left!= NULL){
		temp = temp->left;
		searchMin(temp);
	}
	return temp;
}

//Promotion algorithm implementation
void promotion(Tree * bst,Node *temp,int direction){	
		Node * d_node = searchMin(temp->right);
		temp->data = d_node->data;
		if(d_node->left==NULL && d_node->right==NULL){	
			if(direction == -1){
				removeNode(bst,d_node,d_node->data,1);
			}
			else if (direction == 1){
				removeNode(bst,d_node,d_node->data,-1);
			}
			else if(direction == 0){
				removeNode(bst,d_node,d_node->data,-1);	
			}
		}
		else{
			shortcircuit(bst,d_node,direction);
			}
}

//Removes the node from the tree
//Helper function of removeData()
void removeNode(Tree * bst,Node * temp,Data value,int direction){
	if(temp == NULL){
		return;
	}
	else if(value.value > temp->data.value){
		removeNode(bst,temp->right,value,1);
	}
	else if(value.value < temp->data.value){
		removeNode(bst,temp->left,value,-1);
	}
	else if(value.value == temp->data.value){
		if(temp->left ==NULL && temp->right ==NULL){
			if(direction == -1){
				temp->parent->left = NULL;
			}
			else if(direction == 1){
				temp->parent->right = NULL;
			}
			else if(direction == 0){
				bst->root = NULL;
			}
			free(temp);
		}

		else if(temp->right == NULL || temp->left == NULL){
			shortcircuit(bst,temp,direction);
		}
		else{
			promotion(bst,temp,direction);
		}
	}
}

//Removes data from tree
void removeData(Tree * bst, Data value){
	if(bst==NULL){
		return;
	}
	else{
		removeNode(bst,bst->root,value,0);
	}
}

//Deletes node from the tree
//Helper function of deleteTree()
void deleteLeaf(Node * temp){
	if(temp == NULL){
		return;
	}
		deleteLeaf(temp->left);
		deleteLeaf(temp->right);
		free(temp);
}

//Deletes tree from the memory
void deleteTree(Tree * bst){
	if(bst == NULL){
		return;
	}
	else{
		deleteLeaf(bst->root);
		free(bst);
	}
}