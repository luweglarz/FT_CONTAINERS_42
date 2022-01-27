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
        RBTNode(ncolor col, Pair cont,pointer par, pointer r, pointer l):
        color(col), content(cont), parent(par), right(r), left(l){std::cout << "filecon\n";}

        /*-------------------------------------------------------
        fill constructor
        ---------------------------------------------------------*/
        // RBTNode(const RBTNode &other){
        //     *this = other;
        // }
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
        value_type      content;
        pointer         parent;
        pointer         right;
        pointer         left;
    };
}


#endif