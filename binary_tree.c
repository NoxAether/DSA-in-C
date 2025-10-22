#include <stdio.h>
#include <stdlib.h>

typedef struct BSTNode {
    int value;
    struct BSTNode *right;
    struct BSTNode *left;

} BSTNode;

BSTNode *createBSTNode(int value) {
    BSTNode *node = malloc(sizeof(BSTNode));
    node->value = value;
    node->right = NULL;
    node->left = NULL;
    return node;
}

BSTNode *insert(BSTNode *root, int value) {
    if (!root)
        return createBSTNode(value);

    if (value < root->value)
        root->left = insert(root->left, value);
    else if (value > root->value)
        root->right = insert(root->right, value);

    return root;
}

void inorderTraversal(BSTNode *root) {
    if (root) {
        inorderTraversal(root->left);
        printf("%d ", root->value);
        inorderTraversal(root->right);
    }
}

void preorderTraversal(BSTNode *root) {
    if (root) {
        printf("%d ", root->value);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

void printTree(BSTNode *root, int space) {
    if (!root)
        return;

    space += 5;

    printTree(root->right, space);

    printf("\n");
    for (int i = 5; i < space; i++)
        printf(" ");
    printf("%d\n", root->value);

    printTree(root->left, space);
}

void freeBST(BSTNode *root) {
    if (!root)
        return;

    freeBST(root->left);
    freeBST(root->right);
    free(root);
}

int main() {

    int values[] = {50, 30, 70, 20, 40, 60, 80};

    int size = sizeof(values) / sizeof(*values);

    struct BSTNode *root = NULL;
    for (int i = 0; i < size; i++)
        root = insert(root, values[i]);

    printf("Inorder traversal (should be sorted): ");
    inorderTraversal(root);
    printf("\n");

    printf("Preorder traversal: ");
    preorderTraversal(root);
    printf("\n");

    printf("Tree structure:\n");
    printTree(root, 0);

    freeBST(root);

    return 0;
}
