#ifndef TESTS_H
#define TESTS_H

#include <vector>
#include <stack>
#include <string>
#include <sys/time.h>
#include <ctime>
#include "../containers/vector/ClassVector.hpp"
#include "../containers/map/ClassMap.hpp"
#include "../containers/stack/ClassStack.hpp"
#include "../containers/vector/ClassVector.hpp"
#include "colors.hpp"

void	vector_iterator_tests();
void	reverse_iterator_tests();

void	vector_modifiers_tests();
void	vector_capacity_tests();
void    vector_element_access_tests();
void	vector_constructor_tests();

void    stack_constructor_tests();
void	stack_size_tests();
void	stack_modifier_tests();

template <class InputIterator, class T>
void	iota(InputIterator first, InputIterator last, T value){
	while (first != last){
		*first++ = value;
		++value;
	}
}
#endif