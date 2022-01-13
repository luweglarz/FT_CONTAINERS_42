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
	//Test with vector of size 50
	std::vector<int>	vec3(50);
	ft::Vector<int>		vec4(50);
	iota(vec3.begin(), vec3.end(), 1);
	iota(vec4.begin(), vec4.end(), 1);
	vec3.pop_back();
	vec4.pop_back();
	if (vec3.size() == vec4.size() && vec3.capacity() == vec4.capacity()){
		for (size_t i = 0; i < 49; i++){
			if (vec3[i] != vec4[i]){
				std::cout << FRED("[KO]");
				return ;
			}
		}
		std::cout << FGRN("[OK]");
	}	
	else
		std::cout << FRED("[KO]");

}

void	insert_tests(){
	std::cout << "Insert unitest:" << std::endl;
	//Test on empty vectors
	std::vector<int>	vec1;
	ft::Vector<int>		vec2;
	vec1.insert(vec1.begin(), 10);
	vec2.insert(vec2.begin(), 10);
	if (*vec1.begin() == *vec2.begin() && vec1.capacity() == vec2.capacity() &&
		vec1.size() == vec2.size())
		std::cout << FGRN("[OK]");
	else
		std::cout << FRED("[KO]");
	//Test with iterator pos
	vec1.resize(50);
	vec2.resize(50);
	iota(vec1.begin(), vec1.end(), 1);
	iota(vec2.begin(), vec2.end(), 1);
	std::vector<int>::iterator res1 = vec1.insert(vec1.begin() + 10, 10);
	ft::Vector<int>::iterator res2 = vec2.insert(vec2.begin() + 10, 10);
	if (*res1 != *res2){
		std::cout << FRED("[KO]");
	}
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
	//Test with n size overload
	vec1.clear();
	vec2.clear();
	vec1.resize(50);
	vec2.resize(50);
	iota(vec1.begin(), vec1.end(), 1);
	iota(vec2.begin(), vec2.end(), 1);
	vec1.insert(vec1.begin() + 10, 10, 10);
	vec2.insert(vec2.begin() + 10, 10, 10);
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
	//Test with iterator range overload
	vec1.clear();
	vec2.clear();
	vec1.resize(10);
	vec2.resize(10);
	std::vector<int>::iterator itb1 = vec1.begin();
	std::vector<int>::iterator ite1 = vec1.end();
	ft::Vector<int>::iterator itb2 = vec2.begin();
	ft::Vector<int>::iterator ite2 = vec2.end();
	iota(vec1.begin(), vec1.end(), 1);
	iota(vec2.begin(), vec2.end(), 1);
	vec1.insert(vec1.begin(),itb1, ite1);
	vec2.insert(vec2.begin(),itb2, ite2);
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
}

void	erase_tests(){

}

void	vector_modifiers_tests(){
	assign_tests();
	std::cout << std::endl;
	push_back_tests();
	std::cout << std::endl;
	pop_back_tests();
	std::cout << std::endl;
	insert_tests();
	std::cout << std::endl;
	erase_tests();
}