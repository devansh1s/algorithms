#include <bits/stdc++.h>
#define NIL INT_MIN
using namespace std;

enum Color {RED, BLACK};

class node
{
	public:
		int key;
		bool color;
		node *p, *left, *right;

		node()
		{
			key=0;
			p=left=right=NULL;
			color = BLACK;
		}

		node(int val)
		{
			key=val;
			p=left=right=NULL;
			color = BLACK;
		}
};

class tree
{
	public:
		node *root;

		tree() {root= new node(NIL);}

		void left_rotate(node *x)
		{
			node *y=x->right;
			x->right=y->left;

			if(y->left->key!=NIL)
			y->left->p=x;

			y->p=x->p;

			if(x->p->key==NIL)
			root=y;

			else if(x==x->p->left)
			x->p->left=y;

			else x->p->right=y;

			y->left=x;
			x->p=y;
		}

		void right_rotate(node *x)
		{
			node *y=x->left;
			x->left=y->right;

			//if(y->right!=NULL)
			if(x->left->key!=NIL)
			x->left->p=x;

			y->p=x->p;

			if(x->p->key==NIL)
			root=y;

			else if (x=x->p->left)
			x->p->left=y;

			else x->p->right=y;

			y->right=x;
			x->p=y;
		}

		void insert_fixup(node *z)
		{
			while((z!=root)&&(z->color!=BLACK)&&(z->p->color==RED))
			{
				if(z->p==z->p->p->left)
				{
					node *y=z->p->p->right;

					if((y->key!=NIL)&&(y->color==RED))	//uncle is red
					{
						z->p->p->color=RED;
						y->color=BLACK;
						z->p->color=BLACK;
						z=z->p->p;
					}

					else				//uncle is black
					{
						if (z==z->p->right)	//left-right
						{
							z=z->p;
							left_rotate(z);
						}

						z->p->color=BLACK;	//left-left
						z->p->p->color=RED;
						right_rotate(z->p->p);
					}
				}

				else if(z->p==z->p->p->right)
				{
					node *y=z->p->p->left;

					if((y!=NULL)&&(y->color==RED))	//uncle is red
					{
						y->color=BLACK;
						z->p->color=BLACK;
						z->p->p->color=RED;
						z=z->p->p;
					}

					else 				//uncle is black
					{
						if (z==z->p->left)	//right-left
						{
							z=z->p;
							right_rotate(z);
						}

						z->p->color=BLACK;	//right-right
						z->p->p->color=RED;
						left_rotate(z->p->p);
					}
				}
			}

			root->color=BLACK;
		}

		void insert(int val)
		{
			node *z=new node(val);

			node *y=NULL;
			node *x=root;

			while(x->key!=NIL)
			{
				y=x;
				if(z->key<x->key)
				x=x->left;
				else x=x->right;
			}

			if(y==NULL)
            {
                z->p = root;
                root = z;
            }
            else
            {
                z->p = y;

                if(z->key<y->key)
                {
                    delete y->left;
                    y->left=z;
                }
                else
                {
                    delete y->right;
                    y->right=z;
                }
            }

			z->left=new node(NIL);
			z->left->p = z;
			z->right=new node (NIL);
            z->right->p = z;

			z->color=RED;

			insert_fixup(z);
		}

		const char* getColor(int i)
		{
			switch (i)
			{
			case 0: return "RED";
			case 1: return "BLACK";
			}
		}

		/* Compute the "height" of a tree -- the number of
		nodes along the longest path from the root node
		down to the farthest leaf node.*/

		int height(node* node)
		{
			if (node->key==NIL)
			return 0;
			else
			{
				/* compute the height of each subtree */
				int lheight = height(node->left);
				int rheight = height(node->right);

				/* use the larger one */
				if (lheight > rheight)
				    return(lheight+1);
				else return(rheight+1);
			}
		}

		//Function to print level order traversal a tree
		void printLevelOrder(node* root)
		{
			int h = height(root);
			int i;
			for (i=1; i<=h; i++)
			{
				cout<<"\n";
				printGivenLevel(root, i);
			}
		}

		/* Print nodes at a given level */
		void printGivenLevel(node* root, int level)
		{
			if (root->key == NIL)
			return;
			if (level == 1)
			printf(" Key: %d, Color: %s, Parent: %d;", root->key, getColor(root->color), root->p->key);
			else if (level > 1)
			{
				printGivenLevel(root->left, level-1);
				printGivenLevel(root->right, level-1);
			}
		}

