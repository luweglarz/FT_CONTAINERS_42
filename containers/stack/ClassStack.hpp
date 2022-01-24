#ifndef STACK_HPP
#define STACK_HPP
#include "../vector/ClassVector.hpp"

namespace ft
{
    template<class T, class Container = vector<T> >
    class stack{
    public:
        /*-------------------------------------------------------
        Defining types with typedef
        ---------------------------------------------------------*/
        typedef Container                   container_type;
        typedef typename container_type::value_type  value_type;
        typedef typename container_type::size_type   size_type;
        typedef typename container_type::reference   reference;
        typedef typename container_type::const_reference   const_reference;

        //Constructors:
        /*-------------------------------------------------------
        Default constructor that creates an empty stack
        container_type: type of the underlying container
        ---------------------------------------------------------*/
        explicit stack(const container_type &ctnr = container_type()): C(ctnr){
        }

        /*-------------------------------------------------------
        Assignation operator from x
        x: the copied instance
        ---------------------------------------------------------*/
        stack &operator=(const stack &other){
            C = other.C;
            return(*this);
        }
        /*-------------------------------------------------------
        stack destructor
        ---------------------------------------------------------*/
        ~stack(){
        }

        //Element access
        /*-------------------------------------------------------
        top function returns the element at the top of the stack
        ---------------------------------------------------------*/
        reference top(){
            return (C.back());
        }

        const_reference top() const{
            return (C.back());
        }

        //Capacity
        /*-------------------------------------------------------
        empty function returns true if the underlying container 
        has no elements and false if it is not empty
        ---------------------------------------------------------*/
        bool    empty(){
            return (C.empty());
        }

        /*-------------------------------------------------------
        size function returns the size of the underlying container
        ---------------------------------------------------------*/
        size_type size() const {
            return (C.size());
        }

        //Modifiers
        /*-------------------------------------------------------
        push function that pushes an element into the stack
        value: value to be pushed into the stack
        ---------------------------------------------------------*/
        void    push(const value_type &value){
            C.push_back(value);
        }

        /*-------------------------------------------------------
        pop function that remove the element at the top of the stack
        ---------------------------------------------------------*/
        void    pop(){
            C.pop_back();
        }

    protected:
        container_type C;
    };
    /*-------------------------------------------------------
        Non-member operators overloads
    ---------------------------------------------------------*/
    template <class T, class Container>
    bool operator==(const ft::stack<T, Container> &lhs,
                    const ft::stack<T, Container> &rhs){return (lhs.C == rhs.C);}
    template <class T, class Container>
    bool operator!=(const ft::stack<T, Container> &lhs,
                    const ft::stack<T, Container> &rhs){return (lhs.C != rhs.C);}
    template <class T, class Container>
    bool operator>(const ft::stack<T, Container> &lhs,
                    const ft::stack<T, Container> &rhs){return (lhs.C > rhs.C);}
    template <class T, class Container>
    bool operator>=(const ft::stack<T, Container> &lhs,
                    const ft::stack<T, Container> &rhs){return (lhs.C >= rhs.C);}
    template <class T, class Container>
    bool operator<(const ft::stack<T, Container> &lhs,
                    const ft::stack<T, Container> &rhs){return (lhs.C < rhs.C);}
   template <class T, class Container>
    bool operator<=(const ft::stack<T, Container> &lhs,
                    const ft::stack<T, Container> &rhs){return (lhs.C <= rhs.C);}

}

#endif