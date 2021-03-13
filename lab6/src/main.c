#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct st_AVLTree AVLTree;
struct st_AVLTree {
    AVLTree* link[2];
    int value;
    int height;
};

AVLTree* arr;
unsigned int curAddress;

void printError() {
    printf("Error of reading!\n");
    exit(1);
}

AVLTree* createNewVertex(int newValue) {
    AVLTree* newVertex = arr + curAddress++;
    newVertex->link[0] = NULL;
    newVertex->link[1] = NULL;
    newVertex->height = 1;
    newVertex->value = newValue;
    return newVertex;
}

int getHeightTree(AVLTree* root) {
    if (root == NULL)
        return 0;
    return root->height;
}

void updateHeightTree(AVLTree* root) {
    int leftTreeHeight = getHeightTree(root->link[0]);
    int rightTreeHeight = getHeightTree(root->link[1]);
    root->height = (leftTreeHeight > rightTreeHeight ? leftTreeHeight : rightTreeHeight) + 1;
}

AVLTree* rightRotationTree(AVLTree* root) {
    AVLTree* newRoot = root->link[0];
    root->link[0] = newRoot->link[1];
    newRoot->link[1] = root;

    updateHeightTree(root);
    updateHeightTree(newRoot);
    return newRoot;
}

AVLTree* leftRotationTree(AVLTree* root) {
    AVLTree* newRoot = root->link[1];
    root->link[1] = newRoot->link[0];
    newRoot->link[0] = root;

    updateHeightTree(root);
    updateHeightTree(newRoot);
    return newRoot;
}

int balanceFactor(AVLTree* root) {
    return getHeightTree(root->link[1]) - getHeightTree(root->link[0]);
}

AVLTree* balance(AVLTree* root) {
    updateHeightTree(root);
    if (balanceFactor(root) == 2) {
        if (balanceFactor(root->link[1]) < 0)
            root->link[1] = rightRotationTree(root->link[1]);

        return leftRotationTree(root);
    }
    else if (balanceFactor(root) == -2) {
        if (balanceFactor(root->link[0]) > 0)
            root->link[0] = leftRotationTree(root->link[0]);

        return rightRotationTree(root);
    }
    return root; // балансировка не нужна
}

AVLTree* addNewVertex(AVLTree* tree, int newValue) {
    if (tree == NULL) {
        AVLTree* newVertex = createNewVertex(newValue);
        return newVertex;
    }

    if (tree->value > newValue)
        tree->link[0] = addNewVertex(tree->link[0], newValue);
    else
        tree->link[1] = addNewVertex(tree->link[1], newValue);

    return balance(tree);
}

AVLTree* fillTree(AVLTree* tree, size_t length) {
    int newElem;
    for (size_t i = 0; i < length; ++i) {
        if (scanf("%d", &newElem) == 0)
            printError();
        tree = addNewVertex(tree, newElem);
        updateHeightTree(tree);
    }
    return tree;
}

void clearTree(AVLTree* tree) {
    if (tree->link[0] != NULL)
        clearTree(tree->link[0]);
    if (tree->link[1] != NULL)
        clearTree(tree->link[1]);
    free(tree);
}

int main(void) {

    size_t countVertex;
    if (scanf("%zu", &countVertex) == 0)
        printError();

    if (countVertex > 0) {
        arr = (AVLTree*)malloc(sizeof(AVLTree) * countVertex);
        curAddress = 0;
        AVLTree *tree = NULL;

        tree = fillTree(tree, countVertex);
        printf("%d\n", getHeightTree(tree));
        free(arr);
        //clearTree(tree);
        /*printf("%u", counter);
        printf("%d", sizeof(AVLTree));*/
    }

    else
        printf("%zu", countVertex);
    return 0;
}