		// C function to search a given key in a given BST
		node* search(node* root, int val)
		{
			// Base Cases: root is null or key is present at root
			if (root->key == NIL || root->key == val)
			return root;

			// Key is greater than root's key
			if (root->key < val)
			return search(root->right, val);

			// Key is smaller than root's key
			return search(root->left, val);
		}

		void transplant(node *u, node *v)
		{
			if(u->p->key==NIL)
			root=v;

			else if (u==u->p->left)
			u->p->left=v;

			else u->p->right=v;

			v->p=u->p;
		}

		node* inorder(node *x)		//to find the inorder successor of x's parent
		{
			while(x->left->key!=NIL)
			x=x->left;

			return x;
		}

		void delete_fixup(node *x)
		{
			while((x!=root)&&(x->color==BLACK))
			{
				if(x==x->p->left)
				{
					node *s=x->p->right;

					if(s->color==RED)
					{
						s->color=BLACK;
						x->p->color=RED;
						left_rotate(x->p);
						s=x->p->right;
					}

					if(s->right->color==BLACK&&s->left->color==BLACK)
					{
						s->color=RED;
						x=x->p;
					}

					else
					{
						if(s->right->color==BLACK)
						{
							s->left->color=BLACK;
							s->color=RED;
							right_rotate(s);
							s=x->p->right;
						}

						s->color=x->p->color;
						x->p->color=BLACK;
						s->right->color=BLACK;
						left_rotate(x->p);
						x=root;
					}
				}

				else if(x==x->p->right)
				{
					node *s=x->p->left;

					if(s->color==RED)
					{
						s->color=BLACK;
						x->p->color=RED;
						right_rotate(x->p);
						s=x->p->left;
					}

					if(s->left->color==BLACK&&s->right->color==BLACK)
					{
						s->color=RED;
						x=x->p;
					}

					else
					{
						if(s->left->color==BLACK)
						{
							s->right->color=BLACK;
							s->color=RED;
							left_rotate(s);
							s=x->p->left;
						}

						s->color=x->p->color;
						x->p->color=BLACK;
						s->left->color=BLACK;
						right_rotate(x->p);
						x=root;
					}
				}
			}

			x->color=BLACK;
		}

		void delete_node(int val)
		{
			node *z=search(root,val);
			node *y=z;
			bool y_original_color=y->color;

            node *x;

            if (z->key == NIL)
            {
                x=root;
            }
            else if (z==root && z->left->key==NIL && z->right->key==NIL)
            {
                root=z->p;
                x=root;
                delete z->left;
                delete z->right;
                delete z;
            }
			else if(z->left->key==NIL)
			{
				x=z->right;
				transplant(z,x);
				delete z->left;
				delete z;
			}
			else if(z->right->key==NIL)
			{
				x=z->left;
				transplant(z,x);
				delete z->right;
				delete z;
			}

			else
			{
				node *y=inorder(z->right);
				y_original_color=y->color;
				x=y->right;
				/*if(y->p==z)
				x->p=y;

				else
				{
					transplant(y,y->right);
					y->right=z->right;
					y->right->p=y;
				}
				*/
				transplant(y,x);
				transplant(z,y);
				delete y->left;
				y->left=z->left;
                y->left->p=y;
				y->right=z->right;
				y->right->p=y;

				y->color=z->color;
				delete z;
			}

			if(y_original_color==BLACK)
			delete_fixup(x);
		}

		/*void traverse(node *q)		//inorder traversal
		{
			if(q!=0)
			{
				traverse(q->left);
				cout<<q->key<<" ";
				traverse(q->right);
			}
		}*/
};

int main()
{
	tree t;
	int ch, val;

	do	//10,12,20,5,1
	{
		cout<<"\n Choose one of the following options : ";
		cout<<"\n 1. Insert value";
		cout<<"\n 2. Delete value";
		cout<<"\n 3. Breadth-first traversal of tree";
		cout<<"\n 4. Exit";
		cout<<"\n\n Enter choice : ";
		cin>>ch;

		switch(ch)
		{
			case 1:
			cout<<"\n Enter value to be inserted : ";
			cin>>val;
			t.insert(val);
			break;

			case 2:
			cout<<"\n Enter value to be deleted : ";
			cin>>val;
			t.delete_node(val);
			break;

			case 3:
			//t.traverse(t.root);
			t.printLevelOrder(t.root);
			cout<<"\n\n";
			break;

			case 4:
			break;

		}
	} while(ch!=4);

	return 0;
}
