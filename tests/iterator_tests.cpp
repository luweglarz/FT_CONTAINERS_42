#include "tests.hpp"

void	vector_iterator_tests(){
	std::cout << "iterators unitest:" << std::endl;
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
	std::cout << "reverse iterators unitest:" << std::endl;
	std::vector<int> vec1(50);
	iota(vec1.begin(), vec1.end(), 1);
	std::vector<int>::reverse_iterator v1itbegin = vec1.rbegin();
	std::vector<int>::reverse_iterator v1itend = vec1.rend();

	ft::Vector<int> vec2(50);
	iota(vec2.begin(), vec2.end(), 1);
	ft::Vector<int>::reverse_iterator v2itbegin = vec2.rbegin();
	ft::Vector<int>::reverse_iterator v2itend = vec2.rend();
	if (*(--v2itend ) == *(--v1itend) && vec1.size() == vec2.size() &&
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
		while (i < 49){
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