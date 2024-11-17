/* Kelompok   : IF2110-01-B (K01-B)           */
/* Anggota 1  : 13523019 - Shannon A A Lie    */
/* Anggota 2  : 13523021 - M Raihan Nazhim O  */
/* Anggota 3  : 13523025 - Joel Hotlan H S    */
/* Anggota 4  : 13523043 - Najwa Kahani F     */
/* Anggota 5  : 13523111 - M Iqbal Haidar     */
/* Tanggal    : Minggu, 17 November 2024      */
/* Proyek     : Alstrukdat - TB1 - Purry Mail */
/* Bagian     : ADT - Tree (Binary Tree) - C  */
/* File       : tree.c                        */
/* Deskripsi  : Implementasi ADT Tree (BTree) */
/* PJ F00H    : 13523021 - M Raihan Nazhim O  */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../modules/tree.h"

Address newTreeNode(ElType val) {
    Address p = malloc(sizeof(TreeNode));
    if (p != NULL) {
        ROOT(p) = val;
        LEFT(p) = NULL;
        RIGHT(p) = NULL;
    }
}

Tree NewTree(ElType root , Tree left_tree , Tree right_tree) {
    Address p = newTreeNode(root);
    if (p != NULL) {
        LEFT(p) = left_tree;
        RIGHT(p) = right_tree;
    }
    return p;
}

void CreateTree(ElType root , Tree left_tree , Tree right_tree , Tree *p) {
    *p = newTreeNode(root);
    if (p != NULL) {
        LEFT(*p) = left_tree;
        RIGHT(*p) = right_tree;
    }
}

void deallocTreeNode(Address p) {
    free(p);
}

boolean isTreeEmpty(Tree p) {
    return (p == NULL);
}

boolean isOneElmt(Tree p) {
    return ((!isTreeEmpty(p)) && (isTreeEmpty(LEFT(p))) && (isTreeEmpty(RIGHT(p))));
}

boolean isUnerLeft(Tree p) {
    return ((!isTreeEmpty(p)) && (!isTreeEmpty(LEFT(p))) && (isTreeEmpty(RIGHT(p)))); 
}

boolean isUnerRight(Tree p) {
    return ((!isTreeEmpty(p)) && (isTreeEmpty(LEFT(p))) && (!isTreeEmpty(RIGHT(p))));
}

boolean isBinary(Tree p) {
    return ((!isTreeEmpty(p)) && (!isTreeEmpty(LEFT(p))) && (!isTreeEmpty(RIGHT(p))));
}

void removeNode(Tree *p , Address node) {
    if ((*p != NULL) && (node != NULL)) {
        if (LEFT(*p) == node) {
            deallocTreeNode(LEFT(*p));
            LEFT(*p) = NULL;
        } else if (RIGHT(*p) == node) {
            deallocTreeNode(RIGHT(*p));
            RIGHT(*p) = NULL;
        } else {
            removeNode(&(LEFT(*p)) , node);
            removeNode(&(RIGHT(*p)) , node);
        }
    }
}

Address findNode(Tree p , ElType target) {
    if (p == NULL) {
        return NULL;
    } else if (ROOT(p) == target) {
        return p;
    } else {
        Address left = findNode(LEFT(p) , target);
        if (left != NULL) {
            return left;
        } else {
            return findNode(RIGHT(p) , target);
        }
    }
}

void addReply(Tree *p , ElType new_reply) {
    if (*p == NULL) {
        *p = newTreeNode(new_reply);
    } else {
        Address newNode = newTreeNode(new_reply);
        if (newNode != NULL) {
            if (LEFT(*p) == NULL) {
                LEFT(*p) = newNode;
            } else if (RIGHT(*p) == NULL) {
                RIGHT(*p) = newNode;
            }
        }
    }
}

Address getParent(Tree p , Address node) {
    if ((p == NULL) || (node == NULL)) {
        return NULL;
    } else if ((LEFT(p) == node) || (RIGHT(p) == node)) {
        return p;
    } else {
        Address left = getParent(LEFT(p) , node);
        if (left != NULL) {
            return left;
        } else {
            return getParent(RIGHT(p) , node);
        }
    }
}

void getChildren(Tree p , Address *left_child , Address *right_child) {
    if (p == NULL) {
        *left_child = NULL;
        *right_child = NULL;
    } else {
        *left_child = LEFT(p);
        *right_child = RIGHT(p);
    }
}

void printPreorder(Tree p) {
    if (isTreeEmpty(p)) {
        printf("()");
    } else {
        printf("(");
        printf("%d" , ROOT(p));
        printPreorder(LEFT(p));
        printPreorder(RIGHT(p));
        printf(")");
    }
}  

void printInorder(Tree p) {
    if (isTreeEmpty(p)) {
        printf("()");
    } else {
        printf("(");
        printInorder(LEFT(p));
        printf("%d" , ROOT(p));
        printInorder(RIGHT(p));
        printf(")");
    }
}

void printPostorder(Tree p) {
    if (isTreeEmpty(p)) {
        printf("()");
    } else{
        printf("(");
        printPostorder(LEFT(p));
        printPostorder(RIGHT(p));
        printf("%d" , ROOT(p));
        printf(")");
    }
}

void printTreeWithDepth(Tree p , int h , int depth) {
    if (!isTreeEmpty(p)) {
        int i , space = depth * h;
        for (i = 0 ; i < space ; i++) {
            printf(" ");
        }
        printf("%d\n" , ROOT(p));
        printTreeWithDepth(LEFT(p) , h , depth + 1);
        printTreeWithDepth(RIGHT(p) , h , depth + 1);
    }
}

void printTree(Tree p , int h) {
    printTreeWithDepth(p , h , 0);
}

void printAncestors(Tree p , Address node) {
    Address parent = getParent(p , node);
    if (parent != NULL) {
        printAncestors(p , parent);
        printf("%d ", ROOT(parent));
    }
}

void printDescendants(Tree p , Address node) {
    if (node != NULL) {
        printf("%d ", ROOT(node));
        printDescendants(p , LEFT(node));
        printDescendants(p , RIGHT(node));
    }
}

int hitungNode(Tree p) {
    if (isOneElmt(p)) {
        return 0;
    } else if (isBinary(p)) {
        return (hitungNode(LEFT(p)) + hitungNode(RIGHT(p)));
    } else if (isUnerLeft) {
        return (1 + hitungNode(LEFT(p)));
    } else {
        return (1 + hitungNode(RIGHT(p)));
    }
}