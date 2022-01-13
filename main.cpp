#include "tests/tests.hpp"


void	vector_capacity_tests(){
	std::cout << "Size unitest:" << std::endl;
	std::vector<int>	vec1;
	ft::Vector<int>		vec2;

	if (vec1.size() == vec2.size() && vec1.capacity() == vec2.capacity())
		std::cout << FGRN("[OK]");
	else
		std::cout << FRED("[KO]");
	vec1.insert(vec1.begin(), 10);
	vec2.insert(vec2.begin(), 10);
	if (vec1.size() == vec2.size() && vec1.capacity() == vec2.capacity())
		std::cout << FGRN("[OK]");
	else
		std::cout << FRED("[KO]");
}


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
