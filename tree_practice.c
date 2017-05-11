#include<stdio.h>
#include<stdlib.h>
#include<errno.h>



typedef struct node{
	int data;
	struct node *left, *right;
} Node;

Node * min_node(Node * root);
Node * buildTree(int d);
void add(Node * root, int data);
void print_preorder(Node * root);
void print_inorder(Node * root);
void print_postorder(Node * root);
int find(Node * root, int data);
Node * delete(Node * root, int data);
int serialize(Node * root, int * preorder, int * inorder, int * tree_size);
void get_preorder(Node * root, int * array, int * index);
void get_inorder(Node * root, int * array, int * index);
Node * deserialize(int * preorder, int * inorder, int lower, int higher);

int main(void){

	printf("Running...\n");

	Node *root = buildTree(5);	
	add(root, 2);
	add(root, 1);
	//delete(root, 7);
	add(root, 7);
	add(root, 6);
	add(root, 8);
	printf("Preorder: \n");
	print_preorder(root);
	printf("Inorder: \n");
	print_inorder(root);
	printf("Postorder: \n");
	print_postorder(root);
	printf("Find: %d, Result: %d\n", 9, find(root, 9));
	printf("Find: %d, Result: %d\n", 2, find(root, 2));
	printf("root data; %d\n", root->data);
	int in[80];
	int pre[80];
	int * tree_size = (int *) malloc(sizeof(int));
	serialize(root, pre, in, tree_size);
	int i=0;
	while(i<*tree_size){
		printf("preorder array: %d\n", pre[i]);
		i++;
	}
	i=0;
	while(i<*tree_size){
		printf("inorder array: %d\n", in[i]);
		i++;
	}
	printf("size of array/tree: %d\n", *tree_size);
	Node * new_tree = deserialize(pre, in, 0, *tree_size);
	printf("preorder of new tree: \n");
	print_preorder(new_tree);
}

void add(Node * root, int data){
	if(root == NULL){
		printf("Error: Root is Null\n");
	}else{
		if(root->data > data){
			printf("New Data is smaller than current\n");
			if(root->left == NULL){
				Node * new_node = (Node *) malloc((size_t)sizeof(Node));
				if(new_node == NULL){
					printf("Malloc of root Failed...");
					exit(-1);
				}
				new_node->data = data;
				root->left = new_node;
			}else{
				add(root->left, data);
			}
		}else{
			printf("New Data is larger than current\n");
			if(root->right == NULL){
				//Build Node
				Node * new_node = (Node *) malloc((size_t)sizeof(Node));
				if(new_node == NULL){
					printf("Malloc of root Failed...");
					exit(-1);
				}
				new_node->data = data;
				root->right = new_node;
			}else{
				add(root->right, data);
			}
		}
	}
	return;
}
Node * buildTree(int data){
	
	Node * root = (Node *) malloc((size_t)sizeof(Node));
	if(root == NULL){
		printf("Malloc of root Failed...");
		exit(-1);
	}
	root->data = data;
	return(root);
}

void print_preorder(Node * root){
	if (root == NULL){
		return;
	}
	printf("%d\n", root->data);
	print_preorder(root->left);
	print_preorder(root->right);
	return;
}
void print_inorder(Node * root){
	if (root == NULL){
		return;
	}
	print_preorder(root->left);
	printf("%d\n", root->data);
	print_preorder(root->right);
	return;
}
void print_postorder(Node * root){
	if (root == NULL){
		return;
	}
	print_preorder(root->left);
	print_preorder(root->right);
	printf("%d\n", root->data);
	return;
}
int find(Node * root, int data){
	if(root == NULL){
		return 0;
	}
	if(root->data == data){
		return 1;
	}else if(root->data > data){
		return find(root->left, data);
	}else{
		return find(root->right, data);
	}
}
Node * min_node(Node * root){
	if(root == NULL){
		return NULL;
	}
	if(root->left == NULL){
		return root;
	}else{
		return min_node(root->left);
	}
}

Node * delete(Node * root, int data){
	if(root == NULL){//Root is NULL
		return root;
	}
	//Data not found, search child nodes
	if(root->data > data){
		root->left = delete(root->left, data);
	}else if(root->data < data){
		root->right = delete(root->right, data);
	}else{
	//Data found.  Delete Node
		//Node has one or no children
		if(root->left == NULL){
			Node * tmp = root->right;
			free(root);
			return tmp;
		}else if(root->right == NULL){
			Node * tmp = root -> left;
			free(root);
			return tmp;
		}
		//Nod has two children
		Node * tmp = min_node(root->right);
		root->data = tmp->data;
		root->right = delete(root->right, tmp->data);
	}
	return root;
}	

int serialize(Node * root, int * preorder, int * inorder, int * tree_size){
	if (root == NULL){
		return;
	}
	int * index = malloc(sizeof(int));
	*index = 0;
	get_preorder(root, preorder, index);
	printf("after the getpreorder call\n");
	*tree_size = *index;
	*index = 0;
	printf("print the inorder now \n");
	get_inorder(root, inorder, index);
	if(*index != *tree_size){
		//ERROR!!
	}
	return(0);
}	
void get_preorder(Node * root, int * array, int * index){
	if (root == NULL){
		return;
	}
	printf("addidng %d to preorder array\n", root->data);
	array[*index] = root->data;
	(*index)++;
	//CHECK IF ARRAY SIZE IS TOO BIG
	get_preorder(root->left, array, index);
	get_preorder(root->right, array, index);
	return;
}
void get_inorder(Node * root, int * array, int * index){
	if (root == NULL){
		return;
	}
	get_inorder(root->left, array, index);
	printf("addidng %d to inorder array\n", root->data);
	array[*index] = root->data;
	//CHECK IF ARRAY SIZE IS TOO BIG
	(*index)++;
	get_inorder(root->right, array, index);
	return;
}

Node * deserialize(int * preorder, int * inorder, int lower, int higher){
	if(lower >= higher){

		return NULL;
	}
	
	Node * new_root = buildTree(preorder[0]);
	preorder++;
	int index = lower;
	while (index <= higher){
		if(new_root->data == inorder[index]){
			printf("breaking at index: %d\n", index);
			break;
		}
		index++;
	}
	printf("Before recursive left: \n");
	printf("preorder[0]: %d\n", preorder[0]);
	printf("lower: %d, higher: %d\n", lower, index);
	new_root->left = deserialize(preorder, inorder, lower, index-1);
	
	printf("lower: %d, higher: %d\n", index, higher);
	new_root->right = deserialize(preorder, inorder, index+1, higher);
	return new_root;
}
/*Node * deserialize(int * preorder, int * inorder, int tree_size){
	if(tree_size == 0){
		return NULL;
	}
	printf("preorder[0]: %d\n", preorder[0]);
	printf("size before loop: %d\n", tree_size);
	printf("inorder first %d\n", inorder[0]);
	
	Node * new_root = buildTree(preorder[0]);
	preorder++;
	int index = 0;
	while (index < tree_size){
		if(new_root->data == inorder[index]){
			printf("breaking at index: %d\n", index);
			break;
		}
		index++;
	}
	int tmp = tree_size-index;
	printf("root.left being set in deserialize. tree_size is : %d\n", index);
	root->left = deserialize(preorder, inorder, index);
	index = 0; 
	while(index < tmp){
		inorder++;
		index++;
	}
	printf("root.right being set in deserialize. tree_size is : %d\n", tmp);
	root->right = deserialize(preorder, inorder, tmp);
	return root;
}*/
