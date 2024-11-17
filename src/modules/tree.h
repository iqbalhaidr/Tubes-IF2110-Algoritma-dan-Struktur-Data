/* Kelompok   : IF2110-01-B (K01-B)           */
/* Anggota 1  : 13523019 - Shannon A A Lie    */
/* Anggota 2  : 13523021 - M Raihan Nazhim O  */
/* Anggota 3  : 13523025 - Joel Hotlan H S    */
/* Anggota 4  : 13523043 - Najwa Kahani F     */
/* Anggota 5  : 13523111 - M Iqbal Haidar     */
/* Tanggal    : Minggu, 17 November 2024      */
/* Proyek     : Alstrukdat - TB1 - Purry Mail */
/* Bagian     : ADT - Tree (Binary Tree) - H  */
/* File       : tree.h                        */
/* Deskripsi  : Definisi ADT Tree (Bin Tree)  */
/* PJ F00H    : 13523021 - M Raihan Nazhim O  */

#ifndef TREE_H
#define TREE_H

#include "boolean.h"

//## Selektor ##//
#define ROOT(p) (p)->info
#define LEFT(p) (p)->left
#define RIGHT(p) (p)->right

//## Struktur Tree (Binary Tree) ##//
typedef int ElType;
typedef struct treeNode* Address;
typedef struct treeNode { 
    ElType info;
    Address left;
    Address right;
} TreeNode;

typedef Address Tree;

//## Konstruktor ##//
Address newTreeNode(ElType val);
// Mengalokasi sebuah address p jika berhasil, atau NULL jika gagal.
// Mengembalikan address hasil alokasi sebuah elemen bernilai val. Misalnya menghasilkan p, maka p↑.info = val, p↑.left = NULL, p↑.right = NULL.

Tree NewTree (ElType root , Tree left_tree , Tree right_tree); 
// Menghasilkan sebuah tree biner dari root, left_tree, dan right_tree, jika alokasi berhasil, atau NULL jika gagal.

void CreateTree (ElType root , Tree left_tree , Tree right_tree , Tree *p);
// I.S. p sembarang.
// F.S. Menghasilkan sebuah tree p.
// Menghasilkan sebuah tree biner p dari root, left_tree, dan right_tree jika alokasi berhasil, atau NULL jika gagal.

void deallocTreeNode(Address p);
// I.S. p terdefinisi diawal.
// F.S. p didealokasi ke sistem.
// Melakukan dealokasi address p.

//## Checker - Validator ##//
boolean isTreeEmpty(Tree p);
// Mengembalikan true jika p adalah tree yang kosong.

boolean isOneElmt(Tree p);
// Mengembalikan true jika p adalah tree yang hanya terdiri atas 1 elemen.

boolean isUnerLeft(Tree p);
// Mengembalikan true jika p adalah tree yang hanya memiliki left-subtree.

boolean isUnerRight(Tree p);
// Mengembalikan true jika p adalah tree yang hanya memiliki right-subtree.

boolean isBinary(Tree p);
// Mengembalikan true jika p adalah binary tree yang memiliki left-subtree dan right-subtree.

//## Search & Navigation ##//
void removeNode(Tree *p , Address node);
// Menghapus simpul node dari tree p dan menjaga validitas tree.

Address findNode(Tree p , ElType target);
// Mengembalikan alamat simpul dengan nilai target, atau NULL jika tidak ditemukan.

void addReply(Tree *p , ElType new_reply);
// Menambahkan simpul baru dengan nilai new_reply sebagai children dari parent p.

Address getParent(Tree p , Address node);
// Mengembalikan parent dari simpul node di tree p, atau NULL jika node adalah root atau tidak ditemukan.

void getChildren(Tree p , Address *left_child , Address *right_child);
// Mengembalikan children (left_child dan right_child) dari parent p, atau NULL jika tidak ada.

//## Printer ##//
void printPreorder(Tree p);
// I.S. p terdefinisi.
// F.S. Semua simpul p sudah dicetak secara preorder : root, left-subtree, dan right-subtree.
// Setiap tree ditandai dengan tanda kurung buka dan kurung tutup (), tree kosong ditandai dengan (), serta tidak ada tambahan karakter apa pun di depan, tengah, atau akhir.
// Contoh:
// (A()()) adalah tree dengan 1 elemen dengan root A.
// (A(B()())(C()())) adalah tree dengan root A dan left-subtree (B()()) dan right-subtree (C()()).

void printInorder(Tree p);
// I.S. p terdefinisi
// F.S. Semua simpul p sudah dicetak secara inorder: left-subtree, root, dan right-subtree. 
// Setiap tree ditandai dengan tanda kurung buka dan kurung tutup (), tree kosong ditandai dengan (), serta tidak ada tambahan karakter apa pun di depan, tengah, atau akhir.
// Contoh:
// (()A()) adalah tree dengan 1 elemen dengan root A.
// ((()B())A(()C())) adalah tree dengan root A dan left-subtree (()B()) dan right-subtree (()C()).

void printPostorder(Tree p);
// I.S. p terdefinisi
// F.S. Semua simpul p sudah dicetak secara inorder: left-subtree, right-subtree, dan root. 
// Setiap tree ditandai dengan tanda kurung buka dan kurung tutup (), tree kosong ditandai dengan (), serta tidak ada tambahan karakter apa pun di depan, tengah, atau akhir.
// Contoh:
// (()()A) adalah tree dengan 1 elemen dengan root A.
// ((()()B)(()()C)A) adalah tree dengan akar A dan left-subtree (()()B) dan right-subtree (()()C).

void printTreeWithDepth(Tree p , int h , int depth);
// I.S. p terdefinisi, h adalah jarak antara root dengan node, serta depth adalah kedalaman indentasi.
// F.S. Semua simpul p sudah dicetak secara preorder : root, left-subtree, dan right-subtree.
// Selalu mengakhiri setiap baris dengan newline.
// Contoh, jika depth = 2: 
// 1) Tree preorder : (A()()), akan ditulis sebagai berikut:
// A
// 2) Tree preorder : (A(B()())(C()())), akan ditulis sebagai berikut:
// A
//   B
//   C
// 3) Tree preorder : (A(B(D()())())(C()(E()()))), akan ditulis sebagai berikut:
// A
//   B
//     D
//   C
//     E

void printTree(Tree p , int h);
// I.S. p terdefinisi, h adalah kedalaman indentasi.
// F.S. Semua simpul p sudah dicetak secara preorder : root, left-subtree, dan right-subtree. 
// Menggunakan bantuan fungsi tambahan printTreeWithDepth dan selalu diakhiri dengan newline.
// Contoh, jika h = 2: 
// 1) Tree preorder : (A()()), akan ditulis sebagai berikut:
// A
// 2) Tree preorder : (A(B()())(C()())), akan ditulis sebagai berikut:
// A
//   B
//   C
// 3) Tree preorder : (A(B(D()())())(C()(E()()))), akan ditulis sebagai berikut:
// A
//   B
//     D
//   C
//     E

//## Printer - Khusus ##//
void printAncestors(Tree p , Address node);
// Mencetak semua parent dari simpul node hingga root.

void printDescendants(Tree p , Address node);
// Mencetak semua descendant dari simpul node.

//## Additional ##//
int hitungNode(Tree root);
// Mengembalikan jumlah minimum node yang perlu ditambahkan agar tree menjadi sempurna.

#endif