#pragma once
#include <fstream>      // ifstream
#include <iostream>     // cout
#include <string>       // string, stoi
#include <string_view>  // string_view
#include <chrono>       // high_resolution_clock, duration_cast, nanoseconds
#include <sstream>      // stringstream
#include <random>       //engine and dist
using namespace std;

namespace itis {

  enum nodeColor {BLACK, RED};

  struct Node {
   public:
    Node *left;
    Node *right;
    Node *parent;
    nodeColor color;
    int data;

    explicit Node(int data) : left(nullptr), right(nullptr), parent(nullptr), color(RED), data(data) {}

    Node *uncle() const;

    bool isOnLeft();

    Node *sibling();

    void moveDown(Node *nParent);

    bool hasRedChild() const;
  };
  class RBTree {
    Node *root;

    void leftRotate(Node *x);

    void rightRotate(Node *x);

    static void swapColors(Node *x1, Node *x2);

    static void swapValues(Node *u, Node *v);

    void fixRedRed(Node *x);

    static Node *successor(Node *x);

    static Node *BSTreplace(Node *x);

    void deleteNode(Node *v);

    void fixDoubleBlack(Node *x);

   public:

    RBTree() : root(nullptr) {}

    Node *search(int n);

    void insert(int n);

    void deleteByVal(int n);
  };
}// namespace itis