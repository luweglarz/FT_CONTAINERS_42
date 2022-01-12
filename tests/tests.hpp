#ifndef TESTS_H
#define TESTS_H

#include <vector>
#include <string>
#include "../containers/vector/ClassVector.hpp"
#include "../containers/map/ClassMap.hpp"
#include "../containers/stack/ClassStack.hpp"
#include "../containers/vector/ClassVector.hpp"
#include "colors.hpp"

void	vector_iterator_tests();
void	reverse_iterator_tests();

void	vector_modifiers_tests();
void	assign_tests();
void	push_back_tests();
void	pop_back_tests();
void	insert_tests();

template <class InputIterator, class T>
void	iota(InputIterator first, InputIterator last, T value){
	while (first != last){
		*first++ = value;
		value++;
	}
}
#endif