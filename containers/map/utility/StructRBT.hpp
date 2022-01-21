#ifndef STRUCT_RBT_HPP
# define STRUCT_RBT_HPP

enum ncolor {BLACK, RED};

namespace ft
{
    template <class Pair>
    struct RBTN{
    public:

        RBTN():color(BLACK), content(), parent(NULL),right(NULL), left(NULL){}
        ~RBTN(){}
        RBTN    &operator=(const RBTN &other){
            color = other.color;
            content = other.content;
            parent = other.parent;
            right = other.right;
            left = other.left;
            return (*this);
        }

        ncolor        color;
        Pair          content;
        struct RBTN   *parent, *right, *left;
    };
}


#endif