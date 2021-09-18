#pragma once 
#include <memory>
#include <iostream>

#include <algorithm>
#include <queue>

enum Color {Red, Black};

template<class P>
class Node
{
public:
    P     val;
    Color   color;
    Node<P>    *left, *right, *parent;
    
    Node(P val) : val(val)
    {
        parent = left = right =  NULL;
        this->color = Red;
    }
    Node<P> * max( void )	{	return ( right == NULL ) ? this : right->max() ;	}
	
	//Returns minimum value in subtree
	Node<P> * min( void )	{	return ( left == NULL ) ? this : left->min() ;	}

    Node<P> *uncle()
    {
        if (parent == NULL || parent->parent == NULL)
            return (NULL);
        if (parent->isOnLeft())
            return (parent->parent->right);
        else
            return (parent->parent->left);
    }
    bool isOnLeft() { return (this == parent->left) ;}

    Node<P> *sibling()
    {
        if (parent == NULL)
            return (NULL);
        if (isOnLeft())
            return (parent->right);
        return (parent->left);
    }

    void moveDown(Node<P> *nParent)
    {
        if (parent != NULL)
        {
            if (isOnLeft())
                parent->left = nParent;
            else
                parent->right = nParent;
        }   
        nParent->parent = parent;
        parent = nParent;
    }
    bool hasRedChild()
    {
        return ((left != NULL && left->color == Red) || (right != NULL && right->color == Red));
    }
};

template<class pair>
class RBT
{
    typedef pair P;


    Node<P> *root;

    void rotateLeft(Node<P> *x)
    {
        Node<P> *nParent = x->right;

        if (x == root)
            root = nParent;
        x->moveDown(nParent);
        x->right = nParent->left;
        if (nParent->left != NULL)
            nParent->left->parent = x;
        nParent->left = x;
    }

    void rotateRight(Node<P> *x)
    {
        Node<P> *nParent = x->left;
        if (x == root)
            root = nParent;
        x->moveDown(nParent);
        x->left = nParent->right;
        if (nParent->right != NULL)
            nParent->right->parent = x;
        nParent->right = x;

    }

    void swapColors(Node<P> *x1, Node<P> *x2)
    {
        Color temp;
        temp = x1->color;
        x1->color = x2->color;
        x2->color = temp;
    }

    void swapValues(Node<P> *u, Node<P> *v)
    {
	    P temp;
	    temp = u->val;
	    u->val = v->val;
	    v->val = temp;
    }

    void fixRed(Node<P> *x) {
    // if x is root color it Black and return
    if (x == root) {
      x->color = Black;
      return;
    }
 
    // initialize parent, grandparent, uncle
    Node<P> *parent = x->parent, *grandparent = parent->parent,
         *uncle = x->uncle();
 
    if (parent->color != Black) {
      if (uncle != NULL && uncle->color == Red) {
        // uncle Red, perform recoloring and recurse
        parent->color = Black;
        uncle->color = Black;
        grandparent->color = Red;
        fixRed(grandparent);
      } else {
        // Else perform LR, LL, RL, RR
        if (parent->isOnLeft()) {
          if (x->isOnLeft()) {
            // for left right
            swapColors(parent, grandparent);
          } else {
            rotateLeft(parent);
            swapColors(x, grandparent);
          }
          // for left left and left right
          rotateRight(grandparent);
        } else {
          if (x->isOnLeft()) {
            // for right left
            rotateRight(parent);
            swapColors(x, grandparent);
          } else {
            swapColors(parent, grandparent);
          }
 
          // for right right and right left
          rotateLeft(grandparent);
        }
      }
    }
  }

    Node<P> *successor(Node<P> *x)
    {
        Node<P> *temp = x;

        while (temp->left != NULL)
        {
            temp = temp->left;
        }
        return (temp);
    }

    Node<P> *BSTreplace(Node<P> *x)
    {
        if (x->left != NULL && x->right != NULL)
            return (successor(x->right));
        if (x->left == NULL && x->right == NULL)
            return (NULL);
        if (x->left != NULL)
            return (x->left);
        else
            return (x->right);
    }
    void    deleteNode(Node<P> *v)
    {
        Node<P> *u = BSTreplace(v);

        bool uvBlack = ((u == NULL || u->color == Black) && (v->color == Black));
        Node<P> *parent = v->parent;
        if (u == NULL)/*u is NULL therefore v is leaf*/
        {
            if (v == root)
               root = NULL;/*v is root, making root null*/
            else
            {
                if (uvBlack)/*u and v both Black*/
                    fixDoubleBlack(v);/*v is leaf, fix double Black at v*/
                else/*u or v is Red*/
                {
                    if (v->sibling() != NULL)/*sibling is not null, make it Red"*/
                        v->sibling()->color = Red;
                }
            }
                /*delete v from the tree*/
            if (v->isOnLeft())
                parent->left = NULL;
            else
                 parent->right = NULL;
            delete v;
            return;
        }
        if (v->left == NULL or v->right == NULL)
        {
            /* v has 1 child*/
            if (v == root)
            {
                /* v is root, assign the value of u to v, and delete u*/
                v->val = u->val;
                v->left = v->right = NULL;
                delete u;
            }
            else
            {
                if (v->isOnLeft())/* Detach v from tree and move u up*/
                    parent->left = u;
                else
                    parent->right = u;
                delete v;
                u->parent = parent;
                if (uvBlack)/* u and v both Black, fix double Black at u*/
                    fixDoubleBlack(u);
                else/* u or v Red, color u Black*/
                    u->color = Black;
            }
            return;
        }
        swapValues(u, v);
        deleteNode(u);
    }

