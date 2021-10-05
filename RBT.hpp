#ifndef RBT_HPP
#define RBT_HPP
#include <memory>
#include <iostream>

#include <algorithm>
#include <queue>
#include "Node.hpp"
#include "Iterator.hpp"

template< class pair, class Compare >
class RBT
{
public:

    typedef pair        value_type;
    typedef Node<value_type>     node;
    typedef node *      pointer;
    typedef node &      reference;
    typedef ptrdiff_t   difference_type;
    typedef size_t      size_type;
    typedef Compare     compare;
    typedef ft::rbtit<node, difference_type, pointer, reference> iterator;
    typedef ft::rbt_reverse_it<node, difference_type, pointer, reference> reverse_iterator;


    node *root;
    node *nil;


    RBT() 
    {   
        nil = new Node<value_type>();
        root = NULL;
    }

    void rotateLeft(node *x)
    {
        node *nParent = x->right;

        if (x == root)
            root = nParent;
        x->moveDown(nParent);
        x->right = nParent->left;
        if (nParent->left != NULL)
            nParent->left->parent = x;
        nParent->left = x;
    }

    void rotateRight(node *x)
    {
        node *nParent = x->left;
        if (x == root)
            root = nParent;
        x->moveDown(nParent);
        x->left = nParent->right;
        if (nParent->right != NULL)
            nParent->right->parent = x;
        nParent->right = x;

    }

    void swapColors(node *x1, node *x2)
    {
        Color temp;
        temp = x1->color;
        x1->color = x2->color;
        x2->color = temp;
    }




    void swapValues(node *u, node *v)
    {
	    value_type temp;
	    temp = u->val;
	    u->val = v->val;
	    v->val = temp;
    }



    void fixRed(node *x)
    {
    // if x is root color it Black and return
        if (x == root)
        {
            x->color = Black;
            return;
        }
        // initialize parent, grandparent, uncle
        node *parent = x->parent, *grandparent = parent->parent,
         *uncle = x->uncle();
        if (parent->color != Black)
        {
            if (uncle != NULL && uncle->color == Red)
            {
            // uncle Red, perform recoloring and recurse
                parent->color = Black;
                uncle->color = Black;
                grandparent->color = Red;
                fixRed(grandparent);
            }
            else
            {
            // Else perform LR, LL, RL, RR
                if (parent->isOnLeft())
                {
                    if (x->isOnLeft())
                        swapColors(parent, grandparent);// for left right
                    else
                    {
                        rotateLeft(parent);
                        swapColors(x, grandparent);
                    }
                    rotateRight(grandparent); // for left left and left right
                }
                else
                {
                    if (x->isOnLeft())
                    {
                        rotateRight(parent);// for right left
                        swapColors(x, grandparent);
                    }
                    else
                        swapColors(parent, grandparent);// for right right and right left
                    rotateLeft(grandparent);
                }
            }
        }
    }

    node *BSTreplace(node *x)
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
    void    deleteNode(node *v)
    {
        node *u = BSTreplace(v);

        bool uvBlack = ((u == NULL || u->color == Black) && (v->color == Black));
        node *parent = v->parent;
        if (u == NULL)/*u is NULL therefore v is leaf*/
        {
            if (v == root)
               root = NULL;/*v is root, making root NULL*/
            else
            {
                if (uvBlack)/*u and v both Black*/
                    fixDoubleBlack(v);/*v is leaf, fix double Black at v*/
                else/*u or v is Red*/
                {
                    if (v->sibling() != NULL)/*sibling is not NULL, make it Red"*/
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





    void fixDoubleBlack(node *x)
    {
        if (x == root)/* Reached root*/
            return;
 
        node *sibling = x->sibling(), *parent = x->parent;
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



    void levelOrder(node *x)
    {
        if (x == NULL)/*return if node is NULL*/
            return ;
        std::queue<node *> q;/*queue for level order*/
        node *curr;
        /*push x*/
        q.push(x);
        while (!q.empty())/*while q is not empty*/
        {
            curr = q.front();
            q.pop();
            std::cout << curr->val << " ";/*print node value*/
        /*push children to queue*/
            if (curr->left != NULL)
                q.push(curr->left);
            if (curr->right != NULL)
                q.push(curr->right);
        }
    }



    void inorder(node *x)
    {
        if (x == NULL)
            return;
        inorder(x->left);
        std::cout << x->val.first << " " << x->val.second << " ";
        inorder(x->right);
    }
public:



    iterator begin( void ) //    typedef ft::treeit<node , Compare> iterator;
    {

        if (root == NULL)
        {
            return iterator(nil);
        }

        node *ret = root;
        while (ret->left)
        {
            ret = ret->left;
        }
        return (iterator(ret)); 
    }

	iterator end( void )
    {
        if (root == NULL)
            return (iterator(nil));
        // node *ret = root;
        

        // while (ret->right != NULL)
        //     ret = ret->right;
        // ret = ret->right;
        return (iterator(nil)); 
    }

    reverse_iterator    rbegin(void)
    {
        if (root == NULL)
            return (reverse_iterator(nil));
        node *ret = root;
        while (ret->right)
            ret = ret->right;
        // ret = ret->right;
        return (reverse_iterator(ret)); 
    }

	reverse_iterator rend( void )
    {
        if (root == NULL)
            return (reverse_iterator(nil));
        // node *ret = root;
        // while (ret->left)
        //     ret = ret->left;
        return (reverse_iterator(nil)); 
    }

	bool     empty( void ) const		{	return ( root == NULL ) ;	}


    /*searches for given value*/
    /*if found returns the node (used for delete)*/
    /*else returns the last node while traversing (used in insert)*/
    node *search(value_type n)
    {
        node *temp = root;
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
 

                         
        // std::cout <<std::addressof(NULL) <<  " post new:"<<'\n';



    /*inserts the given value to tree*/
    void insert(value_type n)
    {
       
        
        node *newNode= new Node<value_type>(n);
    // std::cout << std::addressof(nil->root)<< "Here\n";
        
        if (root == NULL)/*when root is NULL*/
        {
            /*simply insert value at root*/
            newNode->color = Black;
            root = newNode;
            root->knowroot(&root, &nil);
            // std::cout << std::addressof(root)<< "Here\n";

            nil->knowroot(&root, &nil);
            // std::cout << std::addressof(nil->root)<< "Here\n";


        }
        else
        {
            node *temp = search(n);
            if (temp->val == n)
            {
                delete newNode;/*return if value already exists*/
                return ;
            }
      /*if value is not found, search returns the node*/
      /*where the value is to be inserted*/
      /*connect new node to correct node*/
            newNode->parent = temp;
 
            if (n < temp->val)
            {
                temp->left = newNode;
                newNode->knowroot(&root, &nil);

            }
            else
            {
                temp->right = newNode;
                newNode->knowroot(&root, &nil);


            }
            /*fix Red Red voilaton if exists*/
            fixRed(newNode);
        }
    }
 
  /*utility function that deletes the node with given value*/
    void deleteByVal(value_type n)
    {
        if (root == NULL)/*Tree is empty*/
            return;
        node *v = search(n), *u;
        std::cout << "HERE: "<< v->val<< "\n";
        if (v->val != n)
        {
            std::cout << "No node found to delete with value:" << n << std::endl;
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
#endif