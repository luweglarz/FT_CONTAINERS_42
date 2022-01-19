#include "../tests.hpp"

void    stack_constructor_tests(){
    std::cout << "constructors unitest:" << std::endl;
    struct timeval	a1;
	struct timeval	b1;
	struct timeval	a2;
	struct timeval	b2;

    gettimeofday(&a1, NULL);
	std::stack<int>	stck1;
	gettimeofday(&b1, NULL);
	gettimeofday(&a2, NULL);
	ft::Stack<int>	stck2;
	gettimeofday(&b2, NULL);
    if (stck1.size() == stck2.size())
		std::cout << FGRN("[OK]");
	else
		std::cout << FRED("[KO]");
    std::cout << (b1.tv_usec - a1.tv_usec) / 1000 - (b2.tv_usec - a2.tv_usec) / 1000 << FYEL("MS ");
}