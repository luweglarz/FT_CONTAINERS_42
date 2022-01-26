#include "tests/tests.hpp"

void	vector_tests(){
	std::cout << "Vector tests:" << std::endl << "_______________" << std::endl;
	vector_constructor_tests();
	std::cout << std::endl;
	vector_modifiers_tests();
	std::cout << std::endl;
	vector_capacity_tests();
	std::cout << std::endl;
	vector_element_access_tests();
	std::cout << std::endl;
	vector_non_members_function();
	std::cout << std::endl;
}

void	stack_tests(){
	std::cout << "Stack tests:" << std::endl << "_______________" << std::endl;
	stack_constructor_tests();
	std::cout << std::endl;
	stack_size_tests();
	std::cout << std::endl;
	stack_modifier_tests();
	std::cout << std::endl;
}

void	iterator_tests(){
	std::cout << "vector_iterator/reverse_iterator tests:" << std::endl << "_______________" << std::endl;
	vector_iterator_tests();
	std::cout << std::endl;
	reverse_iterator_tests();
	std::cout << std::endl;
}

int main()
{
	// iterator_tests();
	// vector_tests();
	// stack_tests();
	ft::map<char, int>	test;
	test.insert(ft::make_pair<char, int>('c', 5));
	ft::map<char, int>::iterator it = test.find('c');
	std::cout << test['c'] << std::endl;
	return (0);
}
