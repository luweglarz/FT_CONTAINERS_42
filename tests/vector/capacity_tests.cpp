#include "../tests.hpp"

void	size_tests(){
	std::cout << "size unitest:" << std::endl;
	std::vector<int>	vec1;
	ft::Vector<int>		vec2;
	struct timeval	a1;
	struct timeval	b1;
	struct timeval	a2;
	struct timeval	b2;

	gettimeofday(&a1, NULL);
	vec1.size();
	gettimeofday(&b1, NULL);
	gettimeofday(&a2, NULL);
	vec2.size();
	gettimeofday(&b2, NULL);
	if (vec1.size() == vec2.size() && vec1.capacity() == vec2.capacity())
		std::cout << FGRN("[OK]");
	else
		std::cout << FRED("[KO]");
	std::cout << (b1.tv_usec - a1.tv_usec) / 1000 - (b2.tv_usec - a2.tv_usec) / 1000 << FYEL("MS ");
	vec1.insert(vec1.begin(), 10);
	vec2.insert(vec2.begin(), 10);
	gettimeofday(&a1, NULL);
	vec1.size();
	gettimeofday(&b1, NULL);
	gettimeofday(&a2, NULL);
	vec2.size();
	gettimeofday(&b2, NULL);
	if (vec1.size() == vec2.size() && vec1.capacity() == vec2.capacity())
		std::cout << FGRN("[OK]");
	else
		std::cout << FRED("[KO]");
	std::cout << (b1.tv_usec - a1.tv_usec) / 1000 - (b2.tv_usec - a2.tv_usec) / 1000 << FYEL("MS ");
    vec1.clear();
    vec2.clear();
	gettimeofday(&a1, NULL);
	vec1.size();
	gettimeofday(&b1, NULL);
	gettimeofday(&a2, NULL);
	vec2.size();
	gettimeofday(&b2, NULL);
    if (vec1.size() == vec2.size() && vec1.capacity() == vec2.capacity())
		std::cout << FGRN("[OK]");
	else
		std::cout << FRED("[KO]");
	std::cout << (b1.tv_usec - a1.tv_usec) / 1000 - (b2.tv_usec - a2.tv_usec) / 1000 << FYEL("MS ");
	std::vector<int>	vec3(1000, 1000);
	ft::Vector<int>		vec4(1000, 1000);
	gettimeofday(&a1, NULL);
	vec3.size();
	gettimeofday(&b1, NULL);
	gettimeofday(&a2, NULL);
	vec4.size();
	gettimeofday(&b2, NULL);
	if (vec1.size() == vec2.size() && vec1.capacity() == vec2.capacity())
		std::cout << FGRN("[OK]");
	else
		std::cout << FRED("[KO]");
	std::cout << (b1.tv_usec - a1.tv_usec) / 1000 - (b2.tv_usec - a2.tv_usec) / 1000 << FYEL("MS ");
}

void    max_size_tests(){
    std::cout << "max_size unitest:" << std::endl;
	std::vector<int>	vec1;
	ft::Vector<int>		vec2;
	struct timeval	a1;
	struct timeval	b1;
	struct timeval	a2;
	struct timeval	b2;

	gettimeofday(&a1, NULL);
	vec1.max_size();
	gettimeofday(&b1, NULL);
	gettimeofday(&a2, NULL);
	vec2.max_size();
	gettimeofday(&b2, NULL);
    if (vec1.max_size() == vec2.max_size())
		std::cout << FGRN("[OK]");
	else
		std::cout << FRED("[KO]");
	std::cout << (b1.tv_usec - a1.tv_usec) / 1000 - (b2.tv_usec - a2.tv_usec) / 1000 << FYEL("MS ");
}

void    resize_tests(){
    std::cout << "resize unitest:" << std::endl;
	std::vector<int>	vec1(10);
	ft::Vector<int>		vec2(10);
	struct timeval	a1;
	struct timeval	b1;
	struct timeval	a2;
	struct timeval	b2;

    gettimeofday(&a1, NULL);
	vec1.resize(500);
	gettimeofday(&b1, NULL);
	gettimeofday(&a2, NULL);
	vec2.resize(500);
	gettimeofday(&b2, NULL);
    if (vec1.size() == vec2.size() && vec1.capacity() == vec2.capacity())
		std::cout << FGRN("[OK]");
	else
		std::cout << FRED("[KO]");
	std::cout << (b1.tv_usec - a1.tv_usec) / 1000 - (b2.tv_usec - a2.tv_usec) / 1000 << FYEL("MS ");
    vec1.insert(vec1.begin() + 5, vec1.begin(), vec1.end());
    vec2.insert(vec2.begin() + 5, vec2.begin(), vec2.end());
    gettimeofday(&a1, NULL);
	vec1.resize(1000);
	gettimeofday(&b1, NULL);
	gettimeofday(&a2, NULL);
	vec2.resize(1000);
	gettimeofday(&b2, NULL);
    if (vec1.size() == vec2.size() && vec1.capacity() == vec2.capacity())
		std::cout << FGRN("[OK]");
	else
		std::cout << FRED("[KO]");
	std::cout << (b1.tv_usec - a1.tv_usec) / 1000 - (b2.tv_usec - a2.tv_usec) / 1000 << FYEL("MS ");
}

