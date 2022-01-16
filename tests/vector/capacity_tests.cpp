#include "../tests.hpp"

void	size_tests(){
	std::cout << "size unitest:" << std::endl;
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
    vec1.clear();
    vec2.clear();
    if (vec1.size() == vec2.size() && vec1.capacity() == vec2.capacity())
		std::cout << FGRN("[OK]");
	else
		std::cout << FRED("[KO]");
}

void    max_size_tests(){
    std::cout << "max_size unitest:" << std::endl;
	std::vector<int>	vec1;
	ft::Vector<int>		vec2;

    if (vec1.max_size() == vec2.max_size())
		std::cout << FGRN("[OK]");
	else
		std::cout << FRED("[KO]");
}

void    resize_tests(){
    std::cout << "resize unitest:" << std::endl;
	std::vector<int>	vec1(10);
	ft::Vector<int>		vec2(10);

    vec1.resize(20);
    vec2.resize(20);
    if (vec1.size() == vec2.size() && vec1.capacity() == vec2.capacity())
		std::cout << FGRN("[OK]");
	else
		std::cout << FRED("[KO]");
    vec1.insert(vec1.begin() + 5, vec1.begin(), vec1.end());
    vec2.insert(vec2.begin() + 5, vec2.begin(), vec2.end());
    vec1.resize(50);
    vec2.resize(50);
    if (vec1.size() == vec2.size() && vec1.capacity() == vec2.capacity())
		std::cout << FGRN("[OK]");
	else
		std::cout << FRED("[KO]");
}

void	capacity_tests(){
	std::cout << "capacity unitest:" << std::endl;
	std::vector<int>	vec1;
	ft::Vector<int>		vec2;
	if (vec1.size() == vec2.size() && vec1.capacity() == vec2.capacity())
		std::cout << FGRN("[OK]");
	else
		std::cout << FRED("[KO]");
	for (int i = 0; i < 20; i++){
		vec1.push_back(10);
		vec2.push_back(10);
	}
	if (vec1.size() == vec2.size() && vec1.capacity() == vec2.capacity())
		std::cout << FGRN("[OK]");
	else
		std::cout << FRED("[KO]");
}

void	empty_tests(){
	std::cout << "empty unitest:" << std::endl;
	std::vector<int>	vec1;
	ft::Vector<int>		vec2;
	if (vec1.empty() == vec2.empty())
		std::cout << FGRN("[OK]");
	else
		std::cout << FRED("[KO]");
	for (int i = 0; i < 20; i++){
		vec1.push_back(10);
		vec2.push_back(10);
	}
	if (vec1.empty() == vec2.empty())
		std::cout << FGRN("[OK]");
	else
		std::cout << FRED("[KO]");
}

void	reserve_tests(){
	std::cout << "empty unitest:" << std::endl;
	std::vector<int>	vec1;
	ft::Vector<int>		vec2;
	vec1.reserve(20);
	vec2.reserve(20);
	if (vec1.size() == vec2.size() && vec1.capacity() == vec2.capacity())
		std::cout << FGRN("[OK]");
	else
		std::cout << FRED("[KO]");
	vec1.reserve(40);
	vec2.reserve(40);
	if (vec1.size() == vec2.size() && vec1.capacity() == vec2.capacity())
		std::cout << FGRN("[OK]");
	else
		std::cout << FRED("[KO]");
	vec1.reserve(0);
	vec2.reserve(0);
	if (vec1.size() == vec2.size() && vec1.capacity() == vec2.capacity())
		std::cout << FGRN("[OK]");
	else
		std::cout << FRED("[KO]");
}

void    vector_capacity_tests(){
    size_tests();
    std::cout << std::endl;
    max_size_tests();
    std::cout << std::endl;
    resize_tests();
	std::cout << std::endl;
	capacity_tests();
	std::cout << std::endl;
	empty_tests();
	std::cout << std::endl;
	reserve_tests();
}