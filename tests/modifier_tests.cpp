#include "tests.hpp"

void	assign_tests(){
	std::cout << "Assign unitest:" << std::endl;
	//Test on empty vectors
	std::vector<int>	vec1;
	ft::Vector<int>		vec2;
	vec1.assign(10,100);
	vec2.assign(10,100);
	if (vec1.size() == vec2.size() && vec1.capacity() == vec2.capacity()){
		for (size_t i = 0; i < 10; i++){
			if (vec1[i] != vec2[i]){
				std::cout << FRED("[KO]");
				return ;
			}
		}
		std::cout << FGRN("[OK]");
	}	
	else
		std::cout << FRED("[KO]");
	//Test with iterator overload
	vec1.resize(50);
	vec2.resize(50);
	std::vector<int>::reverse_iterator revb1 = vec1.rbegin();
	std::vector<int>::reverse_iterator reve1 = vec1.rend();
	ft::Vector<int>::reverse_iterator revb2 = vec2.rbegin();
	ft::Vector<int>::reverse_iterator reve2 = vec2.rend();
	iota(vec1.begin(), vec1.end(), 1);
	iota(vec2.begin(), vec2.end(), 1);
	vec1.assign(revb1, reve1);
	vec2.assign(revb2, reve2);
	if (vec1.size() == vec2.size() && vec1.capacity() == vec2.capacity()){
		for (size_t i = 0; i < 10; i++){
			if (vec1[i] != vec2[i]){
				std::cout << FRED("[KO]");
				return ;
			}
		}
		std::cout << FGRN("[OK]");
	}	
	else
		std::cout << FRED("[KO]");

}

void	push_back_tests(){
	std::cout << "Push_back unitest:" << std::endl;
	std::vector<int>	vec1;
	ft::Vector<int>		vec2;
	//Test with empty vector
	vec1.push_back(1);
	vec2.push_back(1);
	if (vec1[0] == vec2[0] && vec1.size() == vec2.size() &&
		vec1.capacity() == vec2.capacity())
		std::cout << FGRN("[OK]");
	else
		std::cout << FRED("[KO]");
	//Test with vector of size 50
	vec1.resize(50);
	vec2.resize(50);
	iota(vec1.begin(), vec1.end(), 1);
	iota(vec2.begin(), vec2.end(), 1);
	vec1.push_back(1);
	vec2.push_back(1);
	if (vec1.size() == vec2.size() && vec1.capacity() == vec2.capacity()){
		for (size_t i = 0; i < 50; i++){
			if (vec1[i] != vec2[i]){
				std::cout << FRED("[KO]");
				return ;
			}
		}
		std::cout << FGRN("[OK]");
	}	
	else
		std::cout << FRED("[KO]");

}

void	pop_back_tests(){
	std::cout << "pop_back unitest:" << std::endl;
	std::vector<int>	vec1;
	ft::Vector<int>		vec2;
	//Test with empty vector
	vec1.pop_back();
	vec2.pop_back();
	if (vec1.capacity() == vec2.capacity())
		std::cout << FGRN("[OK]");
	else
		std::cout << FRED("[KO]");
	// //Test with vector of size 50
	// vec1.resize(50);
	// vec2.resize(50);
	// iota(vec1.begin(), vec1.end(), 1);
	// iota(vec2.begin(), vec2.end(), 1);
	// vec1.pop_back();
	// vec2.pop_back();
	// if (vec1.size() == vec2.size() && vec1.capacity() == vec2.capacity()){
	// 	for (size_t i = 0; i < 50; i++){
	// 		if (vec1[i] != vec2[i]){
	// 			std::cout << FRED("[KO]");
	// 			return ;
	// 		}
	// 	}
	// 	std::cout << FGRN("[OK]");
	// }	
	// else
	// 	std::cout << FRED("[KO]");

}

void	vector_modifiers_tests(){
	assign_tests();
	std::cout << std::endl;
	push_back_tests();
	std::cout << std::endl;
	pop_back_tests();
}