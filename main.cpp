#include <vector>
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

	ft::Vector<int> vec2(50);
	iota(vec2.begin(), vec2.end(), 1);
	ft::Vector<int>::iterator v2itbegin = vec2.begin();
	ft::Vector<int>::iterator v2itend = vec2.end();

	std::cout << "std::vector itbegin: " << *(v1itbegin + 1) << std::endl;
	std::cout << "ft::Vector itbegin: " << *(v2itbegin + 1) << std::endl;
	std::cout << "std::vector itend: " << *(v1itend - 1) << std::endl;
	std::cout << "ft::Vector itend: " << *(v2itend - 1) << std::endl;
}

int main()
{
	vector_iterator_tests();
	return (0);
}
