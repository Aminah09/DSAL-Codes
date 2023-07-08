/*
Assignment # 5
Implement binary search tree and perform following operations:
a. Insert     b. Delete       c. Search      d. Mirror image
e. Display    f. Display level wise
*/

#include<iostream>

using namespace std;

class t_node
{
	public:
	int data;
	t_node *left,*right;
	t_node()
	{
		left=right=NULL;
	}
};
class bst
{
  	t_node *root, *m_node;
	void inorder_display(t_node*);
	t_node* mirror(t_node*);
	int height(t_node*);
	void printLevel(t_node*, int);
	t_node *inorder_successor(t_node*);
	t_node* delete_node(t_node* ,int);
  	public:

  	bst()
  	{
    		root=NULL;
  	}
  	~bst()
  	{
        destroy(root);
        cout << "\nTree deleted...\n";
    }
    void destroy(t_node* root)
    {
        if(root!=NULL)
    	{
        	destroy(root->left);
        	destroy(root->right);
        	delete(root);
    	}
    }

    void create();
  	void bst_insert();
  	void inorder_display();
  	int bst_search();
  	void minimum();
  	void maximum();
  	void delete_node();
	void mirror();
	void display_mirror();
	void Level();
};

void bst::create()
{
	char choice;
	do
	{
		bst_insert();

	cout << "Do you want to continue?? Y/N\nEnter your choice : ";
	cin >> choice;
 	}while(choice=='y' || choice=='Y');
}

void bst::bst_insert()
{
	int flag;
	char choice;
	t_node *pwalk,*parent,*new_node;

	new_node=new t_node;
	new_node->left = new_node->right = NULL;
    flag=0;
 	cout<<"\nEnter the data : ";
	cin >> new_node->data;
	if(root == NULL)
	{
		root=new_node;
		flag=1;  //root created
	}
	else
	{
		pwalk=root;
		while(pwalk!=NULL) // locate for the leaf or leaf like node for insertion
		{
			parent=pwalk;
			if(new_node->data >= pwalk->data)
				pwalk = pwalk->right;
			else
		  		pwalk = pwalk->left;
		}
		if(flag==0)         //not the first node of the tree
		{
		  	if(new_node->data < parent->data)   //attach the node
		  		parent->left=new_node;
		  	else
				parent->right=new_node;
		}
	}
}

void bst::inorder_display()
{
	cout<<"\n";
	if(root!= NULL)
	{
		cout<<"\nThe Inorder traversal of Tree is : ";
		inorder_display(root);
	}
	else
		cout<<"The Tree does not exist!\n";
}

void bst::inorder_display(t_node* temp)
{
 	if(temp!=NULL)
   	{
   	  	inorder_display(temp->left);
   	  	cout << temp->data << " ";
   	  	inorder_display(temp->right);
   	}
}

int bst::bst_search()
{
  	t_node *temp;
  	int element;
  	cout << "\nEnter data data to be searched : ";
  	cin >> element;

  	temp=root;
  	while(temp!=NULL)
  	{
    		if(temp->data == element)
      			return 1;
    		else if(temp->data < element) // element > root
      			temp=temp->right;
    		else
      			temp=temp->left;
  	}
   	return 0;
}

void bst::minimum()
{
	t_node *temp;
	temp=root;
	while(temp->left != NULL)
		temp=temp->left;
	cout<<"\nMinimum number is : "<< temp->data << "\n";
}

void bst::maximum()
{
	t_node *temp;
	temp=root;
	while(temp->right!=NULL)
		temp=temp->right;
	cout<<"\nMaximum number is : "<< temp->data << "\n";
}

void bst::mirror()
{
	if(root!=NULL)
		m_node=	mirror(root);
}

t_node* bst::mirror(t_node* root)
{
   	t_node* m_node=NULL;
   	if(!root) return NULL;
   	m_node = new t_node;
	m_node->left = m_node->right = NULL;
	m_node->data = root->data;
   	m_node->left = mirror(root->right);
   	m_node->right = mirror(root->left);
   	return m_node;
}

void bst::display_mirror()
{
	cout<<"\n";
	if(m_node!=NULL)
	inorder_display(m_node);
}

t_node* bst::inorder_successor(t_node* temp)
{
          temp=temp->right;
	  while(temp->left!=NULL)
	  	temp=temp->left;
	  return temp;
}

void bst::delete_node()
{
	int target;
	if(root != NULL)
	{
		cout<<"\nEnter the Data to be Deleted : ";
	  	cin >> target;
		root=delete_node(root ,target);
	}
}

t_node* bst::delete_node(t_node* t ,int x)
{
	t_node *temp;
	if(t==NULL)
	{
		cout<<"\nElement not found";
		return(t);
	}
	if(x < t->data)
	{
		t->left = delete_node(t->left,x);
		return(t);
	}
	if(x > t->data)
	{
		t->right = delete_node(t->right,x);
		return(t);
	}
	if(t->left==NULL && t->right==NULL) // is a leaf node?
	{
		temp=t;
		delete temp;
		return(NULL);
	}
	if(t->left==NULL) // check for only right subtree
	{
		temp=t;
		t=t->right;
		delete temp;
		return(t);
	}
	if(t->right==NULL) // check for only left subtree
	{
		temp=t;
		t=t->left;
		delete temp;
		return(t);
	}
	temp=t->right;
	while(temp->left!=NULL)
		temp=temp->left;
	t->data=temp->data;
	t->right = delete_node(t->right,temp->data);
	return (t);
}

int bst::height(t_node *root)
{
    	if(!root)      //tree does not exist
        	return 0;

    	if(!root->left && !root->right)   //only root node exists
        	return 1;

    	int lheight = height(root->left);  //find the height of the left subtree
    	int rheight = height(root->right); //find the height of the right subtree

  	if(lheight > rheight)   //check which subtree has greater height
		return(lheight+1);  //add 1 to it to get the height of the tree / subtree
	else
		return(rheight+1);
}

void bst::Level()
{
    	int i;
    	int h = height(root);

    	for(i=0; i<=h-1; i++)
        {
        	cout << "Level " << i << "- ";
	        printLevel(root, i);
	        cout << "\n";
    	}
}

void bst::printLevel(t_node * node, int level)
{
    	if(!node)
        	return;
    	if (level == 0)
        	cout << " " << node->data;

    	printLevel(node->left, level-1);
    	printLevel(node->right, level-1);
}

main()
{
  	bst T;
  	int choice,temp,target_node;

  	do
  	{
    		cout<<"\n1.Create\n2.Display Inorder\n3.Insert\n4.Search\n5.Minimum Node\n6.Maximum Node\n7.Delete\n8.Mirror\n9.Levelwise \n10.Exit\nEnter Your Choice : ";
    		cin>>choice;

    		switch(choice)
    		{
      			case 1:	T.create();
         			break;
      			case 2:	T.inorder_display();
         			break;
		      	case 3:	T.bst_insert();
		        	break;
      			case 4:	temp=T.bst_search();
         			if(temp==1)
           				cout<<"Data found";
         			else
           				cout<<"Data not found";
         			break;
      			case 5:	T.minimum();
	  			break;
      			case 6:	T.maximum();
	  			break;
      			case 7:	T.delete_node();
	  			T.inorder_display();
	  			break;
			case 8:	T.mirror();
				cout<<"\nThe Inorder traversal of the mirror tree is : ";
				T.display_mirror();
				break;
			case 9:	T.Level();
				break;
  		}
   	}while(choice!=10);
}
