#include "../tests.hpp"

void    vector_non_members_function(){
    std::cout << "non_member_swap unitest:" << std::endl;
	//Test on empty vectors
	std::vector<int>	vec1;
	ft::vector<int>		vec2;
    std::vector<int>	vec3(10, 100);
	ft::vector<int>		vec4(10, 100);
	struct timeval	a1;
	struct timeval	b1;
	struct timeval	a2;
	struct timeval	b2;
	gettimeofday(&a1, NULL);
	std::swap(vec1, vec3);
	gettimeofday(&b1, NULL);
	gettimeofday(&a2, NULL);
	ft::swap(vec2, vec4);
	gettimeofday(&b2, NULL);
	if (vec1.size() == vec2.size() && vec1.capacity() == vec2.capacity() &&
        vec3.size() == vec4.size() && vec3.capacity() == vec4.capacity()){
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
	std::cout << std::endl;
	std::cout << "non_member_operators unitest:" << std::endl;
	std::vector<int>  vec1c(vec1);
	ft::vector<int>	  vec2c(vec2);
	bool res1 = vec1 == vec1c;
	bool res2 = vec2 == vec2c;
	if (res1 == res2)
		std::cout << FGRN("[OK]");
	else
		std::cout << FRED("[KO]");
	res1 = vec1 != vec1c;
	res2 = vec2 != vec2c;
	if (res1 == res2)
		std::cout << FGRN("[OK]");
	else
		std::cout << FRED("[KO]");
	res1 = vec1 < vec1c;
	res2 = vec2 < vec2c;
	if (res1 == res2)
		std::cout << FGRN("[OK]");
	else
		std::cout << FRED("[KO]");
	res1 = vec1 <= vec1c;
	res2 = vec2 <= vec2c;
	if (res1 == res2)
		std::cout << FGRN("[OK]");
	else
		std::cout << FRED("[KO]");
	res1 = vec1 > vec1c;
	res2 = vec2 > vec2c;
	if (res1 == res2)
		std::cout << FGRN("[OK]");
	else
		std::cout << FRED("[KO]");
	res1 = vec1 >= vec1c;
	res2 = vec2 >= vec2c;
	if (res1 == res2)
		std::cout << FGRN("[OK]");
	else
		std::cout << FRED("[KO]");
	std::cout << std::endl;
}