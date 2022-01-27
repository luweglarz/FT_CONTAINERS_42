#ifndef STRUCT_RBT_HPP
# define STRUCT_RBT_HPP

#include <memory>

enum ncolor {BLACK, RED};

namespace ft
{
    template <class Pair>
    struct RBTNode{
    public:

        typedef Pair                        value_type;
        typedef struct RBTNode<value_type>  node;

        /*-------------------------------------------------------
        default constructor
        ---------------------------------------------------------*/
        RBTNode():color(BLACK), content(), parent(NULL),right(NULL), left(NULL){}

        /*-------------------------------------------------------
        constructor
        ---------------------------------------------------------*/
        RBTNode(ncolor col, Pair cont,struct RBTNode &par, struct RBTnode &r, struct RBTnode &l):
        color(col), content(cont), parent(par), right(r), left(l){}
    
        /*-------------------------------------------------------
        Destructor
        ---------------------------------------------------------*/
        ~RBTNode(){}
        RBTNode    &operator=(const RBTNode &other){
            color = other.color;
            content = other.content;
            parent = other.parent;
            right = other.right;
            left = other.left;
            return (*this);
        }

        /*-------------------------------------------------------
        Set node 
        ---------------------------------------------------------*/
        void set_node(ncolor col, node *par, node *r, node *l){
            color = col;
            parent = par;
            right = r;
            left = l;
        }

        ncolor          color;
        value_type      content;
        node            *parent, *right, *left;
    };
}


#endif