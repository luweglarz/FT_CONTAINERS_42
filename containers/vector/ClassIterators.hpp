#ifndef ITERATORS_HPP
# define ITERATORS_HPP

namespace ft
{
    /*-------------------------------------------------------
        Vector Iterator
    ---------------------------------------------------------*/
    template <class T>
    class vector_iterator : std::iterator<std::random_access_iterator_tag, T>{
        public:

            typedef typename vector_iterator::value_type *Tptr;
            vector_iterator(): _ptr(NULL){}
            vector_iterator(T *p): _ptr(p){}
            vector_iterator(const vector_iterator &src){*this = src;}
            vector_iterator &operator=(const vector_iterator &src){_ptr = src._ptr;return(*this);}
            ~vector_iterator(){}


            //overloads
            T   &operator*()const {return (*_ptr);}
            T   *operator->()const {return (_ptr);}
            T   &operator[](int idx) const {return *(_ptr + idx);}

            vector_iterator operator+(const vector_iterator &rhs)const {vector_iterator res(_ptr + rhs._ptr); return (res);}
            vector_iterator operator-(const vector_iterator &rhs)const {vector_iterator res(_ptr - rhs._ptr); return (res);}
            vector_iterator operator*(const vector_iterator &rhs)const {vector_iterator res(_ptr * rhs._ptr); return (res);}
        
            vector_iterator &operator++(){++_ptr; return (*this);}//prefix
		    vector_iterator operator++(int){vector_iterator res; res.ptr = _ptr++; return(res);}
		    vector_iterator	&operator--(){--_ptr; return (*this);}//prefix
		    vector_iterator	operator--(int){vector_iterator res; res.ptr = _ptr--; return(res);}

            bool operator==(const vector_iterator &rhs) const {
                if (_ptr == rhs._ptr)
                    return (true);
                return (false);
            }
            bool operator!=(const vector_iterator &rhs) const {
                if (_ptr != rhs._ptr)
                    return (true);
                return (false);
            }
        private:
            T *_ptr;
    };
};

#endif