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
        typedef value_type                  *val_pointer;
        typedef struct RBTNode<value_type>  node;
        typedef node                        *pointer;
        typedef const node                  *const_pointer;
        typedef node                        &reference;
        typedef const node                  &const_reference;

        /*-------------------------------------------------------
        default constructor
        ---------------------------------------------------------*/
        RBTNode():color(BLACK), content(), parent(NULL),right(NULL), left(NULL){}

        /*-------------------------------------------------------
        fill constructor
        ---------------------------------------------------------*/
        RBTNode(ncolor col, val_pointer cont,pointer par, pointer r, pointer l):
        color(col), content(cont), parent(par), right(r), left(l){}
        /*-------------------------------------------------------
        Destructor
        ---------------------------------------------------------*/
        ~RBTNode(){}

        /*-------------------------------------------------------
        Assignation operator
        ---------------------------------------------------------*/
        reference operator=(const_reference other){
            color = other.color;
            content = other.content;
            parent = other.parent;
            right = other.right;
            left = other.left;
            return (*this);
        }

        ncolor          color;
        val_pointer     content;
        pointer         parent;
        pointer         right;
        pointer         left;
    };

    template <class Pair, class Compare, class Alloc = std::allocator<RBTNode<Pair> > >
    class RBT{
    public:
        typedef Pair                                                value_type;
        typedef RBTNode<value_type>                                 node;
        typedef Compare                                             compare;
        typedef Alloc                                               allocator_type;
        typedef typename allocator_type::reference                  reference;
        typedef typename allocator_type::const_reference            const_reference;
        typedef typename allocator_type::pointer                    pointer;
        typedef typename allocator_type::const_pointer              const_pointer;

        pointer             root;
        pointer             first;
        pointer             last;
        compare             cmp;

        RBT():root(NULL), first(NULL), last(NULL){}
    
        pointer find_min(pointer right){
            while (right->left != NULL)
                right = right->left;
            return (right);
        }

        pointer	find_max(pointer left) {
			while (left->right != NULL)
                left = left->right;
            return (left);
		}

        void    rotate_left(pointer rot){
            pointer right = rot->right;
            rot->right = right->left;
            if (right->left != NULL)
                right->left->parent = rot;
            right->parent = rot->parent;
            if (rot->parent == NULL)
                root = right;
            else if (rot == rot->parent->left)
                rot->parent->left = right;
            else
                rot->parent->right = right;
            right->left = rot;
            rot->parent = right;
        }

        void    rotate_right(pointer rot){
            pointer left = rot->left;
            rot->left = left->right;
            if (left->right != NULL)
                left->right->parent = rot;
            left->parent = rot->parent;
            if (rot->parent == NULL)
                root = left;
            else if (rot == rot->parent->right)
                rot->parent->right = left;
            else
                rot->parent->left = left;
            left->right = rot;
            rot->parent = left;
        }

        void    transplant(pointer a, pointer b){
            if (a->parent == NULL)
                root = b;
            else if (a == a->parent->left)
                a->parent->left = b;
            else
                a->parent->right = b;
            b->parent = a->parent;
        }
    };
}


#endif