#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Loi cap phat bo nho!\n");
        exit(1);
    }
    newNode->data = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node* root, int val) {
    if (root == NULL) {
        return createNode(val);
    }
    
    if (val <= root->data) {
        root->left = insert(root->left, val);
    } else {
        root->right = insert(root->right, val);
    }
    return root;
}

struct Node* search(struct Node* root, int key) {
    if (root == NULL || root->data == key) {
        return root;
    }
    
    if (key <= root->data) {
        return search(root->left, key);
    }
    
    return search(root->right, key);
}

void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void freeTree(struct Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        freeFree(root);
    }
}

int main() {
    int values[] = {2001, 2002, 2006, 2007, 2003, 2004, 2005, 2001, 1999, 2004};
    int n = sizeof(values) / sizeof(values[0]);
    
    struct Node* root = NULL;
    
    for (int i = 0; i < n; i++) {
        root = insert(root, values[i]);
    }
    
    printf("Ket qua duyet cay theo thu tu In-order: ");
    inorder(root);
    printf("\n");

    int target = 2004;
    struct Node* result = search(root, target);
    
    if (result != NULL) {
        printf("Tim thay sinh vien co nam sinh: %d\n", result->data);
    } else {
        printf("Khong tim thay sinh vien co nam sinh %d\n", target);
    }
    freeTree(root);
    
    return 0;
}
