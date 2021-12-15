#ifndef ITERATOR_TRAIT
# define ITERATOR_TRAIT


template<typename Iter>
struct iterator_traits{
    typedef typename Iter::difference_type      difference_type;
    typedef typename Iter::value_type           value_type;
    typedef typename Iter::pointer              pointer;
    typedef typename Iter::reference            reference;
    typedef typename Iter::iterator_category    iterator_category;
};

template <typename T>
struct iterator_traits<T*>{
    typedef std::random_access_iterator_tag     iterator_category;
    typedef T                                   value_type;
    typedef T*                                  pointer;
    typedef T&                                  reference;
    typedef std::ptrdiff_t                      difference_type;
};


#endif