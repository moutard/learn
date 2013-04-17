// An object oriented demonstration of tree traversals.

#include <iostream.h>
#include <string.h>

class tree_node
{
  friend class tree;

  public:
    tree_node(char string[20]);

  private:
    char string[20];
    tree_node *left;
    tree_node *right;
}

class tree
{
  public:
    ~tree();

    void add_to_tree(char string[20]);
    void attach_node();
    void in_order();
    void pre_order();
    void post_order();

    //destructor helper function
    void dispose_of_tree(tree_node *current_node);


  private:
    tree_node *root;
}



int main()
{
 char string[20];
 tree the_tree;

 the_tree.root = NULL; // initialize root of tree to NULL

 cout << "Enter a series of strings to be ordered alphabetically\n"
      << "in a binary search tree. These strings can be last names\n"
      << "or any other strings you wish to enter.\n\n"
      << "Enter a blank string to end.\n\n";
 do
  {
   cout << "Enter a string: ";
   cin.get(string, 20);
   cin.ignore(80,'\n');
   if(strlen(string) != 0)
    {
     the_tree.add_to_tree(string);
    }
  } while(strlen(string) != 0);

 cout << "\nAn in-order traversal of the tree yields:\n";
 the_tree.in_order();

 cout << "\nPress Enter to continue.\n";
 cin.get(string, 80);
 cin.ignore(80,'\n');
 cout << "\nA preorder traveral of the tree yields:\n";
 the_tree.pre_order();

 cout << "\nPress Enter to continue.\n";
 cin.get(string,80);
 cin.ignore(80,'\n');
 cout << "\nA postorder traveral of the tree yields:\n";
 the_tree.post_order();

 cout << "\nPress Enter to continue.\n";
 cin.get(string,80);
 cin.ignore(80,'\n');

 return 0;
}


void tree_node::tree_node(char newstring[20])
{
 // Initialize new node.
 strcpy(string, newstring);
 left = NULL;
 right = NULL;
}


tree::~tree()
{
  dispose_of_tree(root);
}


void tree::dispose_of_tree(tree_node *current_node)
{
 if(!((current_node->left == NULL) && (current_node->right == NULL)))
  {
   if(current_node->right != NULL)
    {
     dispose_of_tree(current_node->right);
    }
   if(current_node->left != NULL)
    {
     dispose_of_tree(current_node->left);
    }
  }
 delete current_node;
}


void tree::add_to_tree(char string[20])
{
 tree_node *new_node_ptr;

 new_node_ptr = new tree_node(string[20]);

 if(root == NULL)
  {
   root = new_node_ptr;
  }
 else
  {
   attach_node(new_node_ptr);
  }
}


void tree::attach_node(tree_node *new_node_ptr)
{
 tree_node *search_ptr;
 tree_node *follow_ptr;

 search_ptr = root;
 follow_ptr = root;

 while(search_ptr != NULL)
  {
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


void tree::in_order()
{
 tree_node *current_node = root;

 if(current_node != NULL)
  {
   in_order(current_node->left);
   cout << current_node->string << endl;
   in_order(current_node->right);
  }
}


void tree::pre_order()
{
 tree_node *current_node = root;

 if(current_node != NULL)
  {
   cout << current_node->string << endl;
   pre_order(current_node->left);
   pre_order(current_node->right);
  }
}


void tree::post_order()
{
 tree_node *current_node = root;

 if(current_node != NULL)
  {
   post_order(current_node->left);
   post_order(current_node->right);
   cout << current_node->string << endl;
  }
}
