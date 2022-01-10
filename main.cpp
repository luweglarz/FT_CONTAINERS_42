#include <vector>
#include <string>
#include "containers/vector/ClassVector.hpp"
#include "containers/map/ClassMap.hpp"
#include "containers/stack/ClassStack.hpp"
#include "containers/vector/ClassVector.hpp"

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
	std::vector<int> vec1(50);
	iota(vec1.begin(), vec1.end(), 1);
	std::vector<int>::iterator v1itbegin = vec1.begin();
	std::vector<int>::iterator v1itend = vec1.end();
	vec1.reserve(100);
	std::cout << "capa " << vec1.size() << std::endl;

	ft::Vector<int> vec2(50);
	iota(vec2.begin(), vec2.end(), 1);
	ft::Vector<int> vec3(vec2.begin(), vec2.end());
	ft::Vector<int>::iterator v2itbegin = vec2.begin();
	ft::Vector<int>::iterator v2itend = vec2.end();

	std::cout << "std::vector itbegin: " << *(v1itbegin + 1) << std::endl;
	std::cout << "ft::Vector itbegin: " << *(v2itbegin + 1) << std::endl;
	std::cout << "std::vector itend: " << *(v1itend - 1) << std::endl;
	std::cout << "ft::Vector itend: " << *(v2itend - 1) << std::endl;
}

template <typename T>
void	display_vector(T &vec){
	std::cout << vec.size() << std::endl;
	for (size_t i = 0; i < vec.size(); i++)
		std::cout << vec[i] << std::endl;
}

void	assign_tests(std::vector<int> &vec1, ft::Vector<int> &vec2){
	std::vector<int>::reverse_iterator revb1 = vec1.rbegin();
	std::vector<int>::reverse_iterator reve1 = vec1.rend();
	ft::Vector<int>::reverse_iterator revb2 = vec2.rbegin();
	ft::Vector<int>::reverse_iterator reve2 = vec2.rend();
	iota(vec1.begin(), vec1.end(), 1);
	iota(vec2.begin(), vec2.end(), 1);
	vec1.assign(revb1, reve1);
	vec2.assign(revb2, reve2);
	std::cout << "std::vec capacity " << vec1.capacity() << std::endl;
	std::cout << "ft::vec capacity " << vec2.capacity() << std::endl;
	display_vector(vec1);

}

void	push_back_tests(std::vector<int> &vec1, ft::Vector<int> &vec2){
	iota(vec1.begin(), vec1.end(), 1);
	iota(vec2.begin(), vec2.end(), 1);
	std::cout << "std::vec capacity " << vec1.capacity() << std::endl;
	std::cout << "ft::vec capacity " << vec2.capacity() << std::endl;
	vec1.push_back(31);
	vec2.push_back(31);
	std::cout << "std::vec capacity " << vec1.capacity() << std::endl;
	std::cout << "ft::vec capacity " << vec2.capacity() << std::endl;

}

void	vector_modifiers_tests(){
	std::vector<int>	vec1(50);
	ft::Vector<int>		vec2(50);
	//assign_tests(vec1, vec2);
	push_back_tests(vec1, vec2);
}

int main()
{
	//vector_iterator_tests();
	std::cout << std::endl;
	vector_modifiers_tests();
	return (0);
}
