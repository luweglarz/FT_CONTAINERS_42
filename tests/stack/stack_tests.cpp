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

void	stack_size_tests(){
	std::cout << "size unitest:" << std::endl;
    struct timeval	a1;
	struct timeval	b1;
	struct timeval	a2;
	struct timeval	b2;
	std::vector<int> vec1(10, 100);
	ft::Vector<int> vec2(10, 100);

    gettimeofday(&a1, NULL);
	std::stack<int, std::vector<int> >	stck1(vec1);
	stck1.pop();
	gettimeofday(&b1, NULL);
	gettimeofday(&a2, NULL);
	ft::Stack<int>	stck2(vec2);
	stck2.pop();
	gettimeofday(&b2, NULL);
	if (stck1.size() == stck2.size())
		std::cout << FGRN("[OK]");
	else
		std::cout << FRED("[KO]");
	std::cout << (b1.tv_usec - a1.tv_usec) / 1000 - (b2.tv_usec - a2.tv_usec) / 1000 << FYEL("MS ");
	gettimeofday(&a1, NULL);
	while (stck1.empty() == false){
		stck1.pop();
	}
	gettimeofday(&b1, NULL);
	gettimeofday(&a2, NULL);
	while (stck2.empty() == false){
		stck2.pop();
	}
	gettimeofday(&b2, NULL);
	if (stck2.empty() == true)
		std::cout << FGRN("[OK]");
	else
		std::cout << FRED("[KO]");
	std::cout << (b1.tv_usec - a1.tv_usec) / 1000 - (b2.tv_usec - a2.tv_usec) / 1000 << FYEL("MS ");
}

void	stack_modifier_tests(){
	std::cout << "modifier unitest:" << std::endl;
    struct timeval	a1;
	struct timeval	b1;
	struct timeval	a2;
	struct timeval	b2;
	std::vector<int> vec1(10, 100);
	ft::Vector<int> vec2(10, 100);

    gettimeofday(&a1, NULL);
	std::stack<int, std::vector<int> >	stck1(vec1);
	stck1.push(5);
	gettimeofday(&b1, NULL);
	gettimeofday(&a2, NULL);
	ft::Stack<int>	stck2(vec2);
	stck2.push(5);
	gettimeofday(&b2, NULL);
	if (stck1.size() == stck2.size() && stck1.top() == stck2.top())
		std::cout << FGRN("[OK]");
	else
		std::cout << FRED("[KO]");
	std::cout << (b1.tv_usec - a1.tv_usec) / 1000 - (b2.tv_usec - a2.tv_usec) / 1000 << FYEL("MS ");
	gettimeofday(&a1, NULL);
	stck1.pop();
	gettimeofday(&b1, NULL);
	gettimeofday(&a2, NULL);
	stck2.pop();
	gettimeofday(&b2, NULL);
	if (stck1.size() == stck2.size() && stck1.top() == stck2.top())
		std::cout << FGRN("[OK]");
	else
		std::cout << FRED("[KO]");
	std::cout << (b1.tv_usec - a1.tv_usec) / 1000 - (b2.tv_usec - a2.tv_usec) / 1000 << FYEL("MS ");
	
}