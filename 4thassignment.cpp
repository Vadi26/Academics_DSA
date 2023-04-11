#include<iostream>
#include<stdlib.h>
#include"header.h"

// Assignment-4 part 1
node *Insert(node *root, int data) {
	if (root == NULL)
	{
		root = createNode(data);
		root->Level = MaxLevel;
		return root;
	}
	else {
		if (data > root->data) root->right = Insert(root->right, data);
		else root->left = Insert(root->left, data);
	}
	return root;
}

// Assignment-4 part 2
void Descendants(node *root, int i){
    if(root == NULL) return;
    if(!i) i++;
    else printf("%d " ,root->data);
    Descendants(root->left, i);
    Descendants(root->right, i);
}

// Assignment-4 part 3
node *destroy_node(node *root, int data) {
    if (root == NULL) return root;
    else if (data < root->data) root->left = destroy_node(root->left, data);
    else if (data > root->data) root->right = destroy_node(root->right, data);
    else
    {
        // Case 1 : No child
        if (root->right == NULL && root->left == NULL)
        {
            delete root;
            root = NULL;
        }
        // Case 2 : One child
        else if (root->left == NULL) {
            node *temp = root;
            root = root->right;
            delete temp;
        }
        else if (root->right == NULL) {
            node *temp = root;
            root = root->left;
            delete temp;
        }
        // Case 3 : Two children
        else {
            node *temp = findMin(root->right);
            root->data = temp->data;
            root->right = destroy_node(root->right, temp->data);
        }
    }
    return root;  
}

// Assignment-4 part 4
// \brief Returns pointer to the node which contains the given data
node* SearchNode(node *root, int data){
    if (root == NULL) return 0;
	node *temp = root;
    if (temp->data == data)
    {
        return temp;
    }
    else if (temp->data < data)
    {
        temp = SearchNode(temp->right, data);
    }
    else{
        temp = SearchNode(temp->left, data);
    }
}

/* 
                                  20
                            16          24
                        12      18  21      26
                    10      14          23
                                    22                                                 
*/

int main() { 
    node *root = NULL;
    root = CreateTree();
    node *ptr = SearchNode(root, 10);
    LevelOrderTraversal(root);
    destroy_node(root, 21);
    cout << endl;
    LevelOrderTraversal(root);

    return 0;
}