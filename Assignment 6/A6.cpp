/*Assignment 6
Implement In-order Threaded Binary Tree and traverse it in In-order and Pre-order.
*/

#include<iostream>
#include "stackh.h"

using namespace std;

struct node    //structure of tree node
{
    node * lptr;     //left pointer
    bool lthread;     //true if lptr contains a thread
    char data;        //node data
    bool rthread;     //true if rptr contains a thread
    node *rptr;      //right pointer
};

class tbt
{
    node *head, *root;
    string expr;
public:
    tbt() //constructor - create and initialize head node
    {
        head = new node;
        head->lthread = false;
        head->data = '-';
        head->rthread = true;
        head->rptr = head;
    }

    void input_expr();
    bool check_expr(string);
    void construct_tree();
    void inorder();
    void preorder();

    ~tbt()    //destructor - delete the tree
    {
        destroy(head);
        //delete(head);
        cout << "\nTree deleted.\n";
    }
    void destroy(node* root)  //recursive function
    {
        if(root!=NULL)
    	{
        	if(!(root->lthread))  //left child exists
                destroy(root->lptr);
            if(!(root->rthread))  //right child exists
                destroy(root->rptr);
        	delete(root);
    	}
    }
};

//Accept a valid postfix expression
void tbt::input_expr()
{
    bool check;
    do
    {
        cout << "Enter a Postfix Expression: ";
        cin >> expr;
        check = check_expr(expr);
        if(!check)  //if check=false - expression is not a valid one
            cout << "Please enter a valid Postfix Expression.\n";
    }while(!check);
}

//Check if the expression is a valid postfix expression
bool tbt::check_expr(string str)
{
    char *token;
    int operand=0, oper=0, i=0;

    //first 2 tokens should be operands and last token should be an operator
    for(token = &str[0]; *token != '\0'; i++,token++);
    i--;
    if((!(isalnum(str[0]))) || (!(isalnum(str[1]))) || (isalnum(str[i])))
        return false;

    //count no. of operators & operands. operands = operators + 1
    for(token = &str[0]; *token != '\0'; token++)
    {
        if(isalnum(*token))
            operand++;
        else
            oper++;
    }
    if(operand == oper+1)
        return true;
    else
        return false;
}

//constructing the TBT from the given Postfix Expression
void tbt::construct_tree()
{
    ClassStack <struct node*> s;
    int i=0;
    node *parent, *t1, *t2, *temp1, *temp2;

    while(expr[i] != '\0')
    {
        parent = new node;
        if(isalnum(expr[i]))  //is operand, create and initialize the node
        {
            parent->data = expr[i];
            parent->lthread = true;
            parent->rthread = true;
            parent->lptr = NULL;
            parent->rptr = NULL;
        }
        else   //is operator, pop 2 elements and attach as right and left subtrees
        {

            parent->data = expr[i];
            parent->lthread = false;
            parent->rthread = false;
            t2 = s.Pop();
            t1 = s.Pop();
            parent->rptr = t2;
            parent->lptr = t1;

            temp1 = t1;
            temp2 = t2;
            //set the right ptr of the rightmost node in the left subtree to point to parent
            while(!(temp1->rthread))
                temp1 = temp1->rptr;
            temp1->rptr = parent;

            //set the left ptr of the node in the right subtree to point to parent
            while(!(temp2->lthread))
                temp2 = temp2->lptr;
            temp2->lptr = parent;
        }
        s.Push(parent);
        i++;
    }
    //attach the root node to the head node
    root = s.Pop();
    head->lptr = root;

    temp1 = root->lptr;
    temp2 = root->rptr;

    //set leftmost node's left pointer to point to head
    while(!(temp1->lthread))
        temp1 = temp1->lptr;
    temp1->lptr = head;

    //set rightmost node's right pointer to point to head
    while(!(temp2->rthread))
        temp2 = temp2->rptr;
    temp2->rptr = head;
}

//Inorder traversal of the Threaded Binary Tree
void tbt::inorder()
{
    node *temp = head->lptr;     //start at root node
    while(!(temp->lthread))      //go to leftmost node
        temp = temp->lptr;
    while(temp != head)
    {
        cout << temp->data << " ";  //output the node data and follow the right pointer
        if(temp->rthread)  //if it is a thread, follow it and then o/p data
            temp = temp->rptr;
        else //if it is a link, follow it, go to the leftmost node and then o/p data
        {
            temp = temp->rptr;
            while(!(temp->lthread) && (temp != head))
                temp = temp->lptr;
        }
    }
}

//Preorder traversal of the Threaded Binary Tree
void tbt::preorder()
{
    node *temp = head->lptr;   //start at root node

    while(temp != head)
    {
        cout << temp->data << " ";  //output the node data
        if(!(temp->lthread))  //internal node
            temp = temp->lptr;
        else     //leaf node
        {
            temp = temp->rptr;
            if(!(temp->rthread)) //if temp has a right child, go to the right child
                temp = temp->rptr;
        }
    }
}

int main()
{
    tbt t;

    t.input_expr();
    cout << "Constructing the Inorder Threaded Binary Tree\n";
    t.construct_tree();
    cout << "\nInorder Traversal: ";
    t.inorder();
    cout << "\nPreorder Traversal: ";
    t.preorder();
    return 0;
}

