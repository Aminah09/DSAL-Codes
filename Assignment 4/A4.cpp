/*
Assignment # 4
Construct an Expression Tree from postfix/prefix expression and perform recursive and non-recursive
Inorder, Pre-order and Post-order traversals.
 */

#include<iostream>
#include "stackh.h"

using namespace std;

struct tree_node
{
	    char data;
      	struct tree_node *left, *right;
};

class Tree
{
private:
    tree_node *root;
    ClassStack <tree_node*> s;
    void inorder(tree_node*);
    void preorder(tree_node*);
    void postorder(tree_node*);
public:
    Tree()
    {
        root = NULL;
    }
    tree_node* getNode(char);
    void create_postfix(string);

    void in_order()
    {
        inorder(root);
    }
    void pre_order()
    {
        preorder(root);
    }
    void post_order()
    {
        postorder(root);
    }
    void nr_inorder();
    void nr_preorder();
    void nr_postorder();

    ~Tree()
    {
        destroy(root);
        cout << "\nTree deleted...\n";
    }
    void destroy(tree_node* root)
    {
        if(root!=NULL)
    	{
        	destroy(root->left);
        	destroy(root->right);
        	delete(root);
    	}
    }
};

tree_node* Tree::getNode(char d) //create and initialize the new node
{
    tree_node *newNode = new tree_node;
    newNode->data = d;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void Tree::create_postfix(string exp)
{
    int i=0;
    tree_node *temp;
    while(exp[i]!='\0')
    {
        temp = getNode(exp[i]);
        if(!isalnum(exp[i]))   //operator
        {
            temp->right = s.Pop();   //2nd operand as right subtree
            temp->left = s.Pop();    //1st operand as left stbtree
        }
        s.Push(temp);
        i++;
    }
    root = s.Pop();
}

//Recursive Inorder Traversal
void Tree::inorder(tree_node *root) //LNR
{
	if(root!=NULL)
	{
		inorder(root->left);
		cout << root->data;
		inorder(root->right);
	}
}

//Recursive Preorder Traversal
void Tree::preorder(tree_node *root) //NLR
{
	if(root!=NULL)
	{
		cout << root->data;
		preorder(root->left);
		preorder(root->right);
	}
}

//Recursive Postorder Traversal
void Tree::postorder(tree_node *root) //LRN
{
	if(root!=NULL)
	{
		postorder(root->left);
		postorder(root->right);
		cout << root->data;
	}
}

//Non-Recursive Preorder Traversal
void Tree::nr_preorder()   //(Node Left Right)
{
    if(root!=NULL)  //Tree exists
    {
        tree_node *temp = new tree_node;
        s.Push(root);        //push root of tree on stack
        do                   //loop till stack is not empty
        {
            temp = s.Pop();             //pop the element at stack top
            while(temp != NULL)         //node exists
            {
                cout << temp->data;     //output the node data
                if(temp->right != NULL) //if it has a right child, push it on stack
                    s.Push(temp->right);
                temp = temp->left;      //go to the left subtree
            }
        }while(!s.IsEmpty());
    }
}

//Non-Recursive Inorder Traversal
void Tree::nr_inorder()   //(Left Node Right)
{
    if(root!=NULL)             //Tree exists
    {
        tree_node *temp = new tree_node;
        temp = root;           //copy root into temp
        do           //loop as long as stack is not empty or temp is a valid node
        {
            while(temp != NULL)  //go to the leftmost node in temp's left subtree
            {                    //keep pushing all the left nodes on the stack
                s.Push(temp);
                temp = temp->left;
            }
            if(!s.IsEmpty())     //if stack is not empty, pop a node and output it
            {                    //go to it's right subtree
                temp = s.Pop();
                cout << temp->data;
                temp = temp->right;
            }
        }while(temp != NULL || !s.IsEmpty());
    }
}

//Non-Recursive Postorder Traversal
void Tree::nr_postorder()   //(Left Right Node)
{
    if(root!=NULL)             //Tree exists
    {
        tree_node *prev = new tree_node;
        tree_node *temp = new tree_node;
        prev = NULL;
        s.Push(root);          //push the root on the stack
        while(!s.IsEmpty())    //loop until stack is empty
        {
            temp = s.Pop();    //pop an element from the stack
            if(temp->right == NULL && temp->left == NULL)   //leaf node
            {
                prev = temp;   //update prev to temp and output temp's data
                cout << temp->data;
            }
            else   //internal node
            {
                if(temp->right == prev || temp->left == prev)  //subtree(s) processed
                {
                    prev = temp;                //update prev and output temp's data
                    cout << temp->data;
                }
                else   ////subtree(s) not processed
                {
                    s.Push(temp); //push temp, it's right & left subtree (if exists) on stack
                    if(temp->right)
                        s.Push(temp->right);
                    if(temp->left)
                        s.Push(temp->left);
                }
            }
        }
    }
}

int main()
{
    Tree post;
    char postfixExp[20];
    cout << "Enter a Postfix Expression: ";
    cin >> postfixExp;
    post.create_postfix(postfixExp);
    cout << "\nRecursive Preorder Traversal: ";
    post.pre_order();
    cout << "\nRecursive Inorder Traversal: ";
    post.in_order();
    cout << "\nRecursive Postorder Traversal: ";
    post.post_order();
    cout << "\nNon Recursive Preorder Traversal: ";
    post.nr_preorder();
    cout << "\nNon Recursive Inorder Traversal: ";
    post.nr_inorder();
    cout << "\nNon Recursive Postorder Traversal: ";
    post.nr_postorder();
    cout<<endl;
    return 0;
}



