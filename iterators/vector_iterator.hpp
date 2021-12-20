#ifndef ITERATORS_HPP
# define ITERATORS_HPP

namespace ft
{
    /*-------------------------------------------------------
        vector_terator
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
            vector_iterator(T *p): _ptr(p){}
            vector_iterator(const vector_iterator &src){*this = src;}
            vector_iterator &operator=(const vector_iterator &src){_ptr = src._ptr;return(*this);}
            ~vector_iterator(){}


            //overloads
            T   &operator*()const {return (*_ptr);}
            T   *operator->()const {return (_ptr);}
            T   &operator[](int idx) const {return *(_ptr + idx);}

            vector_iterator operator+(const difference_type &add)const {return(vector_iterator(_ptr + add));}
            vector_iterator operator-(const difference_type &diff)const {return(vector_iterator(_ptr - diff));}
            vector_iterator operator*(const difference_type &factor)const {return(vector_iterator(_ptr * factor));}
            vector_iterator operator+=(const difference_type &add){_ptr += add; return(*this);}
            vector_iterator operator-=(const difference_type &diff){_ptr -= diff; return(*this);}
            vector_iterator operator*=(const difference_type &factor){_ptr *= factor; return(*this);}

            difference_type operator+(const vector_iterator &add)const {return(_ptr + add._ptr);}
            difference_type operator-(const vector_iterator &diff)const {return(_ptr - diff._ptr);}
            difference_type operator*(const vector_iterator &factor)const {return(_ptr * factor._ptr);}
        
            vector_iterator &operator++(){++_ptr; return (*this);}//prefix
		    vector_iterator operator++(int){vector_iterator res; res._ptr = _ptr++; return(res);}
		    vector_iterator	&operator--(){--_ptr; return (*this);}//prefix
		    vector_iterator	operator--(int){vector_iterator res; res._ptr = _ptr--; return(res);}

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
            pointer _ptr;
    };
};

#endif