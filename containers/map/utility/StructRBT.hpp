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
    
        static pointer find_min(pointer right){
            while (right->left != NULL)
                right = right->left;
            return (right);
        }

        static pointer	find_max(pointer left) {
			while (left->right != NULL)
                left = left->right;
            return (left);
		}
    };
}


#endif