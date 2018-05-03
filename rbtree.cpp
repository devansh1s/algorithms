#include<iostream>
#include <bits/stdc++.h>
using namespace std;
enum Color{RED,BLACK};

class Node
{
	public:
	int data;
	bool color;
	Node *left,*right,*parent;
	Node();
};

class RBTree
{
private:
    Node *root;
    Node *NIL;
public:
    void rotateLeft(Node *x);
    void rotateRight(Node *x);
    void RB_Fixup(Node *z);
    // Constructor
    RBTree();
    void insert(int n);
    void printLevelOrder();
    void printLevel(Node* root, int level);
    int height(Node *node);
    Node *Min(Node *x);
    void Delete(int x);
    void RB_Del_Fixup(Node *p);
    void transplant(Node *u,Node *v);
    void search(int s);
};

Node::Node() 
{ 
        left = NULL;
        right = NULL;
        parent = NULL; 
}

RBTree::RBTree() 
{  
    NIL = new Node();
    NIL->color = BLACK;
    root = NIL;
}
	
const char* getColor(int i) 
{
	switch (i) 
	{
		case 0: return "RED";
		case 1: return "BLACK";
	}
}

int RBTree::height(Node* node)
{
   if (node==NIL)
       return 0;
   else
   {
     int lheight = height(node->left);
     int rheight = height(node->right);
  
     if (lheight > rheight)
         return(lheight+1);
     else
        return(rheight+1);
   }
}

void RBTree::printLevel(Node* root, int level)
{
    if(root ==NIL)
        return ;
    if(level == 1)
        cout<<root->data<<"  "<<getColor(root->color);
    else if (level > 1)
    {
        printLevel(root->left, level-1);
        printLevel(root->right, level-1);
    }
}

void RBTree::printLevelOrder()
{
    int h = height(root);
    int i;
    if(h==0)
		cout<<"\n Empty Tree \n";
    else{

    for(i=1; i<=h; i++)
    {	
	cout<<"\n";
        printLevel(root, i);
    }
	}
}	
    
void RBTree::rotateLeft(Node *x)
{
	Node *y=NIL;
	y=x->right;
	x->right=y->left;
	if(y->left!=NIL)
		y->left->parent=x;
	y->parent=x->parent;
	if(x->parent==NIL)
		root=y;
	else if(x==x->parent->left)
		x->parent->left=y;
	else
		x->parent->right=y;
	y->left=x;
	x->parent=y;
}

void RBTree::rotateRight(Node *x)
{
	Node *y=NIL;
	y=x->left;
	x->left=y->right;
	if(y->right!=NIL)
		y->right->parent=x;
	y->parent=x->parent;
	if(x->parent==NIL)
		root=y;
	else if(x==x->parent->left)
		x->parent->left=y;
	else
		x->parent->right=y;
	y->right=x;
	x->parent=y;
}

void RBTree::RB_Fixup(Node *z)
{
	Node *uncle=NIL,*grand_parent=NIL,*parent_pt=NIL;
	while((z->color!=BLACK)&&(z!=root)&&(z->parent->color==RED))
	{
		parent_pt = z->parent;
        	grand_parent = z->parent->parent;
		//CASE 1:  Parent of z is left child of Grand-parent of z 
		if(parent_pt==grand_parent->left)
		{
			uncle=z->parent->parent->right;
			if(uncle!=NIL && uncle->color==RED)
			{
				parent_pt->color=BLACK;
				uncle->color=BLACK;
				grand_parent->color=RED;
				z=grand_parent;
			}
		
			else
			{ 
				if(z==parent_pt->right)
				{
					z=parent_pt;
					rotateLeft(z);
					parent_pt=z->parent;
				}
				parent_pt->color=BLACK;
				grand_parent->color=RED;
				rotateRight(grand_parent);
				z= parent_pt;
				
			}
		}
		else if(parent_pt==grand_parent->right)
		{
		//CASE 2:Parent of z is right child of Grand parent of z
			{
				uncle=grand_parent->left;
				if(uncle!=NIL &&uncle->color==RED)
				{
					parent_pt->color=BLACK;
					uncle->color=BLACK;
					grand_parent->color=RED;
					z=grand_parent;
				}
				else
				{ 
					if(z==parent_pt->left)
					{
						z=parent_pt;
						rotateRight(z);
					    parent_pt = z->parent;
						
					}
					parent_pt->color=BLACK;
					grand_parent->color=RED;
					rotateLeft(grand_parent);
					z = parent_pt;
				}
			}
		}
	}
	root->color=BLACK;	
}

void RBTree::insert(int n)	//Insert Node in RB-Tree
{
    Node *z=new Node();
	z->left=NIL;
	z->right=NIL;
	z->parent=NIL;
	z->data=n;
    Node *y=NIL;
    Node *x=root;
    while(x!=NIL)
   	{
		y=x;
		if(z->data<x->data)
		x=x->left;
		else x=x->right;
	}
			
	z->parent=y;
			
	if(y==NIL)
	root=z;
			
	else if(z->data<y->data)
	y->left=z;
			
	else y->right=z;
			
	z->color=RED;
    RB_Fixup(z);
}

void RBTree::transplant(Node *u,Node*v){
	if(u->parent==NIL)
		root=v;
	else if(u==u->parent->left)
		u->parent->left=v;
	else
		u->parent->right=v;
	v->parent=u->parent;
}

Node * RBTree::Min(Node *x)	//Find Min value in subtree
{
	while(x->left!=NIL)
		x=x->left;
	return x;
}

