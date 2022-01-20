#include "../tests.hpp"

void    operator_access_tests(){
    std::cout << "operator[] unitest:" << std::endl;
	//Test on filled vector
	std::vector<int>	vec1(50, 23);
	ft::Vector<int>		vec2(50, 23);
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

	//Test on cleared vector
	vec1.clear();
	vec2.clear();
	if (vec1[0] != vec2[0]){
		std::cout << FRED("[KO]");
		return ;
	}
	std::cout << FGRN("[OK]");
}

void	at_tests(){
	std::cout << "at unitest:" << std::endl;
	//Test on filled vector
	std::vector<int>	vec1(50, 23);
	ft::Vector<int>		vec2(50, 23);
	if (vec1.size() == vec2.size() && vec1.capacity() == vec2.capacity()){
		for (size_t i = 0; i < vec2.size(); i++){
			if (vec1.at(i) != vec2.at(i)){
				std::cout << FRED("[KO]");
				return ;
			}
		}
		std::cout << FGRN("[OK]");
	}	
	else
		std::cout << FRED("[KO]");

	//Test on cleared vector
	vec1.clear();
	vec2.clear();
	try{
		vec2.at(0);
		std::cout << FRED("[KO]");
	}
	catch(std::exception &e){
		(void)e;
		std::cout << FGRN("[OK]");
	}
}

void	front_tests(){
	std::cout << "front unitest:" << std::endl;
	//Test on filled vector
	std::vector<int>	vec1(50, 23);
	ft::Vector<int>		vec2(50, 23);
	if (vec1.front() != vec2.front())
		std::cout << FRED("[KO]");
	else
		std::cout << FGRN("[OK]");

	//Test on cleared vector
	vec1.clear();
	vec2.clear();
	if (vec1.front() != vec2.front())
		std::cout << FRED("[KO]");
	else
		std::cout << FGRN("[OK]");
}

void	back_tests(){
	std::cout << "back unitest:" << std::endl;
	//Test on filled vector
	std::vector<int>	vec1(50, 23);
	ft::Vector<int>		vec2(50, 23);
	if (vec1.front() != vec2.front())
		std::cout << FRED("[KO]");
	else
		std::cout << FGRN("[OK]");

	//Test on cleared vector
	vec1.clear();
	vec2.clear();
	if (vec1.front() != vec2.front())
		std::cout << FRED("[KO]");
	else
		std::cout << FGRN("[OK]");
}

void    vector_element_access_tests(){
    operator_access_tests();
    std::cout << std::endl;
	at_tests();
	std::cout << std::endl;
	front_tests();
	std::cout << std::endl;
	back_tests();
	std::cout << std::endl;
}