#ifndef NODE_HPP
#define NODE_HPP



enum Color {Red, Black};


template<class P>
class Node
{
public:

    typedef P value_type;

    P     val;
    Color   color;
    Node<P>    *left, *right, *parent;
    Node<P>    **root;
    Node<P>    **nilp;
    int         nil;
 
    Node(P val) : val(val)
    {
        parent = left = right =  NULL;
        this->color = Red;
    }
    Node ()
    {
        nil = 1;
        parent = left = right =  NULL;
        this->color = Black;
    }

    void    knowroot( Node<P> **rt, Node<P> **nill)
    {
        root = rt;
        nilp = nill;
        // std::cout << std::addressof(*rt)<< "egHere\n";
        // std::cout << std::addressof(*root)<< "egHere\n";

        // std::cout << (*root)->val.first << " what should be\n";
    }



    
    const bool is_a_left_son( void ) const	{	return ( parent != NULL ) && ( parent->left == this ) ;		}
	const bool is_a_right_son( void ) const	{	return ( parent != NULL ) && ( parent->right == this ) ;	}

    Node<P> * max( void )	{	return ( right == NULL ) ? this : right->max() ;	}
	
	//Returns minimum value in subtree
	Node<P> * min( void )	{	return ( left == NULL ) ? this : left->min() ;	}
	
	//Returns successor 
	Node<P> * successor( void ) {
		
		// check if this node has a right subtree:
		if ( right != NULL )
			return right->min() ;

		// check if this node is a left son:
		if ( is_a_left_son() )
			return parent ;
		
		// node does NOT have a right subtree and is NOT a left son.
		// search for the next ancestor which is a left son:
		Node<P> * succ = this ;
		do { 
			succ = succ->parent ; 
		}while ( ( succ != NULL ) && succ->is_a_right_son() ) ;
		if ( succ != NULL )
			return succ->parent ;
		else
			return NULL ;
		return NULL;
	}

    	Node<P> * predecessor( void )
        {
            //check if the node has a left subtree

            if(left!=NULL)
                return left->max();
            //check if node is a right son
            if(is_a_right_son())
                return parent;
            //if node does NOT have a left subtree and is NOT a right son
            Node<P> *pred= this;
            do{
                pred=pred->parent;
            }while(pred!=NULL && pred->is_a_left_son());
            
            if(pred!=NULL)
                return pred->parent;
            else
                return NULL;
        
            return NULL;
        }





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


#endif