#include <vector>
#include <string>
#include "containers/vector/ClassVector.hpp"
#include "containers/map/ClassMap.hpp"
#include "containers/stack/ClassStack.hpp"
#include "containers/vector/ClassVector.hpp"
#include "colors.hpp"

// void	reverse_iterator_tests(){
// 	ft::Vector<int> vec((size_t)5, 10);
// 	ft::Vector<int>::iterator	itbegin = vec.begin();
// 	ft::Vector<int>::iterator	itend = vec.end();
// 	ft::Vector<int>::reverse_iterator 	revbegin;
// 	ft::Vector<int>::reverse_iterator 	revend;
// }
template <class InputIterator, class T>
void	iota(InputIterator first, InputIterator last, T value){
	while (first != last){
		*first++ = value;
		value++;
	}
}

void	vector_iterator_tests(){
	std::cout << "Iterators unitest:" << std::endl;
	std::vector<int> vec1(50);
	iota(vec1.begin(), vec1.end(), 1);
	std::vector<int>::iterator v1itbegin = vec1.begin();
	std::vector<int>::iterator v1itend = vec1.end();

	ft::Vector<int> vec2(50);
	iota(vec2.begin(), vec2.end(), 1);
	ft::Vector<int>::iterator v2itbegin = vec2.begin();
	ft::Vector<int>::iterator v2itend = vec2.end();
	if (*v1itbegin == *v2itbegin && vec1.size() == vec2.size() &&
		vec1.capacity() == vec2.capacity())
		std::cout << FGRN("[OK]");
	else
		std::cout << FRED("[KO]");
	if (*(v1itend - 1) == *(v2itend - 1) && vec1.size() == vec2.size() &&
		vec1.capacity() == vec2.capacity())
		std::cout << FGRN("[OK]");
	else
		std::cout << FRED("[KO]");
	if (vec1.size() == vec2.size() && vec1.capacity() == vec2.capacity()){
		int i = 0;
		while (i < 50){
			if (*v1itbegin != *v2itbegin){
				std::cout << FRED("[KO]");
				return ;
			}
			v1itbegin++;
			v2itbegin++;
			i++;
		}
		std::cout << FGRN("[OK]");
	}
	else
		std::cout << FRED("[KO]");
}

void	reverse_iterator_tests(){
	std::cout << "Reverse terators unitest:" << std::endl;
	std::vector<int> vec1(50);
	iota(vec1.begin(), vec1.end(), 1);
	std::vector<int>::reverse_iterator v1itbegin = vec1.rbegin();
	std::vector<int>::reverse_iterator v1itend = vec1.rend();

	ft::Vector<int> vec2(50);
	iota(vec2.begin(), vec2.end(), 1);
	ft::Vector<int>::reverse_iterator v2itbegin = vec2.rbegin();
	ft::Vector<int>::reverse_iterator v2itend = vec2.rend();
	std::cout << *(v2itend - 1)<< std::endl;
	if (*(v1itend - 1) == *(v2itend - 1) && vec1.size() == vec2.size() &&
		vec1.capacity() == vec2.capacity())
		std::cout << FGRN("[OK]");
	else
		std::cout << FRED("[KO]");
	if (*(v1itbegin + 1) == *(v1itbegin + 1) && vec1.size() == vec2.size() &&
		vec1.capacity() == vec2.capacity())
		std::cout << FGRN("[OK]");
	else
		std::cout << FRED("[KO]");
	if (vec1.size() == vec2.size() && vec1.capacity() == vec2.capacity()){
		int i = 0;
		v1itend--;
		v2itend--;
		while (i < 50){
			std::cout << i << std::endl;
			if (*v1itend != *v2itend){
				std::cout << FRED("[KO]");
				return ;
			}
			v1itend--;
			v2itend--;
			i++;
		}
		std::cout << FGRN("[OK]");
	}
	else
		std::cout << FRED("[KO]");

}

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

void	vector_modifiers_tests(){
	assign_tests();
	std::cout << std::endl;
	push_back_tests();
}

int main()
{
	vector_iterator_tests();
	std::cout << std::endl;
	reverse_iterator_tests();
	std::cout << std::endl;
	vector_modifiers_tests();
	return (0);
}
