#include "tests/tests.hpp"

int main()
{
	vector_iterator_tests();
	std::cout << std::endl;
	reverse_iterator_tests();
	std::cout << std::endl;
	vector_modifiers_tests();
	std::cout << std::endl;
	vector_capacity_tests();
	return (0);
}