void RBTree::Delete(int val)
{
     bool y_original;
     if(root==NIL)
     {
           cout<<"\nEmpty Tree." ;
           return ;
     }
     Node *z;
     z=root;
     Node *y=NIL;
     Node *x;
     int found=0;
     while(z!=NIL&&found==0)
     {
           if(z->data==val)
               found=1;
           if(found==0)
           {
                 if(z->data<val)
                    z=z->right;
                 else
                    z=z->left;
           }
     }
     if(found==0)
     {
            cout<<"\nElement Not Found.";
            return ;
     }
     else
     {
         cout<<"\nDeleted Element: "<<z->data;
         cout<<"\nColour: ";
         if(z->color==BLACK)
     cout<<"Black\n";
    else
     cout<<"Red\n";

        if(z->parent!=NIL)
              cout<<"\nParent: "<<z->parent->data;
         else
               cout<<"\nThere is no parent of the node.  ";
         if(z->right!=NIL)
               cout<<"\nRight Child: "<<z->right->data;
         else
               cout<<"\nThere is no right child of the node.  ";
         if(z->left!=NIL)
              cout<<"\nLeft Child: "<<z->left->data;
         else
               cout<<"\nThere is no left child of the node.  ";
         cout<<"\nNode Deleted.";
	y=z;
	y_original=y->color;
	if(z->left==NIL){
		x=z->right;
		transplant(z,z->right);
	}
	else if(z->right==NIL)
	{
		x=z->left;
		transplant(z,z->left);
	}
	else
	{
		y=Min(z->right);
		y_original=y->color;
		x=y->right;
		if(y->parent==z)
			x->parent=y;
		else
		{
			transplant(y,y->right);
			y->right=z->right;
			y->right->parent=y;
		}
		transplant(z,y);
		y->left=z->left;
		y->left->parent=y;
		y->color=z->color;
	}
	if(y_original==BLACK)
		RB_Del_Fixup(x);
     }
}

void RBTree::RB_Del_Fixup(Node *p)
{
    Node *s;
    while(p!=root&&p->color==BLACK)
    {
          if(p->parent->left==p)
          {
                  s=p->parent->right;
                  if(s->color==RED)
                  {
                         s->color=BLACK;
                         p->parent->color=RED;
                         rotateLeft(p->parent);
                         s=p->parent->right;
                  }
                  if(s->right->color==BLACK && s->left->color==BLACK)
                  {
                         s->color=RED;
                         p=p->parent;
                  }
                  else
                  {
                      if(s->right->color==BLACK)
                      {
                             s->left->color==BLACK;
                             s->color=RED;
                             rotateRight(s);
                             s=p->parent->right;
                      }
                      s->color=p->parent->color;
                      p->parent->color=BLACK;
                      s->right->color=BLACK;
                      rotateLeft(p->parent);
                      p=root;
                  }
          }
          else
          {
                  s=p->parent->left;
                  if(s->color==RED)
                  {
                        s->color=BLACK;
                        p->parent->color=RED;
                        rotateRight(p->parent);
                        s=p->parent->left;
                  }
                  if(s->left->color==BLACK && s->right->color==BLACK)
                  {
                        s->color=RED;
                        p=p->parent;
                  }
                  else
                  {
                        if(s->left->color==BLACK)
                        {
                              s->right->color=BLACK;
                              s->color=RED;
                              rotateLeft(s);
                              s=p->parent->left;
                        }
                        s->color=p->parent->color;
                        p->parent->color=BLACK;
                        s->left->color=BLACK;
                        rotateRight(p->parent);
                        p=root;
                  }
          }
       }
    p->color=BLACK;
}

void RBTree:: search(int s)
{
     if(root==NIL)
     {
           cout<<"\nEmpty Tree." ;
           return ;
     }
     Node *z;
     z=root;
     int found=0;
     while(z!=NIL&&found==0)
     {
           if(z->data==s)
               found=1;
           if(found==0)
           {
                 if(z->data<s)
                    z=z->right;
                 else
                    z=z->left;
           }
     }
     if(found==0)
     {
            cout<<"\nElement Not Found.";
            return ;
     }
     else
     {
         cout<<"\nElement key: "<<z->data;
         cout<<"\nColour: "<<getColor(z->color);

        if(z->parent!=NIL)
              cout<<"\nParent: "<<z->parent->data;
         else
               cout<<"\nThere is no parent of the node.  ";
         if(z->right!=NIL)
               cout<<"\nRight Child: "<<z->right->data;
         else
               cout<<"\nThere is no right child of the node.  ";
         if(z->left!=NIL)
              cout<<"\nLeft Child: "<<z->left->data;
         else
               cout<<"\nThere is no left child of the node.  ";
	}
}
	
int main()
{
    RBTree tree;
    int choice,val;
    do
    {
    	cout<<"\n Menu- \n";
    	cout<<"1.Insert\n";
    	cout<<"2.Delete\n";
    	cout<<"3.Display\n";
	cout<<"4.Search\n";
	cout<<"5.Exit\n";
    	cout<<"Enter Choice = ";
    	cin>>choice;
    	switch(choice)
    	{
    		case 1: cout<<"\n Enter value : ";
    				cin>>val;
    				tree.insert(val);
    				break;
    				
    		case 2: cout<<"\n Enter value to delete : ";
    				cin>>val;
    				tree.Delete(val);
    				break;
    		
    		case 3:  tree.printLevelOrder();
    				break;

		case 4: cout<<"\n Enter value to search : ";
    			cin>>val; 
			tree.search(val); 
			break;

		case 5: break;

    		default: cout<<"\n Wrong choice";
    	}
   	}while(choice!=5);	

    return 0;
}
