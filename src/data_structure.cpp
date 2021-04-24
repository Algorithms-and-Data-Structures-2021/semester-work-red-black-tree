#include "data_structure.hpp"

// файл с определениями

namespace itis {

  // Node
  Node *Node::uncle() const {
    if (parent == nullptr || parent->parent == nullptr) {
      return nullptr;
    }

    if (parent->isOnLeft()) {
      return parent->parent->right;
    }
    return parent->parent->left;
  }
  bool Node::isOnLeft() {
    return this == parent->left;
  }
  Node *Node::sibling() {
    if (parent == nullptr) {
      return nullptr;
    }

    if (isOnLeft()) {
      return parent->right;
    }
    return parent->left;
  }
  void Node::moveDown(Node *nParent) {
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
  bool Node::hasRedChild() const {
    return (left != nullptr && left->color == RED) || (right != nullptr && right->color == RED);
  }
  //RBTree
  void RBTree::leftRotate(Node *x) {
    Node *nParent = x->right;

    if (x == root) {
      root = nParent;
    }
    x->moveDown(nParent);

    x->right = nParent->left;
    if (nParent->left != nullptr) {
      nParent->left->parent = x;
    }

    nParent->left = x;
  }

  void RBTree::rightRotate(Node *x) {
    Node *nParent = x->left;

    if (x == root) {
      root = nParent;
    }

    x->moveDown(nParent);

    x->left = nParent->right;
    if (nParent->right != nullptr) {
      nParent->right->parent = x;
    }

    nParent->right = x;
  }

  void RBTree::swapColors(Node *x1, Node *x2) {
    nodeColor temp = x1->color;
    x1->color = x2->color;
    x2->color = temp;
  }

  void RBTree::swapValues(Node *u, Node *v) {
    int temp = u->data;
    u->data = v->data;
    v->data = temp;
  }

  void RBTree::fixRedRed(Node *x) {
    if (x == root) {
      x->color = BLACK;
      return;
    }

    Node *parent = x->parent;
    Node *grandparent = parent->parent;
    Node *uncle = x->uncle();

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

  Node *RBTree::successor(Node *x) {
    Node *temp = x;

    while (temp->left != nullptr) {
      temp = temp->left;
    }
    return temp;
  }

  Node *RBTree::BSTreplace(Node *x) {
    if (x->left != nullptr && x->right != nullptr) {
      return successor(x->right);
    }

    if (x->left == nullptr && x->right == nullptr) {
      return nullptr;
    }

    if (x->left != nullptr) {
      return x->left;
    }
    return x->right;
  }

  // deletes the given node
  void RBTree::deleteNode(Node *v) {
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
          if (v->sibling() != nullptr) {
            v->sibling()->color = RED;
          }
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

  void RBTree::fixDoubleBlack(Node *x) {
    if (x == root) {
      return;
    }

    Node *sibling = x->sibling();
    Node *parent = x->parent;
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
          if (parent->color == BLACK) {
            fixDoubleBlack(parent);
          } else {
            parent->color = BLACK;
          }
        }
      }
    }
  }
  Node *RBTree::search(int n) {
    Node *temp = root;
    while (temp != nullptr) {
      if (n < temp->data) {
        if (temp->left == nullptr) {
          break;
        }
        temp = temp->left;
      } else if (n == temp->data) {
        break;
      } else {
        if (temp->right == nullptr) {
          break;
        }
        temp = temp->right;
      }
    }

    return temp;
  }

  void RBTree::insert(int n) {
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

      if (n < temp->data) {
        temp->left = newNode;
      } else {
        temp->right = newNode;
      }

      fixRedRed(newNode);
    }
  }

  void RBTree::deleteByVal(int n) {
    if (root == nullptr) {
      return;
    }

    Node *v = search(n);

    if (v->data != n) {
      cout << "No node found to delete with value:" << n << endl;
      return;
    }

    deleteNode(v);
  }

}  // namespace itis