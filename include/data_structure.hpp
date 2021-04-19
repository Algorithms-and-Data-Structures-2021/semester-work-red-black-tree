#pragma once
// Заголовочный файл с объявлением структуры данных
#include <bits/stdc++.h>
#include <mmcobj.h>

using namespace std;

namespace itis {

    // Tip 1: объявите здесь необходимые структуры, функции, константы и прочее

    // Пример: объявление константы времени компиляции в заголовочном файле
    // Пример: объявление структуры с полями и методами
    enum nodeColor {
        BLACK, RED
    };

    struct Node {
    public:
        Node *left;
        Node *right;
        Node *parent;
        nodeColor color;
        int data;

        explicit Node(int data) {
            this->data = data;
            left = nullptr;
            right = nullptr;
            parent = nullptr;
            this->color = RED;
        }

        Node *uncle() {
            if (parent == nullptr || parent->parent == nullptr)
                return nullptr;

            if (parent->isOnLeft())
                return parent->parent->right;
            else
                return parent->parent->left;
        }

        bool isOnLeft() {
            return this == parent->left;
        }

        Node *sibling() {
            if (parent == nullptr) {
                return nullptr;
            }

            if (isOnLeft()) {
                return parent->right;
            }
            return parent->left;
        }

        void moveDown(Node *nParent) {
            if (parent != nullptr) {
                if (isOnLeft()) {
                    parent->left = nParent;
                } else {
                    parent->right = nParent;
                }
            }
            nParent->parent = parent;
            parent = nParent;
        }

        bool hasRedChild() {
            return (left != nullptr && left->color == RED) ||
                   (right != nullptr && right->color == RED);
        }
    };

    class RBTree {
        Node *root;

        void leftRotate(Node *x) {
            Node *nParent = x->right;

            if (x == root) {
                root = nParent;
            }
            x->moveDown(nParent);

            x->right = nParent->left;
            if (nParent->left != nullptr)
                nParent->left->parent = x;

            nParent->left = x;
        }

        void rightRotate(Node *x) {
            Node *nParent = x->left;

            if (x == root)
                root = nParent;

            x->moveDown(nParent);

            x->left = nParent->right;
            if (nParent->right != nullptr)
                nParent->right->parent = x;

            nParent->right = x;
        }

        void swapColors(Node *x1, Node *x2) {
            nodeColor temp;
            temp = x1->color;
            x1->color = x2->color;
            x2->color = temp;
        }

        void swapValues(Node *u, Node *v) {
            int temp;
            temp = u->data;
            u->data = v->data;
            v->data = temp;
        }

        void fixRedRed(Node *x) {
            if (x == root) {
                x->color = BLACK;
                return;
            }

            Node *parent = x->parent, *grandparent = parent->parent,
                    *uncle = x->uncle();

            if (parent->color != BLACK) {
                if (uncle != nullptr && uncle->color == RED) {
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    grandparent->color = RED;
                    fixRedRed(grandparent);
                } else {
                    if (parent->isOnLeft()) {
                        if (x->isOnLeft()) {
                            swapColors(parent, grandparent);
                        } else {
                            leftRotate(parent);
                            swapColors(x, grandparent);
                        }
                        rightRotate(grandparent);
                    } else {
                        if (x->isOnLeft()) {
                            rightRotate(parent);
                            swapColors(x, grandparent);
                        } else {
                            swapColors(parent, grandparent);
                        }
                        leftRotate(grandparent);
                    }
                }
            }
        }

        Node *successor(Node *x) {
            Node *temp = x;

            while (temp->left != nullptr) {
                temp = temp->left;
            }
            return temp;
        }

        Node *BSTreplace(Node *x) {
            if (x->left != nullptr && x->right != nullptr)
                return successor(x->right);

            if (x->left == nullptr && x->right == nullptr)
                return nullptr;

            if (x->left != nullptr)
                return x->left;
            else
                return x->right;
        }

