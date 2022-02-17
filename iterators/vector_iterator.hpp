#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

#include <iterator>

namespace ft
{
    /*-------------------------------------------------------
        vector_iterator (random_access_iterator)
    ---------------------------------------------------------*/
    template <class T>
    class vector_iterator{
        public:
            typedef typename    std::random_access_iterator_tag     iterator_category;
            typedef             T                                   value_type;
            typedef typename    std::ptrdiff_t                      difference_type;
            typedef             T                                   *pointer;
            typedef             T                                   &reference;

            vector_iterator(): _ptr(NULL){}
            vector_iterator(pointer p): _ptr(p){}
            vector_iterator(const vector_iterator &src){*this = src;}
            vector_iterator &operator=(const vector_iterator &src){_ptr = src._ptr;return(*this);}
            ~vector_iterator(){}

            pointer	base(void) const{
			    return (_ptr);
		    }

            //overloads
            reference   operator*()const {return (*_ptr);}
            pointer     operator->()const {return (_ptr);}
            T   &operator[](const int idx) const {return *(_ptr + idx);}

            vector_iterator operator+(const difference_type &add)const {return(vector_iterator(_ptr + add));}
            vector_iterator operator-(const difference_type &diff)const {return(vector_iterator(_ptr - diff));}
            vector_iterator operator*(const difference_type &factor)const {return(vector_iterator(_ptr * factor));}
            vector_iterator operator+=(const difference_type &add){_ptr += add; return(*this);}
            vector_iterator operator-=(const difference_type &diff){_ptr -= diff; return(*this);}
            vector_iterator operator*=(const difference_type &factor){_ptr *= factor; return(*this);}

            difference_type operator+(const vector_iterator<value_type> &add)const {return(_ptr + add._ptr);}
            difference_type operator-(const vector_iterator<value_type> &diff)const {return(_ptr - diff._ptr);}
            difference_type operator*(const vector_iterator<value_type> &factor)const {return(_ptr * factor._ptr);}
            
			friend vector_iterator	operator+(difference_type n, const vector_iterator& it) { return vector_iterator(it._ptr + n); }
			friend vector_iterator	operator-(difference_type n, const vector_iterator& it) { return vector_iterator(it._ptr - n); }

            vector_iterator &operator++(){++_ptr; return (*this);}//prefix
		    vector_iterator operator++(int){vector_iterator res; res._ptr = _ptr++; return(res);}
		    vector_iterator	&operator--(){--_ptr; return (*this);}//prefix
		    vector_iterator	operator--(int){vector_iterator res; res._ptr = _ptr--; return(res);}

            operator vector_iterator<const T>() const {
			return (vector_iterator<const T>(this->_ptr));
		    }

        private:
            pointer _ptr;
    };

    template<class a, class b>
    bool operator==(const vector_iterator<a> &rhs, const vector_iterator<b> &lhs){
            if (rhs.base() == lhs.base())
                return (true);
            return (false);
    }

    template<class a, class b>
    bool operator!=(const vector_iterator<a> &rhs, const vector_iterator<b> &lhs){
            if (rhs.base() != lhs.base())
                return (true);
            return (false);
    }

    template<class a, class b>
    bool operator>(const vector_iterator<a> &rhs, const vector_iterator<b> &lhs){
            if (rhs.base() > lhs.base())
                return (true);
            return (false);
    }

    template<class a, class b>
    bool operator>=(const vector_iterator<a> &rhs, const vector_iterator<b> &lhs){
            if (rhs.base() >= lhs.base())
                return (true);
            return (false);
    }

    template<class a, class b>
    bool operator<(const vector_iterator<a> &rhs, const vector_iterator<b> &lhs){
            if (rhs.base() < lhs.base())
                return (true);
            return (false);
    }

    template<class a, class b>
    bool operator<=(const vector_iterator<a> &rhs, const vector_iterator<b> &lhs){
            if (rhs.base() <= lhs.base())
                return (true);
            return (false);
    }
};

#endif