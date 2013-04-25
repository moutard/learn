// An object oriented demonstration of tree traversals.

#include <iostream>
#include <string>
#include <stack>

using namespace std;

class TreeNode {
  friend class Tree;

  public:
    TreeNode(int);

  private:
    int value;
    TreeNode *left;
    TreeNode *right;
};

class Tree {
  public:
    Tree(){ root=NULL; }
    ~Tree();

    void add_to_tree(int _value);
    void attach_node(TreeNode *node);
    void in_order_no_recursion();
    void pre_order();
    void post_order();

    //destructor helper function
    void dispose_of_tree(TreeNode *current_node);


  private:
    TreeNode *root;
};

TreeNode::TreeNode(int _value) {
 // Initialize new node.
 value = _value;
 left = NULL;
 right = NULL;
};


Tree::~Tree() {
  dispose_of_tree(root);
}


void Tree::dispose_of_tree(TreeNode *current_node) {
 if(!((current_node->left == NULL) && (current_node->right == NULL))) {
   if(current_node->right != NULL) {
     dispose_of_tree(current_node->right);
    }
   if(current_node->left != NULL) {
     dispose_of_tree(current_node->left);
    }
  }
 delete current_node;
}


void Tree::add_to_tree(int _value) {
 TreeNode *new_node_ptr = new TreeNode(_value);

 if(root == NULL) {
   root = new_node_ptr;
  } else {
   attach_node(new_node_ptr);
  }
}


void Tree::attach_node(TreeNode *new_node_ptr) {
 TreeNode *search_ptr;
 TreeNode *follow_ptr;

 search_ptr = root;
 follow_ptr = root;

 while(search_ptr != NULL) {
   follow_ptr = search_ptr;
   if(new_node_ptr->value <  search_ptr->value)
    {
     search_ptr = search_ptr->left;
    }
   else
    {
     search_ptr = search_ptr->right;
    }
  }
 if(new_node_ptr->value < follow_ptr->value)
  {
   follow_ptr->left = new_node_ptr;
  }
 else
  {
   follow_ptr->right = new_node_ptr;
  }
}

/**
 * First, the current pointer is initialized to the root. Keep traversing to its
 * left child while pushing visited nodes onto the stack. When you reach a NULL
 * node (ie, you’ve reached a leaf node), you would pop off an element from the
 * stack and set it to current. Now is the time to print current’s value. Then,
 * current is set to its right child and repeat the process again. When the
 * stack is empty, this means you’re done printing.
 */
void Tree::in_order_no_recursion() {
  TreeNode *current_node = root;
  stack<TreeNode *> s;
  bool done = false;

  while(!done) {
    if(current_node){
      s.push(current_node);
      current_node = current_node->left;
    } else {
      if(s.empty()){
        done = true;
      } else {
        current_node = s.top();
        // The stack container in C++ void pop(). Doesnt return the item poped.
        s.pop();
        cout << current_node->value << endl;
        current_node = current_node->right;
      }
    }
  }
}

int main() {
  Tree * the_tree = new Tree();
  the_tree->add_to_tree(5);
  the_tree->add_to_tree(3);
  the_tree->add_to_tree(9);
  the_tree->add_to_tree(7);
  the_tree->add_to_tree(6);
  the_tree->add_to_tree(2);

  the_tree->in_order_no_recursion();
  /* do {
   cout << "Enter a string: ";
   cin.get(i, 20);
   cin.ignore(80,'\n');
   if(strlen(i) != 0)
    {
     the_tree->add_to_tree(i);
    }
  } while(strlen(string) != 0);

 cout << "\nAn in-order traversal of the tree yields:\n";
 the_tree->in_order();
*/
 return 0;
}

