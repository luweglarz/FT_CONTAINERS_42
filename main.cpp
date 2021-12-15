#include "containers/vector/ClassVector.hpp"
#include <vector>
#include "iterators/iterator_trait.hpp"
int main()
{
	ft::Vector<int>::iterator ibegin;
	ft::Vector<int>::iterator ilast;
	ft::Vector<int> test1(5, 10);
	ibegin = test1.begin();
	ilast = test1.end();
	std::vector<int> bjr;
	ft::Vector<int> test(ibegin, ilast);
	return (0);
}
