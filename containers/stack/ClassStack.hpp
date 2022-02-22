#ifndef STACK_HPP
#define STACK_HPP
#include "../vector/ClassVector.hpp"

namespace ft
{
    template<class T, class Container = vector<T> >
    class stack{
    public:
        typedef Container                   container_type;
        typedef typename container_type::value_type  value_type;
        typedef typename container_type::size_type   size_type;
        typedef typename container_type::reference   reference;
        typedef typename container_type::const_reference   const_reference;

        explicit stack(const container_type &ctnr = container_type()): C(ctnr){
        }

        stack &operator=(const stack &other){
            C = other.C;
            return(*this);
        }

        ~stack(){
        }

        reference top(){
            return (C.back());
        }

        const_reference top() const{
            return (C.back());
        }

        bool    empty(){
            return (C.empty());
        }

        size_type size() const {
            return (C.size());
        }

        void    push(const value_type &value){
            C.push_back(value);
        }

        void    pop(){
            C.pop_back();
        }

    protected:
        container_type C;

        template<class T1, class Container1>
		friend bool	operator==(const stack<T1, Container1>&, const stack<T1, Container1>&);

		template<class T1, class Container1>
		friend bool	operator>(const stack<T1, Container1>&, const stack<T1, Container1>&);
    };

    template <class T, class Container>
    bool operator==(const ft::stack<T, Container> &lhs,
                    const ft::stack<T, Container> &rhs){return (lhs.C == rhs.C);}
    template <class T, class Container>
    bool operator!=(const ft::stack<T, Container> &lhs,
                    const ft::stack<T, Container> &rhs){return (!(lhs == rhs));}
    template <class T, class Container>
    bool operator>(const ft::stack<T, Container> &lhs,
                    const ft::stack<T, Container> &rhs){return (lhs.C > rhs.C);}
    template <class T, class Container>
    bool operator>=(const ft::stack<T, Container> &lhs,
                    const ft::stack<T, Container> &rhs){return (lhs == rhs || lhs > rhs);}
    template <class T, class Container>
    bool operator<(const ft::stack<T, Container> &lhs,
                    const ft::stack<T, Container> &rhs){return (rhs > lhs);}
   template <class T, class Container>
    bool operator<=(const ft::stack<T, Container> &lhs,
                    const ft::stack<T, Container> &rhs){return (rhs >= lhs);}

}

#endif