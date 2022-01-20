#include "../tests.hpp"

void	size_tests(){
	std::cout << "size unitest:" << std::endl;
	//Test on empty vector
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

	//Test on vector of size 1
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

	//Test on cleared vector
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

	//Test on huge vector size
	std::vector<int>	vec3(10000, 1000);
	ft::Vector<int>		vec4(10000, 1000);
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
	//Basic test
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
	//Test on empty vector
	std::vector<int>	vec1;
	ft::Vector<int>		vec2;
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
    if (vec1.size() == vec2.size() && vec1.capacity() == vec2.capacity()){
		for (size_t i = 0; i < vec2.size(); i++){
			if (vec1[i] != vec2[i]){
				std::cout << FRED("[KO]");
				return ;
			}
		}
		std::cout << FGRN("[OK]");
	}	
	else
		std::cout << FRED("[KO]");
	std::cout << (b1.tv_usec - a1.tv_usec) / 1000 - (b2.tv_usec - a2.tv_usec) / 1000 << FYEL("MS ");

	//Test with bigger size
    gettimeofday(&a1, NULL);
	vec1.resize(1000);
	gettimeofday(&b1, NULL);
	gettimeofday(&a2, NULL);
	vec2.resize(1000);
	gettimeofday(&b2, NULL);
    if (vec1.size() == vec2.size() && vec1.capacity() == vec2.capacity()){
		for (size_t i = 0; i < vec2.size(); i++){
			if (vec1[i] != vec2[i]){
				std::cout << FRED("[KO]");
				return ;
			}
		}
		std::cout << FGRN("[OK]");
	}	
	else
		std::cout << FRED("[KO]");
	std::cout << (b1.tv_usec - a1.tv_usec) / 1000 - (b2.tv_usec - a2.tv_usec) / 1000 << FYEL("MS ");

	//Test with a resize smaller than current size
	gettimeofday(&a1, NULL);
	vec1.resize(20);
	gettimeofday(&b1, NULL);
	gettimeofday(&a2, NULL);
	vec2.resize(20);
	gettimeofday(&b2, NULL);
    if (vec1.size() == vec2.size() && vec1.capacity() == vec2.capacity()){
		for (size_t i = 0; i < vec2.size(); i++){
			if (vec1[i] != vec2[i]){
				std::cout << FRED("[KO]");
				return ;
			}
		}
		std::cout << FGRN("[OK]");
	}	
	else
		std::cout << FRED("[KO]");
	std::cout << (b1.tv_usec - a1.tv_usec) / 1000 - (b2.tv_usec - a2.tv_usec) / 1000 << FYEL("MS ");
}

void	capacity_tests(){
	std::cout << "capacity unitest:" << std::endl;
	//Test on empty vector
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

	//Test on push_back vector
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
	//Test on empty vector
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

	//Test on Filled vector
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
	//Test on empty vector
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

	//Test with higer reserve than actual capacity
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

	//Try with reserve 0
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
	std::cout << std::endl;
}