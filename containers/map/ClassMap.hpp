#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <memory>
#include <limits>
#include <stdexcept>
#include <functional>
#include "utility/pair.hpp"

namespace ft
{

    template < class Key, class T, class Compare = std::less<Key>,
				class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map{



    };
}

#endif