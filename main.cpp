#include "containers/vector/ClassVector.hpp"
#include <vector>
int main()
{
	ft::Vector<int>::iterator ibegin;
	ft::Vector<int>::iterator ilast;
	ft::Vector<int> test1((size_t)5, 10);
	ibegin = test1.begin();
	ilast = test1.end();
	ft::Vector<int> test(ibegin, ilast);
	return (0);
}