    void fixDoubleBlack(Node<P> *x)
    {
        if (x == root)/* Reached root*/
            return;
 
        Node<P> *sibling = x->sibling(), *parent = x->parent;
        if (sibling == NULL)/*No sibiling, double Black pushed up*/
          fixDoubleBlack(parent);
        else
        {
            if (sibling->color == Red)/*Sibling Red*/
            {
                parent->color = Red;
                sibling->color = Red;
                if (sibling->isOnLeft())/*left case*/          
                    rotateRight(parent);
                else/*right case*/
                    rotateLeft(parent);
    
                fixDoubleBlack(x);
            }
            else/*Sibling Black*/
            {
                if (sibling->hasRedChild())/*at least 1 Red children*/
                {
          
                    if (sibling->left != NULL and sibling->left->color == Red)
                    {
                        if (sibling->isOnLeft())/*left left*/
                        {
                            sibling->left->color = sibling->color;
                            sibling->color = parent->color;
                            rotateRight(parent);
                        }
                        else/*right left*/
                        {
                            sibling->left->color = parent->color;
                            rotateRight(sibling);
                            rotateLeft(parent);
                        }
                    }
                    else
                    {
                        if (sibling->isOnLeft())/*left right*/
                        {
                            sibling->right->color = parent->color;
                            rotateLeft(sibling);
                            rotateRight(parent);
                        }
                        else/*right right*/
                        {
                            sibling->right->color = sibling->color;
                            sibling->color = parent->color;
                            rotateLeft(parent);
                        }
                    }
                    parent->color = Black;
                }
                else/*2 Black children*/
                {
                    sibling->color = Red;
                    if (parent->color == Black)
                        fixDoubleBlack(parent);
                    else
                        parent->color = Black;
                }
            }
        }
    }
    void levelOrder(Node<P> *x)
    {
        if (x == NULL)/*return if node<P> is null*/
            return ;
        std::queue<Node<P> *> q;/*queue for level order*/
        Node<P> *curr;
        /*push x*/
        q.push(x);
        while (!q.empty())/*while q is not empty*/
        {
            curr = q.front();
            q.pop();
            std::cout << curr->val << " ";/*print node<P> value*/
        /*push children to queue*/
            if (curr->left != NULL)
                q.push(curr->left);
            if (curr->right != NULL)
                q.push(curr->right);
        }
    }
    void inorder(Node<P> *x)
    {
        if (x == NULL)
            return;
        inorder(x->left);
        std::cout << x->val.first << " " << x->val.second << " ";
        inorder(x->right);
    }
public:


    
    Node<P> * begin( void )
    {
        if (root == NULL)
            return NULL;
        Node<P> *ret = root;
        while (ret->left)
            ret = ret->left;
        return (ret); 
    }
	Node<P> * end( void )
    {
        if (root == NULL)
            return NULL;
        Node<P> *ret = root;
        while (ret->right)
            ret = ret->right;
        return (ret); 
    }
	bool     empty( void ) const		{	return ( root == NULL ) ;	}

    RBT() { root = NULL; }
    /*searches for given value*/
    /*if found returns the node<P> (used for delete)*/
    /*else returns the last node<P> while traversing (used in insert)*/
    Node<P> *search(P n)
    {
        Node<P> *temp = root;
        while (temp != NULL)
        {
            if (n < temp->val)
            {
                if (temp->left == NULL)
                    break;
                else
                    temp = temp->left;
            }
            else if (n == temp->val)
                break;
            else
            {
                if (temp->right == NULL)
                    break;
                else
                    temp = temp->right;
            }
        }
        return temp;
    }
 
    /*inserts the given value to tree*/
    void insert(P n)
    {
        Node<P> *newNode= new Node<P>(n);
        if (root == NULL)/*when root is null*/
        {
            /*simply insert value at root*/
            newNode->color = Black;
            root = newNode;
        }
        else
        {
            Node<P> *temp = search(n);
            if (temp->val == n)/*return if value already exists*/
                return ;
      /*if value is not found, search returns the node*/
      /*where the value is to be inserted*/
      /*connect new node<P> to correct node*/
            newNode->parent = temp;
 
            if (n < temp->val)
                temp->left = newNode;
            else
                temp->right = newNode;
            /*fix Red Red voilaton if exists*/
            fixRed(newNode);
        }
    }
 
  /*utility function that deletes the node<P> with given value*/
    void deleteByVal(P n)
    {
        if (root == NULL)/*Tree is empty*/
            return;
        Node<P> *v = search(n), *u;
        std::cout << "HERE: "<< v->val<< "\n";
        if (v->val != n)
        {
            std::cout << "No node<P> found to delete with value:" << n << std::endl;
            return;
        }
        deleteNode(v);
    }
 
  /*prints inorder of the tree*/
    void printInOrder()
    {
        std::cout << "Inorder: " << std::endl;
        if (root == NULL)
            std::cout << "Tree is empty" << std::endl;
        else
            inorder(root);
        std::cout << std::endl;
    }
 
  /*prints level order of the tree*/
    void printLevelOrder()
    {
        std::cout << "Level order: " << std::endl;
        if (root == NULL)
            std::cout << "Tree is empty" << std::endl;
        else
            levelOrder(root);
        std::cout << std::endl;
    }
};
