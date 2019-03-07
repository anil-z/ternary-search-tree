#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * ANIL ZEYBEK 150116052
 */

struct ternaryTree {
    long data;
    struct ternaryTree *left;
    struct ternaryTree *mid;
    struct ternaryTree *right;
};
typedef struct ternaryTree ternaryTree;

int karakterSayisiBul(char *fileName) {
    int numberOfCharacters = 0;

    FILE *tempFile;
    tempFile = fopen(fileName, "r");

    while (!feof(tempFile)) {
        getc(tempFile);
        numberOfCharacters++;
    }
    numberOfCharacters--;

    fclose(tempFile);

    return numberOfCharacters;
}

ternaryTree *findMax(ternaryTree *root) {
    if (root == NULL) return NULL;
    if (root->right == NULL && root->mid == NULL) return root;
    if (root->right == NULL && root->mid != NULL) return findMax(root->mid);
    return findMax(root->right);

}

ternaryTree *findMin(ternaryTree *root) {
    if (root == NULL) return NULL;
    if (root->left == NULL) return root;
    return findMin(root->left);
}

ternaryTree *insert(ternaryTree *root, long x) {
    if (root == NULL) {
        root = malloc(sizeof(ternaryTree));
        root->data = x;
        root->left = root->mid = root->right = NULL;
        return root;
    } else if (x > (root->data * root->data)) {
        root->right = insert(root->right, x);
    } else if (x < ((root->data * root->data)) && x > root->data)
        root->mid = insert(root->mid, x);

    else if (x < root->data)
        root->left = insert(root->left, x);

    return root;
}

ternaryTree *insert2(ternaryTree *root, long x) {
    // d part of the project
    if (root == NULL) {
        root = malloc(sizeof(ternaryTree));
        root->data = x;
        root->left = root->mid = root->right = NULL;
        return root;
    } else if (x % (root->data / 3) < (root->data / 9)) {
        root->left = insert2(root->left, x);
    } else if (x % (root->data / 3) > (root->data / 9) && x % (root->data / 3) < (2 * (root->data / 9))) {
        root->mid = insert2(root->mid, x);
    } else if (x % (root->data / 3) > (2 * (root->data / 9))) {
        root->right = insert2(root->right, x);
    }
    return root;
}

ternaryTree *removeNode(ternaryTree *root, long x) {
    ternaryTree *temp;
    if (root == NULL)
        printf("There is no node contains %ld\n", x);
    else if (x > (root->data * root->data))
        root->right = removeNode(root->right, x);

    else if (x < ((root->data * root->data)) && x > root->data)
        root->mid = removeNode(root->mid, x);

    else if (x < root->data)
        root->left = removeNode(root->left, x);

    else if (x == root->data) {
        if (root->left == NULL && root->mid == NULL && root->right == NULL)
            return NULL;

        else if (root->left != NULL) {
            root->data = (findMax(root->left)->data);
            root->left = removeNode(root->left, (findMax(root->left)->data));
            if (root->mid->data > (root->data * root->data)) {
                while (root->mid != NULL) {
                    root->right = insert(root->right, root->mid->data);
                    root->mid = removeNode(root->mid, root->mid->data);
                }

            }
            return root;
        } else if (root->mid != NULL) {
            root->data = (findMin(root->mid)->data);
            root->mid = removeNode(root->mid, (findMin(root->mid)->data));
            return root;
        } else if (root->right != NULL) {
            temp = root;
            root = temp->right;
            return root;
        }

    }
    return root;
}

ternaryTree *removeNode2(ternaryTree *root, long x) {
    // d part of the project
    ternaryTree *temp;
    if (root == NULL)
        printf("There is no node contains %ld\n", x);
    else if (x == root->data) {
        if (root->left == NULL && root->mid == NULL && root->right == NULL)
            return NULL;
        else if (root->left != NULL) {
            root->data = (findMax(root->left)->data);
            root->left = removeNode2(root->left, (findMax(root->left)->data));
            if (root->mid->data > (root->data * root->data)) {
                while (root->mid != NULL) {
                    root->right = insert(root->right, root->mid->data);
                    root->mid = removeNode2(root->mid, root->mid->data);
                }

            }
            return root;
        } else if (root->mid != NULL) {
            root->data = (findMin(root->mid)->data);
            root->mid = removeNode2(root->mid, (findMin(root->mid)->data));
            return root;
        } else if (root->right != NULL) {
            temp = root;
            root = temp->right;
            return root;
        }
    } else if (x % (root->data / 3) < (root->data / 9))
        root->left = removeNode2(root->left, x);
    else if (x % (root->data / 3) > (root->data / 9) && x % (root->data / 3) < (2 * (root->data / 9)))
        root->mid = removeNode2(root->mid, x);
    else if (x % (root->data / 3) > (2 * (root->data / 9)))
        root->right = removeNode2(root->right, x);

    return root;
}

ternaryTree *setup(ternaryTree *root, FILE *file, long length) {
    char str[length + 1];
    fgets(str, length + 1, file);

    char *token = strtok(str, " ");

    while (token != NULL) {
        char *ptr;
        long x = strtol(token, &ptr, 10);
        root = insert(root, x);
        token = strtok(NULL, " ");
    }
    return root;
}

ternaryTree *setup2(ternaryTree *root, FILE *file, long length) {
    char str[length + 1];
    fgets(str, length + 1, file);

    char *token = strtok(str, " ");

    while (token != NULL) {
        char *ptr;
        long x = strtol(token, &ptr, 10);
        root = insert2(root, x);
        token = strtok(NULL, " ");
    }
    return root;
}

ternaryTree *treeFinder(ternaryTree *root, long x) {
    if (root == NULL)
        printf("There is no node contains %ld\n", x);
    else if (x > (root->data * root->data))
        root->right = treeFinder(root->right, x);

    else if (x < ((root->data * root->data)) && x > root->data)
        root->mid = treeFinder(root->mid, x);

    else if (x < root->data)
        root->left = treeFinder(root->left, x);

    else if (x == root->data) {
        printf("%ld founded\n",x);
    }
    return root;
}

ternaryTree *treeFinder2(ternaryTree *root, long x) {
    if (root == NULL)
        printf("There is no node contains %ld\n", x);
    else if (x == root->data)
        printf("%ld founded\n",x);
    else if (x % (root->data / 3) < (root->data / 9))
        root->left = treeFinder2(root->left, x);
    else if (x % (root->data / 3) > (root->data / 9) && x % (root->data / 3) < (2 * (root->data / 9)))
        root->mid = treeFinder2(root->mid, x);
    else if (x % (root->data / 3) > (2 * (root->data / 9)))
        root->right = treeFinder(root->right, x);

    return root;
}

int main() {
    ternaryTree *root = NULL;
    FILE *file = fopen("C:\\Users\\sasuk\\Desktop\\input from mail.txt", "r");
    int length = karakterSayisiBul("C:\\Users\\sasuk\\Desktop\\input from mail.txt");
    root = setup(root, file, length);
    root = removeNode(root, 6);
    treeFinder(root, 15);

    ternaryTree *root2 = NULL;
    FILE *file2 = fopen("C:\\Users\\sasuk\\Desktop\\d part input", "r");
    int length2 = karakterSayisiBul("C:\\Users\\sasuk\\Desktop\\d part input.txt");
    root2 = setup2(root2, file2, length2);
    root2 = removeNode2(root2, 137);
    treeFinder2(root2, 12);

    /*
     * IN ORDER TO SEE THE TREE, MUST A DEBUGGER USED!
     */

    return 0;
}