        // deletes the given node
        void deleteNode(Node *v) {
            Node *u = BSTreplace(v);

            bool uvBlack = ((u == nullptr || u->color == BLACK) && (v->color == BLACK));
            Node *parent = v->parent;
            if (u == nullptr) {
                if (v == root) {
                    root = nullptr;
                } else {
                    if (uvBlack) {
                        fixDoubleBlack(v);
                    } else {
                        if (v->sibling() != nullptr)
                            v->sibling()->color = RED;
                    }

                    if (v->isOnLeft()) {
                        parent->left = nullptr;
                    } else {
                        parent->right = nullptr;
                    }
                }
                delete v;
                return;
            }


            if (v->left == nullptr or v->right == nullptr) {
                if (v == root) {
                    v->data = u->data;
                    v->left = v->right = nullptr;
                    delete u;
                } else {
                    if (v->isOnLeft()) {
                        parent->left = u;
                    } else {
                        parent->right = u;
                    }
                    delete v;
                    u->parent = parent;
                    if (uvBlack) {
                        fixDoubleBlack(u);
                    } else {
                        u->color = BLACK;
                    }
                }
                return;
            }

            swapValues(u, v);
            deleteNode(u);
        }

        void fixDoubleBlack(Node *x) {
            if (x == root)
                return;

            Node *sibling = x->sibling(), *parent = x->parent;
            if (sibling == nullptr) {
                fixDoubleBlack(parent);
            } else {
                if (sibling->color == RED) {
                    parent->color = RED;
                    sibling->color = BLACK;
                    if (sibling->isOnLeft()) {
                        rightRotate(parent);
                    } else {
                        leftRotate(parent);
                    }
                    fixDoubleBlack(x);
                } else {
                    if (sibling->hasRedChild()) {
                        if (sibling->left != nullptr and sibling->left->color == RED) {
                            if (sibling->isOnLeft()) {
                                sibling->left->color = sibling->color;
                                sibling->color = parent->color;
                                rightRotate(parent);
                            } else {
                                sibling->left->color = parent->color;
                                rightRotate(sibling);
                                leftRotate(parent);
                            }
                        } else {
                            if (sibling->isOnLeft()) {
                                sibling->right->color = parent->color;
                                leftRotate(sibling);
                                rightRotate(parent);
                            } else {
                                sibling->right->color = sibling->color;
                                sibling->color = parent->color;
                                leftRotate(parent);
                            }
                        }
                        parent->color = BLACK;
                    } else {
                        sibling->color = RED;
                        if (parent->color == BLACK)
                            fixDoubleBlack(parent);
                        else
                            parent->color = BLACK;
                    }
                }
            }
        }

    public:

        RBTree() {
            root = nullptr;
        }

        Node *getRoot() {
            return root;
        }

        Node *search(int n) {
            Node *temp = root;
            while (temp != nullptr) {
                if (n < temp->data) {
                    if (temp->left == nullptr)
                        break;
                    else
                        temp = temp->left;
                } else if (n == temp->data) {
                    break;
                } else {
                    if (temp->right == nullptr)
                        break;
                    else
                        temp = temp->right;
                }
            }

            return temp;
        }

        void insert(int n) {
            Node *newNode = new Node(n);
            if (root == nullptr) {
                newNode->color = BLACK;
                root = newNode;
            } else {
                Node *temp = search(n);

                if (temp->data == n) {
                    return;
                }

                newNode->parent = temp;

                if (n < temp->data)
                    temp->left = newNode;
                else
                    temp->right = newNode;

                fixRedRed(newNode);
            }
        }

        void deleteByVal(int n) {
            if (root == nullptr)
                return;

            Node *v = search(n), *u;

            if (v->data != n) {
                cout << "No node found to delete with value:" << n << endl;
                return;
            }

            deleteNode(v);
        }

        void printInOrder() {
            cout << "Inorder: " << endl;
            if (root == nullptr)
                cout << "Tree is empty" << endl;
            else
                inorder(root);
            cout << endl;
        }

        void printLevelOrder() {
            cout << "Level order: " << endl;
            if (root == nullptr)
                cout << "Tree is empty" << endl;
            else
                levelOrder(root);
            cout << endl;
        }

        void inorder(Node *x) {
            if (x == nullptr)
                return;
            inorder(x->left);
            cout << x->data << " ";
            inorder(x->right);
        }

        void levelOrder(Node *x) {
            if (x == nullptr)
                return;

            queue < Node * > q;
            Node *curr;

            // push x
            q.push(x);

            while (!q.empty()) {
                curr = q.front();
                q.pop();
                cout << curr->data << " ";
                if (curr->left != nullptr)
                    q.push(curr->left);
                if (curr->right != nullptr)
                    q.push(curr->right);
            }
        }
    };
}