void	capacity_tests(){
	std::cout << "capacity unitest:" << std::endl;
	std::vector<int>	vec1;
	ft::Vector<int>		vec2;
	struct timeval	a1;
	struct timeval	b1;
	struct timeval	a2;
	struct timeval	b2;

	gettimeofday(&a1, NULL);
	vec1.capacity();
	gettimeofday(&b1, NULL);
	gettimeofday(&a2, NULL);
	vec2.capacity();
	gettimeofday(&b2, NULL);
	if (vec1.size() == vec2.size() && vec1.capacity() == vec2.capacity())
		std::cout << FGRN("[OK]");
	else
		std::cout << FRED("[KO]");
	std::cout << (b1.tv_usec - a1.tv_usec) / 1000 - (b2.tv_usec - a2.tv_usec) / 1000 << FYEL("MS ");
	for (int i = 0; i < 20; i++){
		vec1.push_back(10);
		vec2.push_back(10);
	}
	gettimeofday(&a1, NULL);
	vec1.capacity();
	gettimeofday(&b1, NULL);
	gettimeofday(&a2, NULL);
	vec2.capacity();
	gettimeofday(&b2, NULL);
	if (vec1.size() == vec2.size() && vec1.capacity() == vec2.capacity())
		std::cout << FGRN("[OK]");
	else
		std::cout << FRED("[KO]");
	std::cout << (b1.tv_usec - a1.tv_usec) / 1000 - (b2.tv_usec - a2.tv_usec) / 1000 << FYEL("MS ");
}

void	empty_tests(){
	std::cout << "empty unitest:" << std::endl;
	std::vector<int>	vec1;
	ft::Vector<int>		vec2;
	struct timeval	a1;
	struct timeval	b1;
	struct timeval	a2;
	struct timeval	b2;

	gettimeofday(&a1, NULL);
	vec1.empty();
	gettimeofday(&b1, NULL);
	gettimeofday(&a2, NULL);
	vec2.empty();
	gettimeofday(&b2, NULL);
	if (vec1.empty() == vec2.empty())
		std::cout << FGRN("[OK]");
	else
		std::cout << FRED("[KO]");
	std::cout << (b1.tv_usec - a1.tv_usec) / 1000 - (b2.tv_usec - a2.tv_usec) / 1000 << FYEL("MS ");
	for (int i = 0; i < 20; i++){
		vec1.push_back(10);
		vec2.push_back(10);
	}
	gettimeofday(&a1, NULL);
	vec1.empty();
	gettimeofday(&b1, NULL);
	gettimeofday(&a2, NULL);
	vec2.empty();
	gettimeofday(&b2, NULL);
	if (vec1.empty() == vec2.empty())
		std::cout << FGRN("[OK]");
	else
		std::cout << FRED("[KO]");
	std::cout << (b1.tv_usec - a1.tv_usec) / 1000 - (b2.tv_usec - a2.tv_usec) / 1000 << FYEL("MS ");
}

void	reserve_tests(){
	std::cout << "reserve unitest:" << std::endl;
	std::vector<int>	vec1;
	ft::Vector<int>		vec2;
	struct timeval	a1;
	struct timeval	b1;
	struct timeval	a2;
	struct timeval	b2;

	gettimeofday(&a1, NULL);
	vec1.reserve(20);
	gettimeofday(&b1, NULL);
	gettimeofday(&a2, NULL);
	vec2.reserve(20);
	gettimeofday(&b2, NULL);
	if (vec1.size() == vec2.size() && vec1.capacity() == vec2.capacity())
		std::cout << FGRN("[OK]");
	else
		std::cout << FRED("[KO]");
	std::cout << (b1.tv_usec - a1.tv_usec) / 1000 - (b2.tv_usec - a2.tv_usec) / 1000 << FYEL("MS ");
	gettimeofday(&a1, NULL);
	vec1.reserve(40);
	gettimeofday(&b1, NULL);
	gettimeofday(&a2, NULL);
	vec2.reserve(40);
	gettimeofday(&b2, NULL);
	if (vec1.size() == vec2.size() && vec1.capacity() == vec2.capacity())
		std::cout << FGRN("[OK]");
	else
		std::cout << FRED("[KO]");
	std::cout << (b1.tv_usec - a1.tv_usec) / 1000 - (b2.tv_usec - a2.tv_usec) / 1000 << FYEL("MS ");
	gettimeofday(&a1, NULL);
	vec1.reserve(0);
	gettimeofday(&b1, NULL);
	gettimeofday(&a2, NULL);
	vec2.reserve(0);
	gettimeofday(&b2, NULL);
	if (vec1.size() == vec2.size() && vec1.capacity() == vec2.capacity())
		std::cout << FGRN("[OK]");
	else
		std::cout << FRED("[KO]");
	std::cout << (b1.tv_usec - a1.tv_usec) / 1000 - (b2.tv_usec - a2.tv_usec) / 1000 << FYEL("MS ");
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