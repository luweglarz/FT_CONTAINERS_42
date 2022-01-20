#include "../tests.hpp"

void	vector_constructor_tests(){
    std::cout << "constructors unitest:" << std::endl;
	//Default constructor
    struct timeval	a1;
	struct timeval	b1;
	struct timeval	a2;
	struct timeval	b2;
    gettimeofday(&a1, NULL);
	std::vector<int>	vec1;
	gettimeofday(&b1, NULL);
	gettimeofday(&a2, NULL);
	ft::Vector<int>		vec2;
	gettimeofday(&b2, NULL);
    if (vec1.size() == vec2.size() && vec1.capacity() == vec2.capacity() && vec1.empty() == vec2.empty())
		std::cout << FGRN("[OK]");
	else
		std::cout << FRED("[KO]");
	std::cout << (b1.tv_usec - a1.tv_usec) / 1000 - (b2.tv_usec - a2.tv_usec) / 1000 << FYEL("MS ");

	//Fill constructor
    gettimeofday(&a1, NULL);
	std::vector<int>	vec3(100, 10);
	gettimeofday(&b1, NULL);
	gettimeofday(&a2, NULL);
	ft::Vector<int>		vec4(100, 10);
	gettimeofday(&b2, NULL);
    if (vec3.size() == vec4.size() && vec3.capacity() == vec4.capacity()){
		for (size_t i = 0; i < vec4.size(); i++){
			if (vec3[i] != vec4[i]){
				std::cout << FRED("[KO]");
				return ;
			}
		}
		std::cout << FGRN("[OK]");
	}	
	else
		std::cout << FRED("[KO]");
	std::cout << (b1.tv_usec - a1.tv_usec) / 1000 - (b2.tv_usec - a2.tv_usec) / 1000 << FYEL("MS ");

	//Range constructor
    gettimeofday(&a1, NULL);
	std::vector<int>	vec5(vec3.begin(), vec3.end());
	gettimeofday(&b1, NULL);
	gettimeofday(&a2, NULL);
	ft::Vector<int>		vec6(vec4.begin(), vec4.end());
	gettimeofday(&b2, NULL);
    if (vec5.size() == vec6.size() && vec5.capacity() == vec6.capacity()){
		for (size_t i = 0; i < vec6.size(); i++){
			if (vec5[i] != vec6[i]){
				std::cout << FRED("[KO]");
				return ;
			}
		}
		std::cout << FGRN("[OK]");
		
	}	
	else
		std::cout << FRED("[KO]");
	std::cout << (b1.tv_usec - a1.tv_usec) / 1000 - (b2.tv_usec - a2.tv_usec) / 1000 << FYEL("MS ");

	//Copy constructor
	gettimeofday(&a1, NULL);
	std::vector<int>	vec7(vec5);
	gettimeofday(&b1, NULL);
	gettimeofday(&a2, NULL);
	ft::Vector<int>		vec8(vec6);
	gettimeofday(&b2, NULL);
    if (vec7.size() == vec8.size() && vec7.capacity() == vec8.capacity()){
		for (size_t i = 0; i < vec8.size(); i++){
			if (vec7[i] != vec8[i]){
				std::cout << "vec8[i]: " << vec8[i] << std::endl;
				std::cout << FRED("[KO]");
				return ;
			}
		}
		std::cout << FGRN("[OK]");
		
	}	
	else
		std::cout << FRED("[KO]");
	std::cout << (b1.tv_usec - a1.tv_usec) / 1000 - (b2.tv_usec - a2.tv_usec) / 1000 << FYEL("MS ");
	std::cout << std::endl;
}