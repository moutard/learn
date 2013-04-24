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
    void attach_node();
    void in_order_no_recursion();
    void pre_order();
    void post_order();

    //destructor helper function
    void dispose_of_tree(TreeNode *current_node);


  private:
    TreeNode *root;
};



int main() {
 int i;
 Tree * the_tree = new Tree();


 cout << "Enter a series of strings to be ordered alphabetically\n"
      << "in a binary search tree. These strings can be last names\n"
      << "or any other strings you wish to enter.\n\n"
      << "Enter a blank string to end.\n\n";
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


void TreeNode::TreeNode(int _value) {
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
 TreeNode *new_node_ptr;

 new_node_ptr = new TreeNode(_value);

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
   if(strcmp(new_node_ptr->string, search_ptr->string) < 0)
    {
     search_ptr = search_ptr->left;
    }
   else
    {
     search_ptr = search_ptr->right;
    }
  }
 if(strcmp(new_node_ptr->string, follow_ptr->string) < 0)
  {
   follow_ptr->left = new_node_ptr;
  }
 else
  {
   follow_ptr->right = new_node_ptr;
  }
}


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
        s.pop();
        cout << current_node->value << endl;
        current_node = current_node->right;
      }
    }
  }
}
