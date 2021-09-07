#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	char* word;
	struct Node* left;
	struct Node* right;
}Node;

Node* newNode(char* word) {
	Node* node = (Node*)malloc(sizeof(Node));
	if (node == NULL)
		return NULL;

	node->word = _strdup(word);
	node->left = NULL;
	node->right = NULL;

	return node;
}

Node* insert(Node* root, char* word) {
	if (root == NULL) { root = newNode(word); }
	else {
		Node* parent = NULL;
		Node* p = root;
		while (p != NULL) {
			parent = p;
			if (strcmp(word, p->word) == 0) { return root; }
			else if (strcmp(word, p->word) < 0) { p = p->left;}
			else { p = p->right; }
		}
		if (strcmp(word, parent->word) < 0) { parent->left = newNode(word); }
		else { parent->right = newNode(word);}
	}
	return root;
}

Node* search(Node* root, char* word)
{
	if (root)
	{
		if (strcmp(root->word, word) == 0) return root;
		if (strcmp(root->word, word) > 0)
		{
			if (root->left)	return search(root->left, word);
			else return root;
		}
		if (strcmp(root->word, word) < 0)
		{
			if (root->right) return search(root->right, word);
			else return root;
		}
	}

}

int max(int leftHeight, int rightHeight) {
	int Max = 0;
	if (leftHeight > rightHeight) {
		Max = leftHeight;
	}
	else {
		Max = rightHeight;
	}
	return Max;
}

int height(Node* root) {
	return (root == NULL) ? -1 : 1 + max(height(root->left), height(root->right));
}

int size(Node * root) {
	return (root == NULL) ? 0 : 1 + size(root->left) + size(root->right);
}

char* previous(Node* node, char* word) {
	if (node == NULL)
		return word;
	else if (strcmp(word, node->word) < 0)
		return previous(node->left, word);
	else if (strcmp(word, node->word) == 0)
		return (node->left == NULL) ? word : previous(node->left, word);
	else {
		char* tmp = previous(node->right, word);
		return (strcmp(tmp, word)==0) ? node->word : tmp;
	}
}

char* next(Node * node, char* word) {
	if (node == NULL)
		return word;
	else if (strcmp(word, node->word) > 0)
		return next(node->right, word);
	else if (strcmp(word, node->word) == 0)
		return next(node->right, word);
	else {
		char* tmp = next(node->left, word);
		return (strcmp(tmp, word) == 0) ? node->word : tmp;
	}
}

int main() {

	Node* root = NULL;
	FILE* fp;
		char* wordSTK = (char*)malloc(25 * sizeof(char));
		char word[80];
		char input[1000];

		fp = fopen("Q:\\Imperial coding\\ahmed bst studio\\dictionary.txt", "r");
		if (fp == NULL) {
			printf("file not read");
			exit(1);
		}
		while (!feof(fp))
		{
			fscanf(fp,"%s",word);
			root = insert(root,word);
		}
		fclose(fp);
		printf("Size Of Tree : %d\n", size(root));
		printf("Height Of Tree : %d\n", height(root));

		printf("Enter word(s) to be searched : \n");
		scanf("%s", input);

		wordSTK = strtok(input,"/");

		while (wordSTK != NULL) {
			Node* n = search(root, wordSTK);
			Node* temp = n;
			if (strcmp(n->word,wordSTK)==0) {
				printf("%s - CORRECT\n", wordSTK);
			}
			else {
				printf("%s -%s,%s,%s,%s\n", wordSTK, previous(root, previous(root, temp->word)),previous(root, temp->word), next(root, next(root, temp->word)),next(root, temp->word));
			}
			wordSTK = strtok(NULL,"/");
		}
		//char word2[] = "lovd";
		//printf("\ntest %s", leaf(root,(char*)"lovd"));
	return 0;
}
