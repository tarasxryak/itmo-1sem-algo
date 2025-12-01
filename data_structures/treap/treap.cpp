#include <random>
#include <iostream>

struct Treap {
  static std::minstd_rand generator;
  
  struct Node {
    int val;
    int priority;
    Node* right;
    Node* left;
    Node(int vval) : val(vval), right(nullptr), left(nullptr), priority(generator()) {}
  }; Node* root;

};

